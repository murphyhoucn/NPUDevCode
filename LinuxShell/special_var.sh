#!/bin/bash

echo $0 # bash special_var.sh 
echo $1 # bash special_var.sh 123
: '

# 特殊变量
Bash 中有一些特殊变量，例如 $0 表示脚本名，$1、$2 等表示脚本参数.
$# 表示参数个数，
$@ 和 $* 表示所有参数。

这些特殊变量可以在脚本中使用，例如 echo "Script name: $0, First argument: $1, Number of arguments: $#".
'