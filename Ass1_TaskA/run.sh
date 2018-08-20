#!/bin/sh

flag="-Wall -fopenmp -o"
inputFile="input1"

gcc $flag P_algorithm P_algorithm.c

./P_algorithm
