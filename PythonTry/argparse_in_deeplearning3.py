import argparse

def main(args):
    print("super parameters configuration.")
    print(f"dataset path: {args.data_path}")
    print(f"批量大小: {args.batch_size}")
    print(f"学习率: {args.learning_rate}")
    print(f"训练轮数: {args.epochs}")
    print(f"模型架构: {args.model}")
    print(f"优化器: {args.optimizer}")
    print(f"数据增强: {args.augmentation}")
    # 在这里添加训练代码
    # 比如，加载数据、构建模型、编译模型、训练模型等

if __name__ == "__main__":
    
    # creat the object of argument parser
    parser = argparse.ArgumentParser(description="argparse in deep learning task.")

    # add argument
    parser.add_argument("--data_path", type=str, required=True, help="path of the dataset")
    # required=True：指定该参数是必需的。如果命令行中没有提供这个参数，解析参数时将会报错。
    # required=False：指定该参数是可选的（这是默认值）。
    parser.add_argument("--batch_size", type=int, default=32, help="size of batch")
    parser.add_argument("--learning_rate", type=float, default=0.001, help="learning rate")
    parser.add_argument("--epochs", type=int, default=10, help="the training epoch")
    parser.add_argument("--model", type=str, choices=["resnet", "vgg", "densenet"], default="resnet", help="selected model")
    parser.add_argument("--optimizer", type=str, choices=["sgd", "adam"], default="sgd", help="select the optimizer")
    parser.add_argument("--augmentation", action="store_true", help="whether we use the data augmentation")
    parser.add_argument("--model_save_path", type=str, default="model.pth", help="save model")
    parser.add_argument("--log_interval", type=int, default=10, help="the interval of epoch we save the model")

    # parse the argument
    args = parser.parse_args()

    main(args)



# (base) houjinliang@3080server:~/MyDevProject/NPUDevCode/PythonTry$ python argparse_in_deeplearning3.py --data_path /path/to/dataset --batch_size 64 --learning_rate 0.01 --epochs 20 --model vgg --optimizer sgd --augmentation --model_save_path my_model.pth --log_interval 5
# super parameters configuration.
# dataset path: /path/to/dataset
# 批量大小: 64
# 学习率: 0.01
# 训练轮数: 20
# 模型架构: vgg
# 优化器: sgd
# 数据增强: True