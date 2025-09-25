#!/bin/bash

suit=(Clubs Diamonds Hearts Spades)
rank=(2 3 4 5 6 7 8 9 10 Jack Queen King Ace)

# Count how many elements
num_suits=${#suit[@]}
num_ranks=${#rank[@]}

# Pick a random rank from a random suit
r=$((RANDOM%num_ranks))
s=$((RANDOM%num_suits))

echo ${rank[r]} of ${suit[s]}
