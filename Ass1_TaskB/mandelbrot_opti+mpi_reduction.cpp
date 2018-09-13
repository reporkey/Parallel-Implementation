#include <cstdio>
#include <cstdlib>
#include <math.h>
#include <mpi.h>

// Cardioid / bulb checking
bool cardioidCheck(double real, double img){
	double p = sqrt(pow((real-0.25),2) + pow(img,2));
	if (real < p-2*pow(p,2)+0.25 || pow(real+1,2)+pow(img,2) < 0.0625) return 1;
	return 0;
}

// return 1 if in set, 0 otherwise
int inset(double real, double img, int maxiter){
	double z_real = real;
	double z_img = img;
	if (cardioidCheck(real, img)) return 1;
	for(int iters = 0; iters < maxiter; iters++){
		double z_real_temp = z_real*z_real-z_img*z_img + real;
		double z_img_temp = 2.0*z_real*z_img + img;
		
		// Periodicity checking
		if (z_real == z_real_temp && z_img == z_img_temp) break;		
		z_real = z_real_temp;
		z_img = z_img_temp;
		if(z_real*z_real + z_img*z_img > 4.0) return 0;
	}
	return 1;
}

// main
int main(int argc, char *argv[]){
	double real_lower;
	double real_upper;
	double img_lower;
	double img_upper;
	int num;
	int maxiter;
	int num_regions = (argc-1)/6;

	// MPI init
	int problem_size = num*num;
	int rank = 0, comm_sz = 0;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

	for(int region=0;region<num_regions;region++){
		// scan the arguments
		sscanf(argv[region*6+1],"%lf",&real_lower);
		sscanf(argv[region*6+2],"%lf",&real_upper);
		sscanf(argv[region*6+3],"%lf",&img_lower);
		sscanf(argv[region*6+4],"%lf",&img_upper);
		sscanf(argv[region*6+5],"%i",&num);
		sscanf(argv[region*6+6],"%i",&maxiter);		

		// count the number of points in the set, within the region
		int count=0;
		int real =0, img = 0;
		double real_step = (real_upper-real_lower)/num;
		double img_step = (img_upper-img_lower)/num;
		double img_lower_bound = (abs(img_lower) < abs(img_upper)) ? abs(img_lower) : abs(img_upper);

		int local_count = 0;
		double local_real = real_lower + rank*real_step;
		double local_img = img_lower + rank*img_step;

		for(int real=num/comm_sz*rank; real<num/comm_sz*(rank+1); real++){
			for(int img=0; img<num; img++){
				if (img > 0 && img < img_lower_bound) {
					local_count+=2*inset(real_lower+real*real_step,img_lower+img*img_step,maxiter);
				}
				if (img > -img_lower_bound && img < 0) continue;
				local_count+=inset(real_lower+real*real_step,img_lower+img*img_step,maxiter);
			}
		}
		MPI_Reduce(&local_count, &count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
		if (rank == 0){
			printf("%d\n", count);
		}
	}
	
	MPI_Finalize();
	return EXIT_SUCCESS;
}
