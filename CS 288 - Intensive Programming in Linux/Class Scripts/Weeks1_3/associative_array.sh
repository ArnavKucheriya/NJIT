#!/bin/bash

declare -A shade

shade[apple]="dark red"
shade[bannana]="Yellow"
share[grape]="Purple"

# add new element
shade+=([grape]=purple)

for i in apple banana grape
do
	echo ${shade[$i]}
done

for i in ${!shade[@]}; do
	echo $i ${shade[$i]}
done

#remove an element
unset shade[apple]
