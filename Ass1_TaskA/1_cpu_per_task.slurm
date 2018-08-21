#! /bin/bash									
#SBATCH --partition=physical					
#SBATCH --nodes=1							
#SBATCH --ntasks=1	
#SBATCH --cpu-per-task=1
#SBATCH --account=punim0520						
#SBATCH --time=00:10:00						
#SBATCH --output=output.txt				

time ./run.sh			
