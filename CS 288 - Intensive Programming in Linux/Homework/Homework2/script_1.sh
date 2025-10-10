#!/usr/bin/env bash

infile="$1"
if [[ -z "$infile" || ! -f "$infile" ]]; then
  echo "Usage: $0 <input-file>" >&2
  exit 1
fi

# Array to hold all matched dates (any of ., /, - as separator)
dates=()

# Read the file line by line and extract all date tokens
while IFS= read -r line; do
  while IFS= read -r d; do
    dates+=("$d")
  done < <(grep -Eo '\b(0[1-9]|1[0-2])([/.-])(0[1-9]|[12][0-9]|3[01])\2[0-9]{4}\b' <<<"$line")
done < "$infile"

# Create sortable keys (YYYY-MM-DD) paired with the original token, sort by key, and print originals
{
  for d in "${dates[@]}"; do
    # Positions are consistent: MM at 0-1, DD at 3-4, YYYY at 6-9 (separator is at index 2 and 5)
    mm="${d:0:2}"
    dd="${d:3:2}"
    yyyy="${d:6:4}"
    printf "%s\t%s\n" "${yyyy}-${mm}-${dd}" "$d"
  done
} | sort -t$'\t' -k1,1 | cut -f2
