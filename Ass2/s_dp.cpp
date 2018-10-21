// Input:
// Values (stored in array v)
// Weights (stored in array w)
// Number of distinct items (n)
// Knapsack capacity (W)
// NOTE: The array "v" and array "w" are assumed to store all relevant values starting at index 1.

//#include<mpi.h>
#include <cstdio>
#include <cstdlib>

int n = 4+1;
int W = 10;
void myprint(int* v, int* w, int m[][11]);
int main (int argc, char *argv[]) {

	int v[] = {0, 1, 2, 3, 4};
	int w[] = {0, 4, 1, 3, 2};
	int m[n][11];

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
	for (int j=0; j<=W; j++){
		m[0][j] = 0;
	}
	
//	double t1,t2;
//	t1=MPI_Wtime();
	for (int i=1; i<n; i++){
		for (int j=0; j<=W; j++){
			if (w[i] > j){
				m[i][j] = m[i-1][j];
			}else {
				int temp1 = m[i-1][j];
				int temp2 = m[i-1][j-w[i]]+v[i];
				m[i][j] = ((temp1 > temp2) ? temp1 : temp2);
			}
		}
	}
//	t2=MPI_Wtime();
	
	myprint(v, w, m);
//	printf("\nTotal time = %f sec\n",t2-t1);
	return EXIT_SUCCESS;
}

void myprint(int* v, int* w, int m[][11]){

	// test printf
	printf("\n");
	printf("m  ");
	for (int j=0; j<=W; j++){
		printf("%d ", j);
	}
	printf("\n");

	for (int i=0; i<n; i++){
		printf("%d  ", i);
		for (int j=0; j<=W; j++){
			printf("%d ", m[i][j]);
		}
		printf("\n");
	}
}

void work(int i, int j, int* v, int* w, int m[][11]){
	if (w[i] > j){
		m[i][j] = m[i-1][j];
	}else {
		int temp1 = m[i-1][j];
		int temp2 = m[i-1][j-w[i]]+v[i];
		m[i][j] = ((temp1 > temp2) ? temp1 : temp2);
	}
}
