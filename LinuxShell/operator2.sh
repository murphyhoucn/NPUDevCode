#!/bin/bash

a=4

b=20

#加法运算
echo expr $a + $b
echo `expr $a + $b`
# 注意：expr 命令的输出结果是一个字符串，如果需要将其作为数字使用，最好用反引号 ` 包裹起来。
# 例如：c=`expr $a + $b`，这样 c 就是一个数字变量。

#减法运算
echo expr $a - $b
echo `expr $a - $b`


#乘法运算，注意*号前面需要反斜杠
echo expr $a \* $b
echo `expr $a \* $b`

#除法运算
echo $a / $b
echo `expr $a / $b`


# 此外，还可以通过(())、$(())、$[]进行算术运算。
((a++))
echo "a = $a"
c=$((a + b))
d=$[a + b]
echo "c = $c"
echo "d = $d"