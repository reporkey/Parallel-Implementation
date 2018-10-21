#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

int main(int argc,char** argv){

    int i = 0;
    int number;
    int size;
    size = atoi(argv[1]);
    int x[size];
    // produce array contains random number from 0 to 10000
    for (int n=0; n<size; n++){
        number = rand()%10001;
        x[n] = number;
    }

    double t1,t2;
    t1=MPI_Wtime();
    for (int j=0;j<=size-1;j++){
        if (j>=(powf(2,i))){
            int t=powf(2,i);
            x[j]=x[j]+x[j-t];
        }
    }
    t2=MPI_Wtime();

    printf("\nTotal time = %f sec\n",t2-t1);
    
}