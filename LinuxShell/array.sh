#!/bin/bash

# 数组示例
array=(1 2 3 4 5)
# 输出数组元素
echo "Array elements:"
for i in "${array[@]}"; do
    echo $i
done


: '
# 数组
# Bash 支持数组变量，可以使用括号定义数组，例如 array=(1 2 3)。
# 数组元素可以通过索引访问，例如 echo ${array[0]}。
# 数组的长度可以使用 ${#array[@]} 语法获取，例如 echo ${#array[@]}。
# 数组的遍历可以使用 for 循环，例如 for i in "${array[@]}"; do echo $i; done。

# 特殊变量
# Bash 中有一些特殊变量，例如 $0 表示脚本名，$1、$2 等表示脚本参数，$# 表示参数个数，$@ 和 $* 表示所有参数。
# 这些特殊变量可以在脚本中使用，例如 echo "Script name: $0, First argument: $1, Number of arguments: $#".

# 环境变量
# Bash 中的环境变量是系统级的变量，可以通过 export 命令设置，例如 export PATH="/usr/local/bin:$PATH"。
# 环境变量可以在脚本中使用，例如 echo "PATH: $PATH"。
# 环境变量的作用域是全局的，可以在任何脚本或命令中访问。
'