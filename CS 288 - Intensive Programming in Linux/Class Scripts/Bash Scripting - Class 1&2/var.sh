#!/bin/bash
STR="Hello World"
echo $STR

echo

STR2=Hello
echo $STR2

echo

echo ${STR}2

echo

var="Test String"
newvar="Value of var is $var"
echo $newvar
echo Double quotes allow variable resolution.

echo

newvar2='Value of var is $var'
echo $newvar2
echo Single quotes do not allow variable resolution

echo

echo Getting the first character of the string
echo Value of var = $var
echo ${var:0:2} #echo will pring letters Te

echo 

echo Escape quotes can be included using backslash
var="\"Test String\""
echo $var
echo {var:0:1} gives ${var:0:1}
.
