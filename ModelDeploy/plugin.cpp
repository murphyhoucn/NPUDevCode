// Copyright (c) OpenMMLab. All rights reserved
#include "trt_dynamic_resize.hpp"

#include <assert.h>

#include <chrono>

#include "trt_plugin_helper.hpp"
#include "trt_serialize.hpp"
// 引入CUDA核函数bicubic_interpolate在的头文件，会在enqueue中使用
#include "../bicubic_interpolate/trt_bicubic_interpolate_kernel.hpp"

using namespace nvinfer1;

namespace mmdeploy {
namespace {
static const char *PLUGIN_VERSION{"1"};
static const char *PLUGIN_NAME{"DynamicTRTResize"};//插件名需和ONNX节点名一致，在转换TensorRT模型时被触发
}  // namespace

DynamicTRTResize::DynamicTRTResize(const std::string &name, bool align_corners)
    : TRTPluginBase(name), mAlignCorners(align_corners) {}

DynamicTRTResize::DynamicTRTResize(const std::string name, const void *data,
                                             size_t length)
    : TRTPluginBase(name) {
  deserialize_value(&data, &length, &mAlignCorners);
}

nvinfer1::IPluginV2DynamicExt *DynamicTRTResize::clone() const TRT_NOEXCEPT {
  DynamicTRTResize *plugin =
      new DynamicTRTResize(mLayerName, mAlignCorners);
  plugin->setPluginNamespace(getPluginNamespace());

  return plugin;
}

nvinfer1::DimsExprs DynamicTRTResize::getOutputDimensions(
    int outputIndex, const nvinfer1::DimsExprs *inputs, int nbInputs,
    nvinfer1::IExprBuilder &exprBuilder) TRT_NOEXCEPT {
  nvinfer1::DimsExprs ret;
  ret.nbDims = 4;
  // 输入张量有两个：input和size_tensor，后者只用于计算输出张量形状
  ret.d[0] = inputs[0].d[0];
  ret.d[1] = inputs[0].d[1];
  ret.d[2] = inputs[1].d[2];
  ret.d[3] = inputs[1].d[3];
  return ret;
}

bool DynamicTRTResize::supportsFormatCombination(int pos,
                                                      const nvinfer1::PluginTensorDesc *ioDesc,
                                                      int nbInputs, int nbOutputs) TRT_NOEXCEPT {
  if (pos == 0) {
    return (ioDesc[pos].type == nvinfer1::DataType::kFLOAT &&
            ioDesc[pos].format == nvinfer1::TensorFormat::kLINEAR);

  } else {
    return ioDesc[pos].type == ioDesc[0].type && ioDesc[pos].format == ioDesc[0].format;
  }
}

void DynamicTRTResize::configurePlugin(const nvinfer1::DynamicPluginTensorDesc *inputs,
                                            int nbInputs,
                                            const nvinfer1::DynamicPluginTensorDesc *outputs,
                                            int nbOutputs) TRT_NOEXCEPT {}

size_t DynamicTRTResize::getWorkspaceSize(const nvinfer1::PluginTensorDesc *inputs,
                                               int nbInputs,
                                               const nvinfer1::PluginTensorDesc *outputs,
                                               int nbOutputs) const TRT_NOEXCEPT {
  return 0;
}

int DynamicTRTResize::enqueue(const nvinfer1::PluginTensorDesc *inputDesc,
                                   const nvinfer1::PluginTensorDesc *outputDesc,
                                   const void *const *inputs, void *const *outputs, void *workSpace,
                                   cudaStream_t stream) TRT_NOEXCEPT {
  int batch = inputDesc[0].dims.d[0];
  int channels = inputDesc[0].dims.d[1];
  int height = inputDesc[0].dims.d[2];
  int width = inputDesc[0].dims.d[3];

  int height_out = outputDesc[0].dims.d[2];
  int width_out = outputDesc[0].dims.d[3];
  const void *x = inputs[0];
  void *output = outputs[0];

  // TODO: add fp16 support
  auto data_type = inputDesc[0].type;
  switch (data_type) {
    case nvinfer1::DataType::kFLOAT:
      bicubic_interpolate<float>((float *)x, (float *)output, batch, channels, height, width,
                                 height_out, width_out, mAlignCorners, stream);
      break;
    default:
      return 1;
      break;
  }

  return 0;
}

nvinfer1::DataType DynamicTRTResize::getOutputDataType(int index,
                                                            const nvinfer1::DataType *inputTypes,
                                                            int nbInputs) const TRT_NOEXCEPT {
  return inputTypes[0];
}

// IPluginV2 Methods
const char *DynamicTRTResize::getPluginType() const TRT_NOEXCEPT { return PLUGIN_NAME; }

const char *DynamicTRTResize::getPluginVersion() const TRT_NOEXCEPT { return PLUGIN_VERSION; }

int DynamicTRTResize::getNbOutputs() const TRT_NOEXCEPT { return 1; }

size_t DynamicTRTResize::getSerializationSize() const TRT_NOEXCEPT {
  return serialized_size(mAlignCorners);
}

void DynamicTRTResize::serialize(void *buffer) const TRT_NOEXCEPT {
  serialize_value(&buffer, mAlignCorners);
}

////////////////////// creator /////////////////////////////

DynamicTRTResizeCreator::DynamicTRTResizeCreator() {
  mPluginAttributes.clear();
  mPluginAttributes.emplace_back(nvinfer1::PluginField("align_corners"));
  mFC.nbFields = mPluginAttributes.size();
  mFC.fields = mPluginAttributes.data();
}

const char *DynamicTRTResizeCreator::getPluginName() const TRT_NOEXCEPT { return PLUGIN_NAME; }

const char *DynamicTRTResizeCreator::getPluginVersion() const TRT_NOEXCEPT {
  return PLUGIN_VERSION;
}

nvinfer1::IPluginV2 *DynamicTRTResizeCreator::createPlugin(
    const char *name, const nvinfer1::PluginFieldCollection *fc) TRT_NOEXCEPT {
  nvinfer1::Dims size{2, {1, 1}};
  bool align_corners = 1;

  for (int i = 0; i < fc->nbFields; i++) {
    if (fc->fields[i].data == nullptr) {
      continue;
    }
    std::string field_name(fc->fields[i].name);
    //获取align_corners值，用于创建插件DynamicTRTResize的实例
    if (field_name.compare("align_corners") == 0) {
      align_corners = static_cast<const int *>(fc->fields[i].data)[0];
    }
  }
  // 创建插件DynamicTRTResize实例并返回
  DynamicTRTResize *plugin = new DynamicTRTResize(name, align_corners);
  plugin->setPluginNamespace(getPluginNamespace());
  return plugin;
}

nvinfer1::IPluginV2 *DynamicTRTResizeCreator::deserializePlugin(
    const char *name, const void *serialData, size_t serialLength) TRT_NOEXCEPT {
  auto plugin = new DynamicTRTResize(name, serialData, serialLength);
  plugin->setPluginNamespace(getPluginNamespace());
  return plugin;
}
REGISTER_TENSORRT_PLUGIN(DynamicTRTResizeCreator);//真正注册了该插件
}  // namespace mmdeploy