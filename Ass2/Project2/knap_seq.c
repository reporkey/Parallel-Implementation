
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N 1001
#define CAPACITY_MAX 1001
#define VALUE_MAX 100

int n; // number of items
int capacity; 
int weight[N]; 
int value[N]; 
int knapsack[N+1][CAPACITY_MAX]; 
int seed;

void inputs(int argc, char *argv[]);

int main(int argc,char *argv[]) {
	int i, j;

	clock_t start_time, end_time;  
	inputs(argc, argv);

	start_time=clock();

	for( i=0; i<=n; i++ ){
		for( j=0; j<capacity; j++ ) {

			if( i==0 || j==0 ){
				knapsack[i][j]= 0;

			} else if( weight[i-1] <= j ){

				int one = value[i-1] + knapsack[i-1][j-weight[i-1]];
				int two = knapsack[i-1][j];

				if(one > two) {
					knapsack[i][j] = one;
				} else {
					knapsack[i][j] = two;
				}          
			} else {
				knapsack[i][j] = knapsack[i-1][j];
			}

		}

	}

	end_time = clock(); 

	printf("\nKnapsack max weight: %d\nNumber of items: %d\n", capacity-1, n);
	printf("Best value: %d \n", knapsack[n][capacity-1]);
	printf("\nElapsed time = %lf s.\n",(double)(end_time-start_time)/CLOCKS_PER_SEC);

	
	return 0;
}


void inputs(int argc, char *argv[]){
	int i;

	capacity = atoi(argv[1])+1;
	n  = atoi(argv[2]);
	seed = atoi(argv[3]);

	srandom(seed);
	for(int i=0;i<n;i++){
		value[i]=random()%VALUE_MAX;
		weight[i]=random()%(capacity-1)+1;
	}
}
