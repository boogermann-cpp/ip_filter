#!/bin/sh

test_input="../test/data/ip_filter.tsv"
test_output="Testing/test_output.txt"
expected_output="../test/data/ip_filter.tst"
application_path="src/ip_filter"

rm -f $test_output

cat $test_input | $application_path >> $test_output
#$application_path $test_input > $test_output
printf "End-to-end test: "
if cmp --silent $expected_output $test_output; then
    printf "Test passed!\n"
    exit 0
else
    printf "Test failed!\n"
    diff $expected_output $test_output
    exit 1
fi

