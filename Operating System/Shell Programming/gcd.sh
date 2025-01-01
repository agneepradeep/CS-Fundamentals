#!/bin/bash


# Create a shell script to calculate the GCD (Greatest Common Divisor) and LCM (Least Common Multiple) of two numbers.


echo -n "Type number a: "
read a

echo -n "Type number b: "
read b

gcd() {
    local a=$1
    local b=$2

    while [ $b -ne 0 ]; do
        local temp=$b
        b=$((a%b))
        a=$temp
    done
    echo $a
}

lcm() {
    local a=$1
    local b=$2
    local gcd_value=$(gcd $a $b)
    echo "$((a*b/gcd_value))"

}

gcd_value=$(gcd $a $b)
echo "GCD($a, $b) = $gcd_value"
lcm_value=$(lcm $a $b)
echo "LCM($a, $b) = $lcm_value"