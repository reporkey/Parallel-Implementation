#! /bin/bash									
#SBATCH --partition=cloud					
#SBATCH --nodes=1							
#SBATCH --ntasks=1	
#SBATCH --cpus-per-task=8						
#SBATCH --account=punim0520						
#SBATCH --time=10:00:00						
#SBATCH --output=output.txt				

time ./run.sh
