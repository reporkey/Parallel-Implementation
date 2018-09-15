#! /bin/bash				

make

set1="-2 1 -1 1 100 10000 -1 1 0 1 100 10000"

set2="-1 1 -1 1 100 100000 "
set3="-1 1 -1 1 1000 100000 "
set4="-1 1 -1 1 10000 100000 "


for p in mandelbrot_opti+mpi mandelbrot_opti+mpi+multithread
do
	echo ""
	echo "$p"
	echo "set = set1"
	time mpiexec $p $set1 $set1 $set1
	echo "set = set2"
	time mpiexec $p $set2 $set2 $set2
	echo "set = set3"
	time mpiexec $p $set3 $set3 $set3
	echo "set = set4"
	time mpiexec $p $set4 $set4 $set4
done

for p in mandelbrot mandelbrot_opti mandelbrot_opti+openmp
do
	echo ""
	echo "$p"
	echo "set = set1"
	time ./$p $set1 $set1 $set1
	echo "set = set2"
	time ./$p $set2 $set2 $set2
	echo "set = set3"
	time ./$p $set3 $set3 $set3
	echo "set = set4"
	time ./$p $set4 $set4 $set4
done

