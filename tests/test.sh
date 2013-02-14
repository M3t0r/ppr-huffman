#!/bin/bash

suits="bitarray bitfile heap code"

errors=0

if [ -e tests/bitarray ]; then
    cd tests
fi

for suit in $suits; do
    ./${suit}
    result=$?
    if [ $result -gt 0 ]; then
        errors=$(($errors + $result))
        echo "Error(s) in  \"${suit}\""
    fi;
done;

echo; echo;

if [ $errors = 0 ]; then
    echo "All tests passed";
else
    echo "${errors} tests failed"
fi;
