#!/bin/bash

# 需求: 打印 1~30, 注意 跳过3的倍数

for i in {1..30}; do
        if test $[ i % 3 ] -eq 0; then
                continue
        fi
        echo $i
done