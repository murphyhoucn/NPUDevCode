import argparse

def main():
    # 创建ArgumentParser对象
    parser = argparse.ArgumentParser(description="这是argparse的实例程序2.")

    # 添加参数
    parser.add_argument("input_file", type=str, help="input file name")
    parser.add_argument("-o", "--output_file", type=str, help="output file name", default="output.txt")
    parser.add_argument("-v", "--verbose", action="store_true", help="detail mode")
    parser.add_argument("-l", "--level", type=int, choices=range(1, 6), help="select the level from 1 to 6")

    args = parser.parse_args()

    if args.verbose:
        print(f"input file: {args.input_file}.")
        print(f"output file: {args.output_file}.")
        if args.level:
            print(f"selected level: {args.level}.")

if __name__ == "__main__":
    main()

# (base) houjinliang@3080server:~/MyDevProject/NPUDevCode/PythonTry$ python argparse_in_deeplearning2.py data.txt -v -l 5
# input file: data.txt.
# output file: output.txt.
# selected level: 5.