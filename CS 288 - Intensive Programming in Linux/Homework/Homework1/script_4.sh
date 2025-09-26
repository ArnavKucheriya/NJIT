#!/bin/bash

# Problem 4:

declare -A counts

# Initialize counts to 0 for a..z
for c in {a..z}; do
  counts["$c"]=0
done

# Iterate over /bin entries (files only)
for path in /bin/*; do
  [ -f "$path" ] || continue
  name="${path##*/}"
  first="${name:0:1}"
  # simple case match
  case "$first" in
    [a-z]) counts["$first"]=$(( counts["$first"] + 1 ));;
    *) : ;;  # ignore others (digits, symbols, uppercase)
  esac
done

# Print results
for c in {a..z}; do
  echo "$c ${counts[$c]}"
done

