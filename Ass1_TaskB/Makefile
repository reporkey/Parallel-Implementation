P=mandelbrot
flag=-O3 -lm -std=c++11

all: $(P) $(P)_opti $(P)_opti+openmp $(P)_opti+mpi_reduction $(P)_opti+mpi_reduction+multithread

$(P): $(P).cpp
	gcc -Wall -fopenmp $(P).cpp -o $(P) $(flag)

$(P)_opti: $(P)_opti.cpp
	gcc -Wall -fopenmp $(P)_opti.cpp -o $(P)_opti $(flag)

$(P)_opti+openmp: $(P)_opti+openmp.cpp
	gcc -Wall -fopenmp $(P)_opti+openmp.cpp -o $(P)_opti+openmp $(flag)

$(P)_opti+mpi_reduction: $(P)_opti+mpi_reduction.cpp
	mpic++ -Wall -fopenmp $(P)_opti+mpi_reduction.cpp -o $(P)_opti+mpi_reduction $(flag)

$(P)_opti+mpi_reduction+multithread: $(P)_opti+mpi_reduction+multithread.cpp
	mpic++ -Wall -fopenmp $(P)_opti+mpi_reduction+multithread.cpp -o $(P)_opti+mpi_reduction+multithread $(flag)



