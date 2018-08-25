#!bin/bash

number_of_run=2;
make

for input in "input_512" "input_513" "input_1024" "input_1025"
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
