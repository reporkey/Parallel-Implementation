#include <stdio.h>
#include <string.h>
#include <omp.h>

#define MAX 10000
#define NOT_CONNECTED -1

int distance[MAX][MAX];
int nodesCount, edgesCount;

void Initialize(){
    for (int i=0;i<MAX;++i){
        for (int j=0;j<MAX;++j){
            distance[i][j]=NOT_CONNECTED;
        }
        distance[i][i]=0;
    }
}

int main(int argc, char** argv){
    double timeRead, timeCalculate;

    if(argc!=2){
        printf("The path to the input file is not specified as a parameter.\n");
        return -1;
    }
    FILE *in_file  = fopen(argv[1], "r");
    if (in_file  == NULL){
        printf("Can't open file for reading.\n");
        return -1;
    }
	
	Initialize();

	int a, b, c;
    if(fscanf(in_file,"%d %d", &nodesCount, &edgesCount) == EOF){
		printf("Error\n");
		return 1;
	}
    while(fscanf(in_file,"%d %d %d", &a, &b, &c)!= EOF){
        if ( a > nodesCount || b > nodesCount){
            printf("Vertex index out of boundary.");
            return -1;
        }
        distance[a][b]=c;
    }
	timeRead = omp_get_wtime();

    //Floyd-Warshall
	#pragma omp parallel for collapse(2) shared(distance)
    for (int k=1;k<=nodesCount;++k){
        for (int i=1;i<=nodesCount;++i){
			#pragma omp flush(distance)
            if (distance[i][k]!=NOT_CONNECTED){
                for (int j=1;j<=nodesCount;++j){
					#pragma omp flush(distance)
                    if (distance[i][k]!=NOT_CONNECTED && distance[k][j]!=NOT_CONNECTED && (distance[i][j]==NOT_CONNECTED || distance[i][j]>distance[i][k]+distance[k][j])){
	//					#pragma omp critical(calc)
                       	distance[i][j]=distance[i][k]+distance[k][j];
	//					#pragma omp flush(distance)
                    }
                }
            }
        }
    }
    int diameter=-1;
	timeCalculate = omp_get_wtime();

    //look for the most distant pair
//	#pragma omp parallel for collapse(2) shared(diameter)
    for (int i=1;i<=nodesCount;++i){
        for (int j=1;j<=nodesCount;++j){
			if (diameter<distance[i][j]){
//		        #pragma omp critical(search)
		      	diameter=distance[i][j];
//				#pragma omp flush(diameter)
			}
        }
    }

    printf("Diameter = %d\n", diameter);
	printf("Calculating: \t%f\n", timeCalculate-timeRead);
	
    return 0;

}
