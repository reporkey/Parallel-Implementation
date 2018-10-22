

Sequence:
1. Compile: 
	$ gcc knap_seq.c -o knap_seq

2. Run: 
	$  ./knap_seq 1000 1000 5


MPI:
1. Compile: 
	$ mpicc knap_MPI.c -o knap_MPI

2. Run:
	$ mpiexec -n 20 ./knap_MPI 1000 1000 5


OpenMP:
1. Compile:
	$ gcc -fopenmp knap_OpenMP.c -o knap_OpenMP
2. Run:
	$ ./knap_OpenMP 1000 1000 5