#!/bin/bash

# Write a script to count the number of lines, words and charaters in a file.

echo -n "Type a filename: "
read filename

if [ -f "$filename" ]; then
    lines=$(wc -l < "$filename")
    words=$(wc -w < "$filename")
    characters=$(wc -m < "$filename")

    echo "File Name: $filename"
    echo "Words: $words"
    echo "Lines: $lines"
    echo "Characters: $characters"

else
    echo "File $filename does not exist"
fi