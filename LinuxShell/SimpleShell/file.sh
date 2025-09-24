#!/bin/bash

: '
. filename   # 注意点号(.)和文件名中间有一空格
或
source filename
'
echo "way1"
. array2.sh

echo "way2"
source array2.sh
