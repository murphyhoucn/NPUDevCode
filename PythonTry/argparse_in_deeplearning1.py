import argparse

# 创建ArgumentParser对象
parser = argparse.ArgumentParser(description="argparse的示例程序！")

# 添加参数
# “name”是一个必须的参数
parser.add_argument("name", type=str, help="用户的名字") 

# “age”是一个可选的参数
parser.add_argument("-a", "--age", type=int, help="用户的年龄", default=18)
parser.add_argument("-v", "--verbose", action="store_true", help="详细输出")

# 解析命令行参数
args = parser.parse_args()

# 使用参数
print(f"hello, {args.name}!")
if args.verbose:
    print(f"详细模式开启！你的年龄：{args.age}!")



# (base) houjinliang@3080server:~/MyDevProject/NPUDevCode/PythonTry$ python argparse_in_deeplearning1.py jack
# hello, jack!

# (base) houjinliang@3080server:~/MyDevProject/NPUDevCode/PythonTry$ python argparse_in_deeplearning1.py jack -a 25 -v
# hello, jack!
# 详细模式开启！你的年龄：25!