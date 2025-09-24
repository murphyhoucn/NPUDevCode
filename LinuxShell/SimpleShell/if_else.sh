#!/bin/bash

a=20
b=10

# 需求1: 判断 a 是否 100 # 注意：这里的 > 是字符串比较运算符，不是数字比较运算符
if [ $a > 100 ]; then
        echo "$a 大于 100"
fi


# 需求2: 判断 a 是否等于 b
if [ $a -eq $b ]; then
        echo "$a 等于 $b"
else
        echo "$a 不等于 $b"
fi

# 需求3: 判断 a 与 b 比较
if [ $a -lt $b ]; then
        echo "$a 小于 $b"
elif [ $a -eq $b ]; then
        echo "$a 等于 $b"
else
        echo "$a 大于 $b"
fi


# 需求4: 判断 (a + 10) 和 (b * b) 比较大小
if test $[ a + 10 ] -gt $[ b * b ]; then
        echo "(a+10) 大于 (b * b)"
else
        echo "(a+10) 小于或等于 (b*b)"
fi