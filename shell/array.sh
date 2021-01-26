#!/bin/bash
string="hello,shell,haha"
array=(${string//,/ }) 
echo ${array[0]}
for var in ${array[@]}
do
  echo $var
done