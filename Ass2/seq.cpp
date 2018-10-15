// Input:
// Values (stored in array v)
// Weights (stored in array w)
// Number of distinct items (n)
// Knapsack capacity (W)
// NOTE: The array "v" and array "w" are assumed to store all relevant values starting at index 1.


#include <cstdio>
#include <cstdlib>

int n = 4;
int W = 10;

int main (int argc, char *argv[]) {

	int v[] = {0, 2, 1, 5};
	int w[] = {0, 3, 2, 5};
	int m[n][W];

	// the first row is 0, since index is started from 1.
	for (int j=0; j<W; j++){
		m[0][j] = 0;
	}

	for (int i=1; i<n; i++){
		for (int j=0; j<W; j++){
			if (w[i] > j){
				m[i][j] = m[i-1][j];
			}else {
				m[i][j] = ((m[i-1][j] > m[i-1][j-w[i]]+v[i]) ? m[i-1][j] : m[i-1][j-w[i]]+v[i]);
			}
		}
	}

	// test printf
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


  return EXIT_SUCCESS;
}


