#!/bin/bash

number_of_run=10;
make
for program in "s_dp" "Knapsack_mpi" "Knapsack_mpi_openmp"
do
	echo ""
	echo "$program"
	echo ""
	for input in "100_1000.txt" "100_5000.txt" "100_50000.txt" "500_5000.txt" "1000_5000.txt" "1000_10000.txt" "1000_50000.txt" "5000_5000.txt" "5000_10000.txt" "5000_50000.txt" "10000_5000.txt" "10000_10000.txt" "10000_100000.txt" "50000_5000.txt" "50000_50000.txt" "100000_10000.txt"
	do
		for ((i=1; i<=$number_of_run; i++))
		do
			mpiexec $program $input;
		done
	done
done

for program in "s_dp"
do
	echo ""
	echo "$program"
	echo ""
	for input in "100_1000.txt" "100_5000.txt" "100_50000.txt" "500_5000.txt" "1000_5000.txt" "1000_10000.txt" "1000_50000.txt" "5000_5000.txt" "5000_10000.txt" "5000_50000.txt" "10000_5000.txt" "10000_10000.txt" "10000_100000.txt" "50000_5000.txt" "50000_50000.txt" "100000_10000.txt"
	do
		for ((i=1; i<=$number_of_run; i++))
		do
			./$program $input;
		done
	done
done
