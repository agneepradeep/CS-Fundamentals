#!/bin/bash
echo -n "Type a number: "
read number
if [ $number -gt 0 ]; then
    echo "$number is Postive"
elif [ $number -eq 0 ]; then
    echo "$number is Zero"
else
    echo "$number is Negative"
fi

# Write a shell script to check whether a given number is positive, negative or zero.