import onnxruntime
import numpy as np

sess = onnxruntime.InferenceSession('linear_func.onnx')
a = np.random.rand(10, 10).astype(np.float32)
b = np.random.rand(10, 10).astype(np.float32)
x = np.random.rand(10, 10).astype(np.float32)

output = sess.run(['output'], {'a': a, 'b': b, 'x': x})[0]

assert np.allclose(output, a * x + b)


# 第四行，有问题！不知道为什么？
# onnx                   1.17.0
# onnxruntime-gpu        1.8.0
