all: P_algorithm P_algorithm_alt S_algorithm nodegen

P_algorithm: P_algorithm.c
	gcc -Wall -fopenmp -o P_algorithm P_algorithm.c

P_algorithm_alt: P_algorithm_alt.c
	gcc -Wall -fopenmp -o P_algorithm_alt P_algorithm_alt.c

S_algorithm: S_algorithm.cpp
	g++ -Wall -fopenmp -o S_algorithm S_algorithm.cpp

nodegen: nodegen.cpp
	g++ -Wall -o nodegen nodegen.cpp
