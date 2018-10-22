#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>
#include <time.h>

#define N_MAX 1000
#define VALUE_MAX 100
#define WEIGHT_MAX 1000

int *weight;
int table_cost[N_MAX][WEIGHT_MAX];
int table_s[N_MAX][WEIGHT_MAX];
int *map;
int numproc, rank;
int knapsack_capacity, n, seed;
int *value;

void inputs(int argc, char *argv[]){
	int i;

	knapsack_capacity = atoi(argv[1])+1;
	n  = atoi(argv[2]);
	seed = atoi(argv[3]);
	srandom(seed);

	for(i=0;i<n;i++){
		value[i]=random()%VALUE_MAX;
		weight[i]=random()%(knapsack_capacity-1)+1;
	}

	for (i = 0; i < knapsack_capacity; i++){
		map[i] = i%numproc;
	}

}

void outputs(){
	int i, j;
	MPI_Status status;
	MPI_Request request;

	int table_svg[N_MAX][WEIGHT_MAX];
	if(rank != map[knapsack_capacity-1]){
		for(j=rank; j<knapsack_capacity-1; j+=numproc){
			MPI_Isend(table_s, N_MAX*WEIGHT_MAX, MPI_INT, map[knapsack_capacity-1], 0x20, MPI_COMM_WORLD, &request);
		}
	}else{

		memcpy(table_svg, table_s, N_MAX*WEIGHT_MAX);

		printf("\nResults:\n");
		printf("Knapsack max weight: %d\nNumber of items: %d\n", knapsack_capacity-1, n);
		printf("Best value: %d \n", table_cost[n-1][knapsack_capacity-1]);
		
	}
}
int max(int a, int b){
    return a > b ? a : b;
}

int main(int argc,char *argv[]) {
	int i, j, k;
	int cost_with_i, cost_without_i;
	clock_t start_time, end_time; 
	MPI_Status status;
	MPI_Request request;

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&numproc);

	value = malloc(sizeof(int)*N_MAX);
	weight =(int*)malloc(sizeof(int)*N_MAX);
	map = (int*)malloc(sizeof(int)*N_MAX);
	
	inputs(argc, argv);	
	MPI_Barrier(MPI_COMM_WORLD);

	start_time=clock(); 

	for(i=0;i<n;i++){
		// Rank computes own column
		for(j=rank; j<knapsack_capacity; j+=numproc){
			if(j - weight[i]<0)
				cost_with_i=0;

			else if(i == 0 && j-weight[i] >= 0)
				cost_with_i=value[i];

			else{
				MPI_Recv(&cost_with_i, 1, MPI_INT, map[j-weight[i]], i-1, MPI_COMM_WORLD, &status);
				cost_with_i+=value[i];
			}
			cost_without_i = (i==0) ? 0 : table_cost[i-1][j];

			table_cost[i][j] = max(cost_with_i, cost_without_i);
			table_s[i][j] = (table_cost[i][j]==cost_without_i) ? 1 : 0;
			for(k=j+1; k<knapsack_capacity; k++){
				if(k-j == weight[i+1]){
					MPI_Isend(&table_cost[i][j], 1, MPI_INT, map[k], i, MPI_COMM_WORLD, &request);
				}
			}

		}
	}

	MPI_Barrier(MPI_COMM_WORLD);
	outputs();
	end_time = clock();
	if(rank==0) printf("\nElapsed time = %lf s.\n",(double)(end_time-start_time)/CLOCKS_PER_SEC);
	 
	MPI_Finalize();
	return 0;
}


