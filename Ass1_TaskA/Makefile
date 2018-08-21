all: P_algorithm P_algorithm_new S_algorithm nodegen

P_algorithm: P_algorithm.c
	gcc -Wall -fopenmp -std=c99 -o P_algorithm P_algorithm.c

P_algorithm_new: P_algorithm_new.c
	gcc -Wall -fopenmp -std=c99 -o P_algorithm_new P_algorithm_new.c

S_algorithm: S_algorithm.cpp
	g++ -Wall -fopenmp -o S_algorithm S_algorithm.cpp

nodegen: nodegen.cpp
	g++ -Wall -o nodegen nodegen.cpp
