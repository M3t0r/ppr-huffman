#!/bin/bash

NORMAL="\033[0m"
GREEN="\033[0;32m"
RED="\033[0;31m"

if [ ! -f ../ppr-huffman ];
then
    cd ../
    make
    cd tests
fi

tests=`ls *.txt`

for fall in $tests; do
	../ppr-huffman -c ${fall}
	../ppr-huffman -d ${fall}".hc"
    diff ${fall} ${fall}".hc.hd"
    result=$?
    if [ $result != 0 ]; then
        errors=$(($errors + $result))
        echo -e ${RED}"FAILED:"${NORMAL}" ${fall}"
    else
    	echo -e ${GREEN}"PASSED:"${NORMAL}" ${fall}"
    fi;
done;

rm *.hc*

cd ../
make clean
cd tests
