#include <stdio.h>
#include <omp.h>

#define PROBLEMSIZE 20 
#define MAX_THREAD 8


void main(int argc, char **argv)
{
	int a[PROBLEMSIZE],b[PROBLEMSIZE],t[PROBLEMSIZE];
	int n,x;
	double time_1, time_2, time_3;
	
	time_1 = omp_get_wtime(); 	
	omp_set_num_threads(MAX_THREAD);

    #pragma omp parallel for 
    for(n=0;n<PROBLEMSIZE;n++) 
    {	
        a[n] = n*n; /* n is private by default */
    }
    
    time_2 = omp_get_wtime();

    for(n=0;n<PROBLEMSIZE;n++) 
    {	
        b[n] = n*n; /* n is private by default */
    }

    time_3 = omp_get_wtime();

    /* back to a single thread */
 //   for(x=0;x<PROBLEMSIZE;x++) 
 //   {
 //       printf("a[%d]=%d (done by thread %d)\n",x,a[x],t[x]);
 //   }

    printf("The execution time is %f.\n",time_2-time_1);
    printf("The execution time is %f.\n",time_3-time_2);
}
