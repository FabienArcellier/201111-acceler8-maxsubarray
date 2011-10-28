#!/bin/sh
echo "Execution des tests"

for binaire in * 
do 
  if [ $binaire != "." -a $binaire != ".." -a $binaire != ".svn" -a $binaire != "tests.sh" -a -x $binaire -a ! -d $binaire ]
  then
    ./$binaire >> log.txt
  fi
done

cat log.txt

reussi=`cat log.txt | grep Success --count`
echec=`cat log.txt | grep Failed --count`

echo "\033[32m"
echo "Nombre de test reussi : $reussi"
echo "\033[31mNombre de test echoue : $echec"
echo "\033[0mFin des tests"
rm log.txt