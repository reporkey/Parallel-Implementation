#! /bin/bash
#SBATCH --partition=physical
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=12
#SBATCH --mem-per-cpu=MaxMemPerCPU
#SBATCH --time=1:00:00


module load OpenMPI/2.1.1-GCC-6.4.0-2.28
make

./run.sh
