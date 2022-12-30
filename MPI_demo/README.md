# PUCS610_N6 Release Note
This is a console MRI program that generates a random number in range of 0-10 for each processes created (tested for: 1, 2, 4, 8, 16, 32, 64, 128 process) and add them up parallelly in reduced fashion using collective communications.


### How to Run
Compile the mpi_multiLoads.c with gcc. Run it with the following command:

**mpiexec -n NUMBER_OF_PROCESS --hostfile HOSTFILE_NAME ./COMPILED_FILE_NAME**

(ex. mpiexec -n 16 --hostfile hostfile.txt ./a.out)


### Note
Please make sure to have MPI packages (ex. libmpich-dev) installed, as the program requires mpicc to run.

This program also requires a hostfile to be present in order to mitigate the low cpu slot warning (at least in linux). Please make sure you have the following hostfile present within same directory as this program. Create a hostfile, add the following content to it and save:
**localhost slots=256**
