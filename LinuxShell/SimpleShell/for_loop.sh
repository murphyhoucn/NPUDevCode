#!/bin/bash


# 需求1: 遍历 1~5
for i in 1 2 3 4 5; do
        echo $i;
done
# 需求2: 遍历 1~100
for i in {1..100}; do
        echo $i
done
# 需求3: 遍历 1~100之间的奇数
for i in {1..100..2}; do
        echo $i
done
# 需求4: 遍历 根目录 下的内容
for f in `ls /`; do
        echo $f
done