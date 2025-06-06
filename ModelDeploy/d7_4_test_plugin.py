from mmdeploy.backend.tensorrt.utils import from_onnx

engine = from_onnx(
    'srcnn3.onnx',
    'srcnn3',
    input_shapes=dict(
        input=dict(
            min_shape=[1, 3, 256, 256],
            opt_shape=[1, 3, 256, 256],
            max_shape=[1, 3, 256, 256]),
        factor=dict(
            min_shape=[1, 1, 256, 256],
            opt_shape=[1, 1, 512, 512],
            max_shape=[1, 1, 1024, 1024])))

from mmdeploy.backend.tensorrt import TRTWrapper

trt_model = TRTWrapper('srcnn3.engine', ['output'])

factor = torch.rand([1, 1, 768, 768], dtype=torch.float)
trt_output = trt_model.forward(dict(input=x.cuda(), factor=factor.cuda()))
torch_output = model.forward(x, factor)
assert np.allclose(
    trt_output['output'].cpu().numpy(),
    torch_output.cpu().detach(),
    rtol=1e-3,
    atol=1e-5)