#!/bin/bash

my_arr=(AA BB CC)


echo "way1"
for var in ${my_arr[*]}
do
  echo $var
done


echo "way2"
my_arr_num=${#my_arr[*]}
for((i=0;i<my_arr_num;i++));
do
  echo "-----------------------------"
  echo ${my_arr[$i]}
done