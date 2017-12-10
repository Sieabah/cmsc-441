How to run on maya:

You can submit the slurm files independently.  Or you can use the bash script created to automatically submit all the slurm files.  


BATCH SLURMS
--------------------------------

chmod +x submit-batch.sh

./submit-batch.sh

the output files will go to the out/ directory.

Any error files will go to the created err/ directory.


COMPILING:
--------------------------------

To compile the program run:

make

to clean the files run:

make clean

