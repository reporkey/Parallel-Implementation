all: P_algorithm S_algorithm nodegen

P_algorithm: P_algorithm.c
	gcc -Wall -fopenmp -o P_algorithm P_algorithm.c

S_algorithm: S_algorithm.cpp
	g++ -Wall -fopenmp -o S_algorithm S_algorithm.cpp

nodegen: nodegen.cpp
	g++ -Wall -o nodegen nodegen.cpp
