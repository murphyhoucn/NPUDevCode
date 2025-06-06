#!/bin/bash

echo 'hello world'

: '
注释：这是一个简单的 Bash 脚本，它输出 "hello world"。

#!是一个约定的标记，它告诉系统这个脚本需要什么解释器来执行，即使用哪一种 Shell。
echo 命令用于向窗口输出文本。

.sh 执行方式
# 1. 直接执行
./hello.sh (前提是给脚本文件添加了执行权限， 可以使用 chmod +x hello.sh 命令)
# 2. 使用 bash 命令
bash hello.sh
'