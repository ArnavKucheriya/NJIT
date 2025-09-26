#!/bin/bash

# Problem 1: 
# 1. Prompts the user for a pathname of a directory, verifies the directory exists, and moves into that directory.
# 2. Lists all the files in the directory and displays a menu to the user to select a file.
# 3. After a file is selected, display the last ten lines of the file and ask the user if they want to display more. If the user responds "yes", display the next ten lines. Continue displaying the next ten lines at a time as long as the user responds "yes".  Stop "scrolling up" if the displaying reaches the first line of the file.

echo -n "Enter a directory path: "
read dir

if [ ! -d "$dir" ]; then
  echo "Error: '$dir' is not a directory."
  exit 1
fi

cd "$dir" || exit 1

# Build a list of regular files (non-recursive)
files=()
for f in * .*; do
  # skip . and .. and non-regular files
  [ "$f" = "." ] && continue
  [ "$f" = ".." ] && continue
  [ -f "$f" ] || continue
  files+=("$f")
done

if [ ${#files[@]} -eq 0 ]; then
  echo "No files in this directory."
  exit 0
fi

echo "Files:"
i=1
for name in "${files[@]}"; do
  echo "  $i) $name"
  i=$((i+1))
done

echo -n "Select a file number: "
read choice
# Basic numeric check
if ! [ "$choice" -ge 1 ] 2>/dev/null || [ "$choice" -gt ${#files[@]} ]; then
  echo "Invalid selection."
  exit 1
fi

file="${files[$((choice-1))]}"
if [ ! -r "$file" ]; then
  echo "File is not readable."
  exit 1
fi

total=$(wc -l < "$file")
if [ "$total" -eq 0 ]; then
  echo "(Empty file)"
  exit 0
fi

# Start from the end; offset counts how many lines we've already shown
offset=0

show_block() {
  # Show the next 10 lines moving upward (toward the start)
  # We can do this with tail-of-N then head 10.
  want=$((offset + 10))
  if [ "$want" -ge "$total" ]; then
    want="$total"
  fi
  # If want < 10 (very short file), head handles it
  tail -n "$want" -- "$file" | head -n 10
}

echo "---- Showing last 10 lines of '$file' ----"
show_block

while true; do
  offset=$((offset + 10))
  if [ "$offset" -ge "$total" ]; then
    echo "(Reached the start of the file.)"
    break
  fi
  echo -n "Display 10 more earlier lines? (yes/no): "
  read ans
  case "$ans" in
    yes|y|Y)
      show_block
      ;;
    *)
      echo "Done."
      break
      ;;
  esac
done

