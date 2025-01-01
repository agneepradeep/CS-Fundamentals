#!/bin/bash

# Write a script to display the largest of three numbers entered by the user.

echo -n "Type 1st Number: "
read a

echo -n "Type 2nd Number: "
read b

echo -n "Type 3rd Number: "
read c

if [ $a -gt $b ] && [ $a -gt $c ]; then
    echo "1st Number $a is the Largest of all"
elif [ $b -gt $a ] && [ $b -gt $c ]; then
    echo "2nd Number $b is the largest of all"
else
    echo "3rd Number $c is the largest of all"
fi
