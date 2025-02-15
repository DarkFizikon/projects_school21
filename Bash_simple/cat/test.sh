#!/bin/bash

TEST_FILES=("test1.txt" "test2.txt")
FLAGS=("-b" "-e" "-n" "-s" "-t" "-E" "-T" "-v")

for file in "${TEST_FILES[@]}"; do
  for flag in "${FLAGS[@]}"; do
    if ! diff <(./s21_cat $flag "$file") <(cat $flag "$file"); then
      echo "Test failed for file $file with flag $flag"
    else
      echo "Test passed for file $file with $flag"
    fi
  done
done

