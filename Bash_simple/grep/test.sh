#!/bin/bash

S21_GREP=./s21_grep
ORIGINAL_GREP=grep

TEST_CASES=(
  "-e as test1.txt"
  "-i as test1.txt"
  "-v as test1.txt"
  "-c as test1.txt"
  "-l as test1.txt"
  "-n as test1.txt"
  "-h as test1.txt"
 # "-s nonexistent.txt"
 # "-f patterns.txt test1.txt"
  "-e as test1.txt test2.txt"
  "-i as test1.txt test2.txt"
  "-v as test1.txt test2.txt"
  "-c as test1.txt test2.txt"
  "-l as test1.txt test2.txt"
  "-n as test1.txt test2.txt"
  "-h as test1.txt test2.txt"
 # "-s pattern.txt"
 # "-f patterns.txt test2.txt"
  "-iv asd test1.txt"
  "-iv asd test1.txt test2.txt"
  "-i -e asd test1.txt"
  "-i -e asd test1.txt test2.txt"
  "-c asdfadadsfascv test1.txt"
  "-c as ../grep"
)

for test_case in "${TEST_CASES[@]}"; do
  echo "Running test: $test_case"
  $ORIGINAL_GREP $test_case > original_output.txt 2>&1
  $S21_GREP $test_case > s21_output.txt 2>&1
  if diff -q original_output.txt s21_output.txt > /dev/null; then
    echo "Test passed"
  else
    echo "Test failed"
    #echo "Original:"
    #cat original_output.txt
    #echo "S21:"
    #cat s21_output.txt
  fi
done

rm -f original_output.txt s21_output.txt