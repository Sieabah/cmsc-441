#!/bin/bash
#SBATCH --job-name=proj2-cpu1
#SBATCH --output cpu1.out
#SBATCH --error cpu1.err
#SBATCH --partition=batch
#SBATCH --qos=short
#SBATCH --constraint=hpcf2010
#SBATCH --exclusive
#SBATCH --cpus-per-task=1
#SBATCH --ntasks=1

export KMP_AFFINITY="verbose,compact"
export OMP_NUM_THREADS=1
srun ./main test1.txt 10 test2.txt 10
srun ./main test1.txt 25 test2.txt 25
srun ./main test1.txt 50 test2.txt 50
srun ./main test1.txt 75 test2.txt 75
srun ./main test1.txt 100 test2.txt 100
srun ./main test1.txt 175 test2.txt 175
srun ./main test1.txt 250 test2.txt 250
srun ./main test1.txt 500 test2.txt 500
srun ./main test1.txt 750 test2.txt 750
srun ./main test1.txt 1000 test2.txt 1000
srun ./main test1.txt 1250 test2.txt 1250
srun ./main test1.txt 1500 test2.txt 1500
srun ./main test1.txt 1750 test2.txt 1750
srun ./main test1.txt 2000 test2.txt 2000
srun ./main test1.txt 2250 test2.txt 2250
srun ./main test1.txt 2500 test2.txt 2500
srun ./main test1.txt 5000 test2.txt 5000
srun ./main test1.txt 7500 test2.txt 7500
srun ./main test1.txt 10000 test2.txt 10000
srun ./main test1.txt 12500 test2.txt 12500
srun ./main test1.txt 15000 test2.txt 15000
srun ./main test1.txt 17500 test2.txt 17500
srun ./main test1.txt 20000 test2.txt 20000
srun ./main test1.txt 22500 test2.txt 22500
srun ./main test1.txt 25000 test2.txt 25000
srun ./main test1.txt 27500 test2.txt 27500
srun ./main test1.txt 30000 test2.txt 30000