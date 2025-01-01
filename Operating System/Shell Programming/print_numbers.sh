#!/bin/bash

# Write a shell program to print all prime numbers between two given numbers.

echo -n "Type start Point: "
read start

echo -n "Type end Point: "
read end

is_prime() {
    local num=$1
    
    if [ $num -le 1 ]; then
        return 1
    fi
    for ((i = 2; i*i <=num; i++)); do
        if [ $((num%i)) -eq 0 ]; then
            return 1
        fi
    done
    return 0
}

echo "Prime numbers between $start and $end are:"
for ((n = start; n<=end; n++)); do
    if is_prime $n; then
        echo -n "$n "
    fi
done
echo