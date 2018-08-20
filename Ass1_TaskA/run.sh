#!/bin/bash

number_of_run=2;
make

for input in "input_sample" "input_50" "input_100" "input_500" "input_1k" "input_2k" "input_5k" "input_10k"
do
	echo $input
	echo ""
	for ((i=1; i<=$number_of_run; i++))
	do
		echo "Run time: $i"
		
		./P_algorithm $input;
		echo ""		
	done
done
