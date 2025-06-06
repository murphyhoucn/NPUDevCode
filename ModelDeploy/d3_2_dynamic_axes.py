import torch

class Model(torch.nn.Module):
    def __init__(self):
        super().__init__()
        self.conv = torch.nn.Conv2d(3, 3, 3)

    def forward(self, x):
        x = self.conv(x)
        return x


model = Model()
dummy_input = torch.rand(1, 3, 10, 10)
model_names = ['model_static.onnx',
'model_dynamic_0.onnx',
'model_dynamic_23.onnx']

import torch

class Model(torch.nn.Module):
    def __init__(self):
        super().__init__()
        self.conv = torch.nn.Conv2d(3, 3, 3)

    def forward(self, x):
        x = self.conv(x)
        return x

model = Model()
dummy_input = torch.rand(1, 3, 10, 10)
model_names = ['model_static.onnx',
               'model_dynamic_0.onnx',
               'model_dynamic_23.onnx']

dynamic_axes_0 = {
    'in': {0: 'batch'},
    'out': {0: 'batch'}
}

dynamic_axes_23 = {
    'in': {2: 'width', 3: 'height'},
    'out': {2: 'width', 3: 'height'}
}

torch.onnx.export(model, dummy_input, model_names[0],
                  input_names=['in'], output_names=['out'])
torch.onnx.export(model, dummy_input, model_names[1],
                  input_names=['in'], output_names=['out'], dynamic_axes=dynamic_axes_0)
torch.onnx.export(model, dummy_input, model_names[2],
                  input_names=['in'], output_names=['out'], dynamic_axes=dynamic_axes_23)

torch.onnx.export(model, dummy_input, model_names[0],
input_names=['in'], output_names=['out'])
torch.onnx.export(model, dummy_input, model_names[1],
input_names=['in'], output_names=['out'], dynamic_axes=dynamic_axes_0)
torch.onnx.export(model, dummy_input, model_names[2],
input_names=['in'], output_names=['out'], dynamic_axes=dynamic_axes_23)