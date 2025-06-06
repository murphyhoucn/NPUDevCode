#!bin/bash

name="murphy"
age=18
echo "My name is ${name}, I am ${age} years old."

# 已定义的变量，可以被重新定义
your_name="tom"
echo $your_name
your_name="alibaba"
echo $your_name

# 删除
unset your_name
echo $your_name # 输出为空

: '
注释：这是一个简单的 Bash 脚本，它定义了两个变量 name 和 age，并输出它们的值。

# 变量定义
# name="murphy" 定义了一个名为 name 的变量，并赋值为 "murphy"。
# age=18 定义了一个名为 age 的变量，并赋值为 18。
# 注意：在变量赋值时，等号两边不能有空格。

# 输出变量值
# echo "My name is $name, I am $age years old." 使用 echo 命令输出变量的值。

# 变量引用
# 在 Bash 中，变量可以通过前缀 $ 来引用，例如 $name 和 $age。

# 变量作用域
# 在 Bash 中，变量的作用域是全局的，除非使用 local 关键字在函数内部定义局部变量。

# 变量类型
# Bash 中的变量类型是动态的，可以存储字符串、整数等多种类型的数据。

# 变量命名规则
# 变量名可以包含字母、数字和下划线，但不能以数字开头。
# 变量名区分大小写，例如 name 和 NAME 是两个不同的变量。

# 变量的默认值
# 如果变量未被赋值，则其默认值为空字符串。

# 变量的使用
# 在脚本中，可以直接使用变量名来引用变量的值，例如 $name 和 $age。

# 变量的修改
# 可以通过重新赋值来修改变量的值，例如 name="new_name"。

# 变量的删除
# 可以使用 unset 命令删除变量，例如 unset name。

# 变量的导出
# 可以使用 export 命令将变量导出为环境变量，例如 export name="murphy"。

# 变量的读取
# 可以使用 read 命令从用户输入中读取变量的值，例如 read name。

# 变量的默认值
# 可以使用 ${variable:-default_value} 语法来设置变量的默认值，例如 echo ${name:-"default_name"}。

# 变量的长度
# 可以使用 ${#variable} 语法来获取变量的长度，例如 echo ${#name}。

# 变量的替换
# 可以使用 ${variable/pattern/replacement} 语法来进行字符串替换，例如 echo ${name/murphy/john}。


'