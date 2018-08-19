#include <stdio.h>
#include <omp.h>

#define NTHREAD 10

void main (int argc, char **argv)
{ 
	
	int i, n, chunk;
	float a[100], b[100], result; /* Some initializations */
	n = 100; 
	chunk = 10; 
	result = 0.0;
	
	for (i=0; i < n; i++) 
	{ 
		a[i] = i * 1.0; 
		b[i] = i * 2.0; 
	}

	omp_set_num_threads(NTHREAD); 

	#pragma omp parallel for default(shared) private(i) schedule(static,chunk) reduction(+:result)
	for (i=0; i < n; i++) 
	{
		result = result + (a[i] * b[i]);
		printf("temporary result by No.%d thread is %f\n", omp_get_thread_num(),result);
	}
		
	
	printf("Final result= %f\n",result);
}