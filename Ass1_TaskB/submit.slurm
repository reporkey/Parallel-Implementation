#! /bin/bash				
#SBATCH --partition=physical
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=12
#SBATCH --time=1:00:00			
#SBATCH --export=NONE					

module load OpenMPI/2.1.1-GCC-6.4.0-2.28
make

set1='-2 1 -1 1 100 10000 -1 1 0 1 100 10000'

set2='-100 100 -1000 100 1000 10000'
set3='-500 500 -5000 500 1000 10000'
set4='-1000 1000 -10000 1000 1000 10000'

set5='100 100 0 1000 1000 10000'
set6='-500 500 0 5000 1000 10000'
set7='-1000 1000 0 10000 1000 10000'

set8='-500 500 -5000 500 100 10000'
set9='-500 500 -5000 500 1000 10000'
set10='-500 500 -5000 500 2000 10000'
set11='-500 500 -5000 500 5000 10000'

set12='-500 500 -5000 500 1000 1000'
set13='-500 500 -5000 500 1000 10000'
set14='-500 500 -5000 500 1000 50000'
set15='-500 500 -5000 500 1000 100000'

for p in mandelbrot mandelbrot_opti mandelbrot_opti+openmp
do
	echo ""
	echo "$p"
	echo "" >> "answer.txt"
	echo "$p" >> "answer.txt"
	for set in set1 set2 set3 set4 set5 set6 set7 set8 set9 set10 set11 set12 set13 set14 set15
	do
		echo "set = $set"
		echo "set = $set" >> "answer.txt"
		time ./$p $set $set $set $set $set $set $set $set $set $set >> "answer.txt"
	done
done

echo ""
echo ""
echo ""

for p in mandelbrot_opti+mpi mandelbrot_opti+mpi+multithread
do
	echo ""
	echo "$p"
	echo "" >> "answer.txt"
	echo "$p" >> "answer.txt"
	for set in set1 set2 set3 set4 set5 set6 set7 set8 set9 set10 set11 set12 set13 set14 set15
	do
		echo "set = $set"
		echo "set = $set" >> "answer.txt"
		time mpiexec $p $set $set $set $set $set $set $set $set $set $set >> "answer.txt"
	done
done
