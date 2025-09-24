#!/bin/bash

echo "Shell 传递参数实例！";

echo "执行的文件名：$0";

echo "第一个参数为：$1";

echo "第二个参数为：$2";

echo "第三个参数为：$3";

: '
(base) houjinliang@3080server:~/MyDevProject/NPUDevCode/LinuxShell$ bash trans_params.sh 1 2 3
Shell 传递参数实例！
执行的文件名：trans_params.sh
第一个参数为：1
第二个参数为：2
第三个参数为：3
'