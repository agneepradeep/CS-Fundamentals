#!/bin/bash

# Write a shell script to find the sum of a given number

echo -n "Type Number: "
read number

temp_copy=$number
sum_of_digits=0

while [ $temp_copy -ne 0 ]; do
    digit=$((temp_copy%10))
    sum_of_digits=$((sum_of_digits + digit))
    temp_copy=$((temp_copy/10))
done
echo "Sum of Digits of $number is $sum_of_digits"