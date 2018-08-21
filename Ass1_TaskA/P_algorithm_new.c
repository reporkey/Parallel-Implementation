#include <stdio.h>
#include <string.h>
#include <omp.h>

#define MAX 10000
#define NOT_CONNECTED -1

#define L 32
#define U 32

int D[MAX][MAX];


int nodesCount, edgesCount;

void Initialize(){
	#pragma omp parallel for
    for (int i=0;i<MAX;++i){
        for (int j=0;j<MAX;++j){
            D[i][j]=NOT_CONNECTED;

        }
        D[i][i]=0;
    }
}

void FWI(int Ai, int Aj, int Bi, int Bj, int Ci, int Cj){
	for (int k=1; k<=L; k++){
		for (int i=1; i+U<=L+1; i+=U){
			for (int j=1; j+U<=L+1; j+=U){

				// inner loop
				for (int x=i; x<i+U; x++){
					for (int y=j; y<j+U; y++){
						if (D[Ai+x][Aj+k]!=NOT_CONNECTED && D[Bi+k][Bj+y]!=NOT_CONNECTED && (D[Ci+x][Cj+y]==NOT_CONNECTED || D[Ci+x][Cj+y]>D[Ai+x][Aj+k]+D[Bi+k][Bj+y])){
				        	D[Ci+x][Cj+y] = D[Ai+x][Aj+k] + D[Bi+k][Bj+y];
				        }
					}
				}
			}
		}
	}
}

void FWIabc(int Ai, int Aj, int Bi, int Bj, int Ci, int Cj){
//	#pragma omp parallel for collapse(3)
	for (int i=1; i<=L-U+1; i+=U){
		for (int j=1; j<=L-U+1; j+=U){
			for (int k=1; k<=L-U+1; k+=U){
				
				// inner loop		
				for (int z=k; z<k+U; z++){
					for (int x=i; x<i+U; x++){
						for (int y=j; y<j+U; y++){
							if (D[Ai+x][Aj+z]!=NOT_CONNECTED && D[Bi+z][Bj+y]!=NOT_CONNECTED && (D[Ci+x][Cj+y]==NOT_CONNECTED || D[Ci+x][Cj+y]>D[Ai+x][Aj+z]+D[Bi+z][Bj+y])){
						    	D[Ci+x][Cj+y] = D[Ai+x][Aj+z] + D[Bi+z][Bj+y];
						    }
						}
					}
				}
			}
		}
	}
}

void FWT(){
	int M = nodesCount / L; //tilesCount
	printf("nodes: %d\t M: %d\t L: %d\t U: %d \n", nodesCount, M, L, U);
	for (int k=0; k<M; k++){
		// phase 1, itself
		// FWI(kk, kk, kk, L);
		FWI(k*L, k*L, k*L, k*L, k*L, k*L);
		
		// phase 2, in a row
		for (int j=0; j<M; j++){
			// FWI(kk, kj, kj, L);
			if (j!=k){
				FWI(k*L, k*L, k*L, j*L, k*L, j*L);
			}
		}
		// phase 3, in a colunm
		for (int i=0; i<M; i++){
			// FWI(ik, kk, ik, L);
			if (i!=k){
				FWI(i*L, k*L, k*L, k*L, i*L, k*L);
			}
		}
		// phase 4, others
		#pragma omp parallel for collapse(2)
		for (int i=0; i<M; i++){
			for (int j=0; j<M; j++){
				// FWIabc(ik, kj, ij, L);
				if (i!=k && j!=k){
					FWIabc(i*L, k*L, k*L, j*L, i*L, j*L);
				}
			}
		}
	}
}

int main(int argc, char** argv){
    double timeBegin, timeRead, timeCalculate, timeCompare, timeEnd;
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

	int a, b, c;
    fscanf(in_file,"%d %d", &nodesCount, &edgesCount);
    while(fscanf(in_file,"%d %d %d", &a, &b, &c)!= EOF){
        if ( a > nodesCount || b > nodesCount){
            printf("Vertex index out of boundary.");
            return -1;
        }
        D[a][b]=c;
    }

	// comtuting begin
	timeRead = omp_get_wtime();
		
	FWT();

	// For else nodes
	//#pragma omp parallel for collapse(2) shared(D)
 /*   for (int k=1;k<=nodesCount;k++){
        for (int i=M*L;i<=nodesCount;i++){
        	for (int j=M*L;j<=nodesCount;j++){
            	if (D[i][k]!=NOT_CONNECTED && D[k][j]!=NOT_CONNECTED && (D[i][j]==NOT_CONNECTED || D[i][j]>D[i][k]+D[k][j])){
                	D[i][j]=D[i][k]+D[k][j];
                }
//				printf("error");
            }
        }
    }*/
	timeCalculate = omp_get_wtime();

    //look for the most distant pair
	int diameter=-1;
//	#pragma omp parallel for collapse(2) shared(diameter)
    for (int i=1;i<=nodesCount;i++){
        for (int j=1;j<=nodesCount;j++){
//			#pragma omp flush(diameter)
			if (diameter<D[i][j]){
		      	diameter=D[i][j];
			}
        }
    }

	timeCompare = omp_get_wtime();

    printf("Diameter = %d\n", diameter);
	timeEnd = omp_get_wtime();
	printf("Calculating: \t%f\n", timeCalculate-timeRead);
//	printf("Comparing: \t%f\n", timeCompare-timeCalculate);
//	printf("Total: \t\t%f\n", timeEnd-timeBegin);
	
    return 0;

}
