#!/bin/bash
#SBATCH --job-name=proj2-cpu2
#SBATCH --output out/cpu2.out
#SBATCH --error err/cpu2.err
#SBATCH --partition=batch
#SBATCH --qos=short
#SBATCH --constraint=hpcf2010
#SBATCH --exclusive
#SBATCH --cpus-per-task=2
#SBATCH --ntasks=1

export KMP_AFFINITY="verbose,compact"
export OMP_NUM_THREADS=2
srun ./main test1.txt 10 test2.txt 10
srun ./main test1.txt 100 test2.txt 100
srun ./main test1.txt 1000 test2.txt 1000
srun ./main test1.txt 10000 test2.txt 10000
srun ./main test1.txt 25000 test2.txt 25000