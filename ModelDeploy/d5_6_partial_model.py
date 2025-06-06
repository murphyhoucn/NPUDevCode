import onnx

# onnx.utils.extract_model('whole_model.onnx', 'partial_model.onnx', ['22'], ['28'])
# onnx.utils.extract_model('whole_model.onnx', 'submodel_1.onnx', ['22'], ['27', '31'])
# onnx.utils.extract_model('whole_model.onnx', 'submodel_2.onnx', ['22', 'input.1'], ['28'])
# onnx.utils.extract_model('whole_model.onnx', 'submodel_3.onnx', ['24'], ['28']) # error
# onnx.utils.extract_model('whole_model.onnx', 'submodel_4.onnx', ['24', '26'], ['31'])
# onnx.utils.extract_model('whole_model.onnx', 'more_output_model.onnx', ['input.1'], ['31', '23', '25', '27'])


onnx.utils.extract_model('whole_model.onnx', 'debug_model_1.onnx', ['input.1'], ['23'])
onnx.utils.extract_model('whole_model.onnx', 'debug_model_2.onnx', ['23'], ['25'])
onnx.utils.extract_model('whole_model.onnx', 'debug_model_3.onnx', ['23'], ['27'])
onnx.utils.extract_model('whole_model.onnx', 'debug_model_4.onnx', ['25', '27'], ['31'])