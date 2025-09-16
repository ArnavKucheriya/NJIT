#!/bin/bash
var="Test"
echo Variable value: $var
echo Variable length: ${#var}
echo Variable Substring \(index 1\): ${var:1}
echo Variable Substring \(index 1-2\): ${var:1:2}

echo

echo -n "Enter a number 1<x<10:"
read num
if [ $num -lt 10 ]; then
if [ $num -gt 1 ]; then
echo "$num*$num="$((num*num))
else
echo "Wrong number!"
fi
else
echo "Wrong number!"
fi

