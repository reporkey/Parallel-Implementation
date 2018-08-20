#!/bin/bash

number_of_run=2;
make

for input in "input_1k" "input_2k"
do
	for program in "P_algorithm" "S_algorithm"
	do
		for ((i=1; i<=$number_of_run; i++))
		do
			echo "Run time: $i with $input by $program"
			./$program $input;
			echo ""
		done
	done
done
