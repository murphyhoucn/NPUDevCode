#!/bin/bash

# string length
skill='java'
echo ${skill}    # 输出结果: java
echo ${#skill}   # 输出结果: 4

# substring operations
str="I am goot at $skill"
echo ${str:2}    # 输出结果为: am goot at java  从第二个字符开始截取,到结尾
echo ${str:2:2}    # 输出结果为: am  从第二个字符开始截取,截取2个字符
echo ${str: -4}   # 输出结果为: java  从倒数第四个字符开始截取,到结尾
echo ${str: -4:2} # 输出结果为: ja   从倒数第四个字符开始截取,截取2个字符

# string replacement
str="I am good at java, I love java"
echo ${str/java/python}  # 输出结果为: I am good at python, I love java  替换第一个java为python
echo ${str//java/python} # 输出结果为: I am good at python, I love python  替换所有的java为python

# find and replace
str="I am goot at  $skill"
echo `expr index "$str" am`    # 输出是: 3