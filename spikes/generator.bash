#!/bin/bash

cols=$1
rows=$2
range=$3
negativ=$4

# cols est le nombre de ligne
# rows est le nombre de colonnes
# range est l'intervale dans lequel se trouve les valeurs
#negativ est la teneur en nombre negativ (plus il est faible et plus il y a des nombres negatifs )

for (( k = 0; k < $cols; k++ ))
do
  for (( j = 0; j < $rows; j++))
  do
    echo -n $(( ($RANDOM % $range) - ($range / $negativ) ))" "
  done
  echo
done