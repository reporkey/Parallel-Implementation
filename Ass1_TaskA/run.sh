#!/bin/bash

number_of_run=10;
make
for program in "S_FW" "P_FW" "S_FWT" "P_FWT"
do
	echo ""
	echo "$program"
	echo ""
	for input in "input_4" "input_8" "input_16" "input_32" "input_33" "input_50" "input_64" "input_65" "input_100" "input_128" "input_129" "input_256" "input_257" "input_300" "input_500" "input_512" "input_513" "input_800" "input_1k" "input_1024" "input_1025" "input_1500" "input_1700" "input_2k" "input_2500" 
	do
		for ((i=1; i<=$number_of_run; i++))
		do
			./$program $input;
		done
	done
done
