#!/bin/bash
echo "PATH: $PATH"

: '
# 环境变量
# Bash 中的环境变量是系统级的变量，可以通过 export 命令设置，例如 export PATH="/usr/local/bin:$PATH"。
# 环境变量可以在脚本中使用，例如 echo "PATH: $PATH"。
# 环境变量的作用域是全局的，可以在任何脚本或命令中访问。
'