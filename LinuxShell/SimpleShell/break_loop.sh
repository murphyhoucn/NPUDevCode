#!/bin/bash
# 需求: 执行死循环 每隔1秒打印当前时间, 执行10次停止
i=0;
while true; do
        sleep 1
        echo $i `date +"%Y-%m-%d %H:%M:%S"`

        i=$[ i + 1]
        if [ $i -eq 10 ]; then
                break
        fi
done