#!/bin/bash

echo "-- $* 演示 ---"
for i in "$*"; do
    echo $i
done

echo "-- $@ 演示 ---"
for i in "$@"; do
    echo $i
done

: '
(base) houjinliang@3080server:~/MyDevProject/NPUDevCode/LinuxShell$ bash star_at.sh 1 2 3 
-- 1 2 3 演示 ---
1 2 3
-- 1 2 3 演示 ---
1
2
3
'
# 注意：$* 和 $@ 的区别在于双引号的使用。
# 当使用 "$*" 时，所有参数被视为一个单一的字符串。
# 当使用 "$@" 时，每个参数都被视为独立的字符串。
# 在循环中，"$*" 会将所有参数作为一个整体处理，而 "$@" 则会将每个参数单独处理。
# 这意味着如果参数中有空格，"$*" 会将它们视为一个整体，而 "$@" 则会将它们视为独立的参数。