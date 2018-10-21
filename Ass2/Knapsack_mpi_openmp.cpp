// Input:
// Values (stored in array v)
// Weights (stored in array w)
// Number of distinct items (n)
// Knapsack capacity (W)
// NOTE: The array "v" and array "w" are assumed to store all relevant values starting at index 1.


#include <cstdio>
#include <cstdlib>
#include <math.h>
#include <mpi.h>
#include <omp.h>

// Compile
// mpic++ Knapsack_mpi_openmp.cpp -o Knapsack_mpi_openmp

void work(int i, int j, int* v, int* w, int** m);
void myprint(int* v, int* w, int** m);

int n, W, newW;

int main (int argc, char *argv[]) {

	int rank = 0, comm_sz = 0;

	if(argc!=2){
        printf("The path to the input file is not specified as a parameter.\n");
        return -1;
    }

	// read input
	FILE *f;
	f=fopen(argv[1], "r");
	if (f == NULL) { 
        fprintf(stderr, "\nError opend file\n"); 
        exit (1); 
    }
	fscanf(f, "%d %d", &n, &W);
	int v[n+1], w[n+1], i=1;
	v[0] = 0;
	w[0] = 0;
	while (fscanf(f,"%d %d", &(v[i]), &(w[i]))==2) {
		i++; 
	}

	// MPI init
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

	// new W to fit num(p): newW = num(p) * int >= W
	// newW includes index 0
	newW = W+1;
	if ((W+1) % comm_sz > 0) newW = (comm_sz) * ((W+1) / comm_sz + 1);

	int recvbuf[newW/comm_sz];

	// allocate memory space and initialize value
	int** m = NULL;
	if ( (m = (int**) malloc((n+1)*sizeof(int*))) == NULL){
		printf("Malloc error.\n");
		return EXIT_FAILURE;
	}
	for (int i=0; i<=n; i++){
		if ( (m[i] = (int*) malloc(newW*sizeof(int))) == NULL){
			printf("Malloc error.\n");
			return EXIT_FAILURE;
		}
		for (int j=0; j<newW; j++){
			m[i][j] = 0;
		}
	}
	
	int root = 0;
  	int sendcount = newW / comm_sz;
  	int recvcount = newW / comm_sz;
	double t1,t2;
	t1=MPI_Wtime();
	for (int i=1; i<=n; i++){
		// scatter works to all processors
  		MPI_Scatter(m[i], sendcount, MPI_INT, recvbuf, recvcount, MPI_INT, root, MPI_COMM_WORLD);
		
		// do works
		int jStart = rank*recvcount;
		#pragma omp parallel
		for (int j=0; j<recvcount; j++){
			work(i, jStart+j, v, w, m);
		}
		
		// share results
		MPI_Allgather (&(m[i][jStart]), sendcount, MPI_INT, m[i], recvcount, MPI_INT, MPI_COMM_WORLD);

		// free
		if (i>=2) free(m[i-2]);
	}

	MPI_Finalize();
	t2=MPI_Wtime();

	if (rank == 0) {
		printf("\n");
		printf("n = %d\n", n);
		printf("W = %d\n", W);
		printf("comm_sz = %d\n", comm_sz);
		printf("newW = %d\n", newW);
//		myprint(v, w, m);
		printf("Max total value: %d.\n", m[n][W]);
		printf("\nTotal time = %f sec\n",t2-t1);
	}
	free(m[n-1]);
	free(m[n]);
	return EXIT_SUCCESS;
}

void work(int i, int j, int* v, int* w, int** m){
	if (w[i] > j){
		m[i][j] = m[i-1][j];
	}else {
		int temp1 = m[i-1][j];
		int temp2 = m[i-1][j-w[i]]+v[i];
		m[i][j] = ((temp1 > temp2) ? temp1 : temp2);
	}
}

void myprint(int* v, int* w, int** m){
	// test printf
	printf("\n");
	printf("i ");
	for (int i=0; i<=n; i++){
		printf("%d ", i);
	}
	printf("\n");	
	printf("v ");
	for (int i=0; i<=n; i++){
		printf("%d ", v[i]);
	}
	printf("\n");
	printf("w ");
	for (int i=0; i<=n; i++){
		printf("%d ", w[i]);
	}
	printf("\n\n");

/*	printf("m  ");
	for (int j=0; j<newW; j++){
		printf("%d ", j);
	}
	printf("\n");

	for (int i=0; i<=n; i++){
		printf("%d  ", i);
		for (int j=0; j<newW; j++){
			printf("%d ", m[i][j]);
		}
		printf("\n");
	}
*/
}
