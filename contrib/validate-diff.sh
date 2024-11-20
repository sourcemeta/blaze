#!/bin/sh

set -o errexit
set -o nounset

# To easily diff JSONL output from multiple runs of `validate.cc`

usage() {
  echo "Usage $0 <left.txt> <right.txt>" 1>&2
  exit 1
}

if [ "$#" -lt 2 ]
then
  usage
fi

LEFT="$1"
RIGHT="$2"

echo "Comparing $LEFT against $RIGHT"

extract_ns() {
  echo "$1" | awk -F' ' '{print $2}' | sed 's/ns//'
}

while IFS= read -r line_left && IFS= read -r line_right <&3
do
  row1="$(echo "$line_left" | awk '{print $1}')"
  row2="$(echo "$line_right" | awk '{print $1}')"

  if [ "$row1" != "$row2" ]
  then
    echo "error: row mismatch ($row1 vs $row2)"
    exit 1
  fi

  ns_left="$(extract_ns "$line_left")"
  ns_right="$(extract_ns "$line_right")"
  diff="$(awk -v ns_left="$ns_left" -v ns_right="$ns_right" 'BEGIN {
      diff = (ns_left - ns_right) / ((ns_left + ns_right) / 2) * 100
      printf "%.2f", diff
  }')"

  printf "%s %sns|%sns %s%%\n" "$row1" "$ns_left" "$ns_right" "$diff"
done < "$LEFT" 3< "$RIGHT"
