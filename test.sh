#!/bin/bash
set -e

run_test() {
  input_file=$1
  method=$2
  expected_output=$3

  echo "Test: $input_file ($method)"
  ./LindenShoreOA "$input_file" "$method" > output.csv

  if diff -q output.csv "$expected_output" >/dev/null; then
    echo "PASSED"
  else
    echo "FAILED"
    echo "Expected:"
    cat "$expected_output"
    echo "Actual:"
    cat output.csv
    exit 1
  fi
}

run_test tests/test_1.csv fifo tests/test_1_fifo.csv
run_test tests/test_1.csv lifo tests/test_1_lifo.csv
run_test tests/test_2.csv fifo tests/test_2_fifo.csv
run_test tests/test_2.csv lifo tests/test_2_lifo.csv
run_test tests/test_3.csv fifo tests/test_3_fifo.csv
run_test tests/test_3.csv lifo tests/test_3_lifo.csv
run_test tests/test_4.csv fifo tests/test_4_fifo.csv
run_test tests/test_4.csv lifo tests/test_4_lifo.csv

echo "All tests passed!"
