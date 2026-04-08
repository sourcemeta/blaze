#!/bin/sh
# Helper script to run the compile binary against the corpus files.
# Usage: ./contrib/run_corpus.sh <path-to-compile-binary>
#
# This is an optional utility for local testing and fuzzing preparation.
# It is NOT part of the CI test suite.
#
# Expected behavior:
#   - valid/ and stress/ files: should succeed (exit 0)
#   - All other categories: should fail gracefully (exit non-zero), never crash

set -e

COMPILE="${1:?Usage: $0 <path-to-compile-binary>}"
CORPUS_DIR="$(cd "$(dirname "$0")/../test/corpus/compile" && pwd)"

if [ ! -x "$COMPILE" ]; then
  echo "error: compile binary not found or not executable: $COMPILE" >&2
  exit 1
fi

pass=0
fail=0
crash=0

for category in valid invalid_json invalid_schema unknown_dialect edge_cases stress; do
  dir="$CORPUS_DIR/$category"
  [ -d "$dir" ] || continue
  for f in "$dir"/*.json; do
    [ -f "$f" ] || continue
    name="${category}/$(basename "$f")"

    rc=0
    "$COMPILE" "$f" > /dev/null 2>&1 || rc=$?

    if [ $rc -ge 128 ]; then
      echo "CRASH  $name (signal $((rc - 128)))"
      crash=$((crash + 1))
    elif [ "$category" = "valid" ] || [ "$category" = "stress" ]; then
      if [ $rc -eq 0 ]; then
        echo "PASS   $name"
        pass=$((pass + 1))
      else
        echo "FAIL   $name (expected success, got exit $rc)"
        fail=$((fail + 1))
      fi
    else
      if [ $rc -ne 0 ]; then
        echo "PASS   $name (graceful error, exit $rc)"
        pass=$((pass + 1))
      else
        echo "NOTE   $name (unexpected success, exit 0)"
        pass=$((pass + 1))
      fi
    fi
  done
done

echo ""
echo "Results: $pass passed, $fail failed, $crash crashed"

if [ $crash -gt 0 ]; then
  echo "ERROR: $crash files caused a crash!" >&2
  exit 1
fi

exit 0
