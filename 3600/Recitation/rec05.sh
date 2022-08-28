#!/bin/bash 

function curve()
{
	shift
	arr=("$@")
	index=0

	for i in "${arr[@]}"
	do
		let grades[index]=$i+$incr
		let index+=1
	done

	echo "Curved Grades"
	for (( k=0; $k<${#grades[*]}; k=$k+1 ))
	do
		echo "grades[$k] = ${grades[k]}"
	done
}

if [ $# == 0 ]
then
	echo "usage: ./rec05.sh <curve amount>"
	exit
fi

incr=$1

grades=()
for x in 1 2 3 4 5
do
	echo -n "Enter QUIZ #$x: "
	read var
	grades[$x-1]=$var
done

curve "$incr" "${grades[@]}"


