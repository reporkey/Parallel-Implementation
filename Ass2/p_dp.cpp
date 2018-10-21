// Input:
// Values (stored in array v)
// Weights (stored in array w)
// Number of distinct items (n)
// Knapsack capacity (W)
// NOTE: The array "v" and array "w" are assumed to store all relevant values starting at index 1.

// assume that problem size is power of 2.

// bottom/up parallel prefix sum


#include <cstdio>
#include <cstdlib>
#include <math.h>
// #include <mpi.h>

// mpicc -fopenmp p_dp.cpp -o p_dp

int n = 4+1;
int W = 10;

void prefix(int i, int* v, int* w, int m[][10]);
void myprint(int* v, int* w, int m[][10]);

void test(int i, int* a){
	a[i] += a[i-1];
}

int main (int argc, char *argv[]) {

	int v[] = {0, 2, 1, 5, 3};
	int w[] = {0, 3, 2, 5, 2};
	int m[n][10];
	int a[] = {0, 1, 2, 3, 4};

//	if(argc!=2){
//        printf("The path to the input file is not specified as a parameter.\n");
//        return -1;
//    }
	// MPI init
//	int rank = 0, comm_sz = 0;
//	MPI_Init(&argc, &argv);
//	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);


	printf("\n");
	printf("i ");
	for (int i=0; i<n; i++){
		printf("%d ", i);
	}
	printf("\n");	
	printf("v ");
	for (int i=0; i<n; i++){
		printf("%d ", v[i]);
	}
	printf("\n");
	printf("w ");
	for (int i=0; i<n; i++){
		printf("%d ", w[i]);
	}
	printf("\n\n");


	
	// the first row is 0, since index is started from 1.
	for (int j=0; j<W; j++){
		m[0][j] = 0;
	}
	
	// f = 2 ^ depth where f <= num of items
	for (int f=2; f<=n; f*=2){
		printf("f = %d\n", f);
		myprint(v, w, m);
		// operate each in the same depth
		for (int i=f; i<=n; i+=f){
//			test(i, a);
			prefix(i, v, w, m);
		}
	}


  return EXIT_SUCCESS;
}

void myprint(int* v, int* w, int m[][10]){
	// test printf
	

	
	printf("m  ");
	for (int j=0; j<W; j++){
		printf("%d ", j);
	}
	printf("\n");

	for (int i=0; i<n; i++){
		printf("%d  ", i);
		for (int j=0; j<W; j++){
			printf("%d ", m[i][j]);
		}
		printf("\n");
	}
}

void prefix(int i, int* v, int* w, int m[][10]){
	// block of prefix oporation. m[i] = f(m[i-1])
	for (int j=0; j<W; j++){
		if (w[i] > j){
			m[i][j] = m[i-1][j];
		}else {
			int temp1 = m[i-1][j];
			int temp2 = m[i-1][j-w[i]]+v[i];
			m[i][j] = ((temp1 > temp2) ? temp1 : temp2);
		}
	}
}
