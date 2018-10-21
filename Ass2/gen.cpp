#include <cstdio>
#include <cstdlib>
#include <math.h>

int main (int argc, char *argv[]) {

	if(argc!=6){
        printf("Enter \n num of items \n max value of item \n max weight of item \n max total weight \n output file\n");
        return -1;
    }
	
	int n = atoi(argv[1]);
	int maxV = atoi(argv[2]);
	int maxW = atoi(argv[3]);
	int W = atoi(argv[4]);
	char* path = argv[5];

//	time_t t;
//	/* Intializes random number generator */
//	srand((unsigned) time(&t));
	
	FILE *f = fopen(path, "w");
	if (f == NULL) { 
        fprintf(stderr, "\nError opend file\n"); 
        exit (1); 
    } 

	fprintf(f, "%d %d\n", n, W);

	for (int i=1; i<=n; i++){
		fprintf(f, "%d %d\n", rand() % maxV +1, rand() % maxW +1);
	}

	fclose(f);
	return EXIT_SUCCESS;
}
