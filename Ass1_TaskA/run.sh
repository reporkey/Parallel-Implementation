#!/bin/bash

number_of_run=5;
make

for input in "input_512" "input_1024" "input_8192"
do
	for program in "P_algorithm" "P_algorithm_new" "S_algorithm"
	do
		for ((i=1; i<=$number_of_run; i++))
		do
			echo "Run time: $i with $input by $program"
			./$program $input;
			echo ""
		done
	done
done
