#!bin/bash

# Write a program to reverse a given string and check if it is a palindrome.

echo -n "Type a string"
read string

temp_copy=$(echo "$string"|rev)

if [ "$string" = "$temp_copy" ]; then
    echo "String is a Palindrome"
else
    echo "String is not a Palindrome"
fi