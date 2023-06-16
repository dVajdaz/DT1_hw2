#!/bin/bash

TESTS_TO_RUN=100
EXECUTABLE=./a

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

shopt -s nullglob
FAILED_TESTS=""

for i in inFiles/test*.in
do
	if [ ${i//[^0-9]/} -gt $TESTS_TO_RUN ]; then
		continue
	fi
	
	printf "test $i >>>  "
	$EXECUTABLE < $i > outFiles/test${i//[^0-9]/}.result

	dos2unix outFiles/test${i//[^0-9]/}.out
	dos2unix outFiles/test${i//[^0-9]/}.result

	diff outFiles/test${i//[^0-9]/}.out outFiles/test${i//[^0-9]/}.result

	if [ $? -eq 0 ]
	then
		printf "Test: ${GREEN}pass${NC},   "
	else
		printf "Test: ${RED}fail${NC},   "
		FAILED_TESTS+='-'
		FAILED_TESTS+='F'
	fi


done

if [ -z ${FAILED_TESTS} ]; then
	printf "\n${GREEN} All tests passed :)${NC}\n\n"
else
	printf "\n${RED} Failed ${FAILED_TESTS}${NC} tests.\n\n"
fi
