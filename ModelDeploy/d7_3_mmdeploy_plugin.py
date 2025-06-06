import tensorrt as trt
from mmdeploy.backend.tensorrt import load_tensorrt_plugin
load_tensorrt_plugin()
def get_plugin_names():
    return [pc.name for pc in trt.get_plugin_registry().plugin_creator_list]
print(get_plugin_names())