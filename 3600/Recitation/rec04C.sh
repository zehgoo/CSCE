#!/bin/bash

#Samuel Njogo
#CSCE 3600
#Sec-201

let "number = (1 + $RANDOM % 10)"

echo -n "Enter between 1 and 10: "
read var

until [ $var == $number ]
do
    echo "Sorry you are not correct. Try again!"
    echo -n "Enter between 1 and 10: "
    read var
done

echo "Congratulations, the number is $var"
