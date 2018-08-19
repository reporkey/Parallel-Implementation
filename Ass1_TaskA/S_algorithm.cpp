#include <cstdio>
#include <omp.h>

using namespace std;

#define MAX 10000
#define NOT_CONNECTED -1

int distance[MAX][MAX];

int nodesCount;

void Initialize(){
    for (int i=0;i<MAX;++i){
        for (int j=0;j<MAX;++j){
            distance[i][j]=NOT_CONNECTED;

        }
        distance[i][i]=0;
    }
}


int main(int argc, char** argv){
    double timeBegin, timeInitial, timeRead, timeCalculate, timeCompare, timeEnd;
	timeBegin = omp_get_wtime();

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
	timeInitial = omp_get_wtime();

	int a, b, c;
    fscanf(in_file,"%d", &nodesCount);
    while(fscanf(in_file,"%d %d %d", &a, &b, &c)!= EOF){
        if ( a > nodesCount || b > nodesCount){
            printf("Vertex index out of boundary.");
            return -1;
        }
        distance[a][b]=c;
    }
	timeRead = omp_get_wtime();

    //Floyd-Warshall
    for (int k=1;k<=nodesCount;++k){
        for (int i=1;i<=nodesCount;++i){
            if (distance[i][k]!=NOT_CONNECTED){
                for (int j=1;j<=nodesCount;++j){
                    if (distance[k][j]!=NOT_CONNECTED && (distance[i][j]==NOT_CONNECTED || distance[i][k]+distance[k][j]<distance[i][j])){
                        distance[i][j]=distance[i][k]+distance[k][j];
                    }
                }
            }
        }
    }
    int diameter=-1;
	timeCalculate = omp_get_wtime();

    //look for the most distant pair
    for (int i=1;i<=nodesCount;++i){
        for (int j=1;j<=nodesCount;++j){
            if (diameter<distance[i][j]){
                diameter=distance[i][j];
                //printf("%d-%d-%d\n", i, diameter, j);
            }
        }
    }
	timeCompare = omp_get_wtime();

    printf("Diameter = %d\n", diameter);
	timeEnd = omp_get_wtime();
	printf("Initialing: \t%f\n", timeInitial-timeBegin);
	printf("Reading: \t%f\n", timeRead-timeInitial);
	printf("Calculating: \t%f\n", timeCalculate-timeRead);
	printf("Comparing: \t%f\n", timeCompare-timeCalculate);
	printf("Total: \t\t%f\n", timeEnd-timeBegin);
	
    return 0;

}
