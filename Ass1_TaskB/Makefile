P=mandelbrot
flag=-O3 -lm -std=c++11

all: $(P) $(P)_opti $(P)_opti+openmp $(P)_opti+mpi $(P)_opti+mpi+multithread

$(P): $(P).cpp
	gcc -Wall -fopenmp $(P).cpp -o $(P) $(flag)

$(P)_opti: $(P)_opti.cpp
	gcc -Wall -fopenmp $(P)_opti.cpp -o $(P)_opti $(flag)

$(P)_opti+openmp: $(P)_opti+openmp.cpp
	gcc -Wall -fopenmp $(P)_opti+openmp.cpp -o $(P)_opti+openmp $(flag)

$(P)_opti+mpi: $(P)_opti+mpi.cpp
	mpic++ -Wall -fopenmp $(P)_opti+mpi.cpp -o $(P)_opti+mpi $(flag)

$(P)_opti+mpi+multithread: $(P)_opti+mpi+multithread.cpp
	mpic++ -Wall -fopenmp $(P)_opti+mpi+multithread.cpp -o $(P)_opti+mpi+multithread $(flag)



