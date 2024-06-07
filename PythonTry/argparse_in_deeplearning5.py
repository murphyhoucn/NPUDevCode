import argparse

def train(args):
    print(f"开始训练模型...")
    print(f"数据集路径: {args.data_path}")
    print(f"批量大小: {args.batch_size}")
    print(f"学习率: {args.learning_rate}")
    print(f"训练轮数: {args.epochs}")

def evaluate(args):
    print(f"开始评估模型...")
    print(f"数据集路径: {args.data_path}")
    print(f"模型路径: {args.model_path}")

def predict(args):
    print(f"开始预测...")
    print(f"输入图片路径: {args.image_path}")
    print(f"模型路径: {args.model_path}")

def main():
    # create the object of argument parser
    # main parser
    main_parser = argparse.ArgumentParser(description="parser in deeplearning weith sub-parser")

    sub_parsers = main_parser.add_subparsers(title="sub parser", description="available sub-parser", help="select a sub-parser", dest="command")
    sub_parsers.required = True

    # Train 子命令
    train_parser = sub_parsers.add_parser('train', help='训练模型')
    train_parser.add_argument("--data_path", type=str, required=True, help="数据集路径")
    train_parser.add_argument("--batch_size", type=int, default=32, help="批量大小")
    train_parser.add_argument("--learning_rate", type=float, default=0.001, help="学习率")
    train_parser.add_argument("--epochs", type=int, default=10, help="训练轮数")
    train_parser.set_defaults(func=train)

    # Evaluate 子命令
    evaluate_parser = sub_parsers.add_parser('evaluate', help='评估模型')
    evaluate_parser.add_argument("--data_path", type=str, required=True, help="数据集路径")
    evaluate_parser.add_argument("--model_path", type=str, required=True, help="模型路径")
    evaluate_parser.set_defaults(func=evaluate)

    # Predict 子命令
    predict_parser = sub_parsers.add_parser('predict', help='预测图片分类')
    predict_parser.add_argument("--image_path", type=str, required=True, help="输入图片路径")
    predict_parser.add_argument("--model_path", type=str, required=True, help="模型路径")
    predict_parser.set_defaults(func=predict)

    args = main_parser.parse_args()
    args.func(args)

if __name__ == "__main__":
    main()

# (base) houjinliang@3080server:~/MyDevProject/NPUDevCode/PythonTry$ python argparse_in_deeplearning5.py train --data_path ./data --batch_size 64 --learning_rate 0.01 --epochs 20
# 开始训练模型...
# 数据集路径: ./data
# 批量大小: 64
# 学习率: 0.01
# 训练轮数: 20

# (base) houjinliang@3080server:~/MyDevProject/NPUDevCode/PythonTry$ python argparse_in_deeplearning5.py evaluate --data_path ./data  --model_path ./model.pth
# 开始评估模型...
# 数据集路径: ./data
# 模型路径: ./model.pth

# (base) houjinliang@3080server:~/MyDevProject/NPUDevCode/PythonTry$ python argparse_in_deeplearning5.py predict --image_path ./data  --model_path ./model.pth
# 开始预测...
# 输入图片路径: ./data
# 模型路径: ./model.pth