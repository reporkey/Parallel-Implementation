#!/bin/bash

number_of_run=2;
make

for input in "input_4" "input_8" "input_16" "input_32" "input_33" "input_64" "input_65" "input_128" "input_129" "input_256" "input_257" "input_512" "input_513" "input_1024" "input_1025"
do
	for program in "S_FW" "P_FW" "S_FWT" "P_FWT"
	do
		for ((i=1; i<=$number_of_run; i++))
		do
			echo "Run time: $i with $input by $program"
			./$program $input;
		done
	done
	echo ""
done

echo ""
echo "============================================================================="
echo ""

for input in "input_100" "input_500" "input_1k" "input_2k"
do
	for program in "S_FW" "P_FW" "S_FWT" "P_FWT"
	do
		for ((i=1; i<=$number_of_run; i++))
		do
			echo "Run time: $i with $input by $program"
			./$program $input;
		done
	done
	echo ""
done

echo ""
echo "============================================================================="
echo ""

for input in "input_8192" "input_8193"
do
	for program in "S_FW" "P_FW" "S_FWT" "P_FWT"
	do
		echo "$input by $program"
		./$program $input;
	done
	echo ""
done
