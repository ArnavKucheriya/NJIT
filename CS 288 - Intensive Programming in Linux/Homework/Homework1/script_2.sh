#!/bin/bash

# Problem 2:
# Write a Bash script, which prints out the entries (including files and sub-directories) in a directory in a reversed order as what obtained using filename expansion. The pathname of the directory is provided as an argument. Assuming that with filename expansion you see /my/dir contains "cache cron games lib log run tmp," your program "reverse.sh /my/dir" will print "tmp run log lib games cron cache." You can print the names on one line, or each name on a line.

dir="$1"
if [ -z "$dir" ] || [ ! -d "$dir" ]; then
  echo "Usage: $0 <directory>"
  exit 1
fi

# Array of filename expansion
entries=( "$dir"/* )

# If directory could be empty, guard null case
if [ ! -e "$dir"/* ]; then
  # still try to detect dotfiles? requirement doesn't demand; just handle empty
  entries=()
fi

# simple reverse function
reverse() {
  local -n arr_ref=$1
  local n=${#arr_ref[@]}
  # Print each on its own line to avoid problems with spaces
  for (( i=n-1; i>=0; i-- )); do
    # Print the base name
    bn="${arr_ref[$i]##*/}"
    echo "$bn"
  done
}

reverse entries

