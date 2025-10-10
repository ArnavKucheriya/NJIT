#!/usr/bin/env bash

infile="$1"
if [[ -z "$infile" || ! -f "$infile" ]]; then
  echo "Usage: $0 <input-file>" >&2
  exit 1
fi

trim() {  # trim leading/trailing whitespace
  local s="$1"
  s="${s#"${s%%[![:space:]]*}"}"
  s="${s%"${s##*[![:space:]]}"}"
  printf '%s' "$s"
}

tmpfile="$(mktemp)"
trap 'rm -f "$tmpfile"' EXIT

while IFS= read -r line; do
  # Expect: "FirstName LastName, YYYY-MM-DD, City, Country"
  IFS=',' read -r name dob city country <<<"$line"

  name="$(trim "$name")"
  dob="$(trim "$dob")"
  city="$(trim "$city")"
  country="$(trim "$country")"

  # must contain two or more words (at least one space between word chars)
  if [[ "$city" =~ [[:alpha:]]+[[:space:]][[:alpha:]]+ ]]; then
    # Extract DOB with regex and compute age for 2023
    if [[ "$dob" =~ ^([0-9]{4})-([0-9]{2})-([0-9]{2})$ ]]; then
      byear="${BASH_REMATCH[1]}"
      age=$(( 2023 - byear ))
      printf "%d\t%s\n" "$age" "$name" >> "$tmpfile"
    fi
  fi
done < "$infile"

# Sort by age (desc)
sort -nr -k1,1 "$tmpfile" | while IFS=$'\t' read -r age name_rest; do
  printf "%s is %d\n" "$name_rest" "$age"
done

