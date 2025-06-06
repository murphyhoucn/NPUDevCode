import onnx
model = onnx.load('linear_func_2.onnx')
print(model)


graph = model.graph
node = graph.node
input = graph.input
output = graph.output
print(node)
print(input)
print(output)


node_0 = node[0]
node_0_inputs = node_0.input
node_0_outputs = node_0.output
input_0 = node_0_inputs[0]
input_1 = node_0_inputs[1]
output = node_0_outputs[0]
op_type = node_0.op_type

print(input_0)
print(input_1)
print(output)
print(op_type)

# Output
"""
a
x
c
Mul
"""