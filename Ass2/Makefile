all: s_dp Knapsack_mpi Knapsack_mpi_openmp gen

s_dp: s_dp.cpp
	mpic++ -Wall -fopenmp -std=c99 -O3 -o s_dp s_dp.cpp

Knapsack_mpi: Knapsack_mpi.cpp
	mpic++ -Wall -fopenmp -std=c99 -O3 -o Knapsack_mpi Knapsack_mpi.cpp

Knapsack_mpi_openmp: Knapsack_mpi_openmp.cpp
	mpic++ -Wall -fopenmp -std=c99 -O3 -o Knapsack_mpi_openmp Knapsack_mpi_openmp.cpp

gen: gen.cpp
	g++ -Wall -O3 -o gen gen.cpp

clean:
	rm s_dp Knapsack_mpi Knapsack_mpi_openmp gen
