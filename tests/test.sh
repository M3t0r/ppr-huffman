#!/bin/bash

NORMAL="\033[0m"
GREEN="\033[0;32m"
RED="\033[0;31m"
YELLOW="\033[0;33m"

suits="bitarray bitfile heap code frequency codebuch diffs.sh"

errors=0

cd tests

for suit in $suits; do
	if [ ! -e ./${suit} ]; then
		echo -e ${YELLOW}"Warning: Testsuit ${suit} does not exist! Skipping"${NORMAL}
	else
    	./${suit}
    	result=$?
    	if [ $result != 0 ]; then
        	errors=$(($errors + $result))
        	echo -e ${RED}"Error(s) in  \"${suit}\""${NORMAL}
    	fi;
    fi;
done;

echo; echo;

if [ $errors = 0 ]; then
    echo -e ${GREEN}"All tests passed"${NORMAL}
else
    echo -e ${RED}"${errors} tests failed"${NORMAL}
fi;
