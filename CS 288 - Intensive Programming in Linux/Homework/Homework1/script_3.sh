#!/bin/bash

# Problem 3:

# Write a Bash script, which sorts a list of command line parameters in ascending order. For example, your command will look something like:

# $ insert-sort.sh 7 2 3 9 -1

# and type enter.
# Your program will return: -1 2 3 7 9

# Use only basic commands and array. Do not use any built-in commands that sort array.


# args into an array to sort in place
arr=( "$@" )
n=${#arr[@]}

# Insertion sort (cs114)
for (( i=1; i<n; i++ )); do
  key="${arr[$i]}"
  j=$((i-1))
  # While arr[j] > key, shift right
  while [ "$j" -ge 0 ]; do
    # numeric comparison; assume inputs are integers
    if [ "${arr[$j]}" -gt "$key" ]; then
      arr[$((j+1))]="${arr[$j]}"
      j=$((j-1))
    else
      break
    fi
  done
  arr[$((j+1))]="$key"
done

# Print results
out=""
for x in "${arr[@]}"; do
  if [ -z "$out" ]; then
    out="$x"
  else
    out="$out $x"
  fi
done
echo "$out"

