#!/bin/bash

# Promblem 5

root="$1"
if [ -z "$root" ] || [ ! -d "$root" ]; then
  echo "Usage: $0 <directory>"
  exit 1
fi

declare -A first_seen 

# find to walk the directory tree
while IFS= read -r path; do
  [ -f "$path" ] || continue
  fname="$(basename -- "$path")"

  if [ -n "${first_seen[$fname]}" ]; then
    echo "Duplicate filename found:"
    echo "  Original: ${first_seen[$fname]}"
    echo "  New     : $path"
    echo -n "Delete the NEW file? (yes/no): "
    read ans
    case "$ans" in
      yes|y|Y)
        rm -- "$path" && echo "Deleted: $path" || echo "Failed to delete: $path"
        ;;
      *)
        echo "Kept: $path"
        ;;
    esac
  else
    first_seen["$fname"]="$path"
  fi
done < <(find "$root" -type f)

