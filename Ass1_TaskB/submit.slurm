#! /bin/bash				
#SBATCH --partition=physical
#SBATCH --nodes=1							
#SBATCH --ntasks=12
#SBATCH --time=24:00:00						
#SBATCH --output=output.txt				

module load OpenMPI/3.0.0-GCC-6.2.0
make

set1='-2 1 -1 1 100 10000 -1 1 0 1 100 10000'

set2='-100 100 -100 100 1000 10000'
set3='-500 500 -500 500 1000 10000'
set4='-1000 1000 -1000 1000 1000 10000'

set5='100 100 0 100 1000 10000'
set6='-500 500 0 500 1000 10000'
set7='-1000 1000 0 1000 1000 10000'

set8='-500 500 -500 500 100 10000'
set9='-500 500 -500 500 1000 10000'
set10='-500 500 -500 500 2000 10000'
set11='-500 500 -500 500 5000 10000'

set12='-500 500 -500 500 1000 1000'
set13='-500 500 -500 500 1000 10000'
set14='-500 500 -500 500 1000 50000'
set15='-500 500 -500 500 1000 100000'

for p in mandelbrot mandelbrot_opti mandelbrot_opti+openmp
do
	echo ""
	echo "$p"
	for set in set1 set2 set3 set4 set5 set6 set7 set8 set9 set10 set11 set12 set13 set14 set15
	do
		echo "set = $set"
		time for i in {1..5}; do ./$p $set; done;
	done
done

echo ""
echo ""
echo ""

for p in mandelbrot_opti+mpi_reduction mandelbrot_opti+mpi_reduction+multithread
do
	echo ""
	echo "$p"
	for set in set1 set2 set3 set4 set5 set6 set7 set8 set9 set10 set11 set12 set13 set14 set15
	do
		echo "set = $set"
		time for i in {1..5}; do mpiexec $p $set; done;
	done
done
