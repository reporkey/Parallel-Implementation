#! /bin/bash				
#SBATCH --partition=physical
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=12
#SBATCH --time=1:00:00			
#SBATCH --export=NONE					

module load OpenMPI/2.1.1-GCC-6.4.0-2.28
make

set1='-2 1 -1 1 100 10000 -1 1 0 1 100 10000'

set2='-2 2 -2 2 100 10000 '
set3='-2 2 -2 2 200 10000 '
set4='-2 2 -2 2 400 10000 '
set5='-2 2 -2 2 600 10000 '
set6='-2 2 -2 2 800 10000 '
set7='-2 2 -2 2 1000 10000 '
set8='-2 2 -2 2 1200 10000 '
set9='-2 2 -2 2 1400 10000 '
set10='-2 2 -2 2 1600 10000 '
set11='-2 2 -2 2 1800 10000 '
set12='-2 2 -2 2 2000 10000 '

for p in mandelbrot_opti+mpi mandelbrot_opti+mpi+multithread
do
	echo ""
	echo "$p"
	echo "set = set8"
	time for i in {1..3}; do mpiexec $p $set8 $set8 >> "answer.txt"; done
	echo "set = set9"
	time for i in {1..3}; do mpiexec $p $set9 $set9 >> "answer.txt"; done
	echo "set = set10"
	time for i in {1..3}; do mpiexec $p $set10 $set10 >> "answer.txt"; done
	echo "set = set11"
	time for i in {1..3}; do mpiexec $p $set11 $set11 >> "answer.txt"; done
	echo "set = set12"
	time for i in {1..3}; do mpiexec $p $set12 $set12 >> "answer.txt"; done
done

for p in mandelbrot mandelbrot_opti mandelbrot_opti+openmp
do
	echo ""
	echo "$p"
	echo "set = set8"
	time for i in {1..3}; do ./$p $set8 $set8 >> "answer.txt"; done
	echo "set = set9"
	time for i in {1..3}; do ./$p $set9 $set9 >> "answer.txt"; done
	echo "set = set10"
	time for i in {1..3}; do ./$p $set10 $set10 >> "answer.txt"; done
	echo "set = set11"
	time for i in {1..3}; do ./$p $set11 $set11 >> "answer.txt"; done
	echo "set = set12"
	time for i in {1..3}; do ./$p $set12 $set12 >> "answer.txt"; done
done

