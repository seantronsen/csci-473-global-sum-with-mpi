#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include "functions.h"

int main(int argc, char **argv) {

    int rank, size, value;
    double sum;
    sum = rank = size = value = 0;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    /* ENSURE THAT THE NUMBER OF PROCESSES IS A POWER OF TWO */
    if ((size & (size - 1)) != 0) {
        if (rank == 0) printf("Program processes must be a power of 2\n");
        exit(EXIT_SUCCESS); // kill the program
    }
    value = rank;
    global_sum(&sum, rank, size, value);
    printf("FINAL IN MAIN: Process: %d has Sum = %f \n", rank, sum);
    MPI_Finalize();
    return 0;
}