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

tests="1_zeichen.txt blz.csv donau.txt kartoffelpuffer.txt PPR_V01.pdf franz.txt \
		leer.txt lorem_ipsum_1000_woerter.txt quick_fox.txt 1_in.txt 2_ab.txt \
		3_leere.txt 4_1Byte.txt 5_0-255.txt 6_8Nutzbits.txt 7_in8Bits.txt 8_splint.exe \
		9_hpr3_ws0910.pdf 10_in.txt"

i=1
for fall in $tests; do
	echo
	#start_time=`date +%s`
	#echo "Testfall ${i}: ${fall}"
	../ppr-huffman -c ${fall}
	../ppr-huffman -d ${fall}".hc"
    diff ${fall} ${fall}".hc.hd"
    result=$?
    if [ $result != 0 ]; then
        errors=$(($errors + $result))
        ls -lh ${fall} | awk  '{printf("original:\t%s\n", $5);}'
    	ls -lh ${fall}".hc" | awk  '{printf("komprimiert:\t%s\n", $5);}'
        ls -lh ${fall}".hc.hd" | awk  '{printf("dekomprimiert:\t%s\n", $5);}'
        echo -e "${RED}FAILED:${NORMAL} ${fall}"
    else
    	echo -e "${GREEN}PASSED:${NORMAL} ${fall}"
    fi;
    #echo "Took $(expr `date +%s` - $start_time)s"
    ((i++))
done;

rm *.hc*

cd ../
make clean
cd tests

exit $errors
