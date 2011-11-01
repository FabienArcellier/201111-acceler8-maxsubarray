#!/bin/sh
a=`date +%y%m%d-%H%M%S` 
mkdir -p reports 
mkdir ./reports/$a
echo $a >./reports/$a/$a.txt
echo >>./reports/$a/$a.txt
for i in $@ 
do
  if [ $i != $1 ]
  then
    echo >>./reports/$a/$a.txt
    echo $i >>./reports/$a/$a.txt
    time -a -o ./reports/$a/$a.txt ./run $1 $i  >>./reports/$a/$a.txt
    echo >>./reports/$a/${a}_profiling.txt
    echo $i >>./reports/$a/${a}_profiling.txt
    gprof run >>./reports/$a/${a}_profiling.txt
  fi
done 
echo >>./reports/$a/$a.txt
echo Exécution complète :  >>./reports/$a/$a.txt
time -a -o ./reports/$a/$a.txt ./run $@  | grep ZZZ
exit