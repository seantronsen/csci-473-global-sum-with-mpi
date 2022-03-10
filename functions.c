#include <math.h>
#include <mpi.h>
#include <stdio.h>
#include "functions.h"

void global_sum_forgetful_edition(double *result, int rank, int size, double my_value) {

    // set the initial group number for the partitioning
    double group_number = rank;

    // perform an iteration for each phase
    for (int phase_number = 0; phase_number < log2(size); phase_number++) {

        // distance is defined by the phase number the loop is currently on
        int distance = pow(2, phase_number);

        // the direction depends on whether the partition group number is even or odd
        // doing such avoids over-complicated operations such as checking for operational bounds each iteration
        // the if the group number is an even number, then travel to the right
        // otherwise travel to the left by the specified distance.
        int direction = ((int) group_number % 2) == 0 ? 1 : -1;
        int target_process = rank + (distance * direction);

        /* COMMUNICATIONS WITH OTHER PROCESSES */

        // send output
        printf("Phase %d - P %d sending to P %d  -  value %lf\n", phase_number, rank, target_process, my_value);
        MPI_Send(&my_value, 1, MPI_DOUBLE, target_process, phase_number, MPI_COMM_WORLD);
        //receive input
        double holder = 0; // buffer for the received value
        MPI_Recv(&holder, 1, MPI_DOUBLE, target_process, phase_number, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Phase %d - P %d receiving from P %d-value %lf\n", phase_number, rank, target_process, holder);
        my_value += holder;
        group_number = floor(group_number / 2);
    }
    *result = my_value;
}


void global_sum(double *result, int rank, int size, double my_value) {

    // set the initial group number for the partitioning
    double group_number = rank;

    // perform an iteration for each phase
    for (int phase_number = 0; phase_number < log2(size); phase_number++) {

        // distance is defined by the phase number the loop is currently on
        int distance = pow(2, phase_number);

        // the direction depends on whether the partition group number is even or odd
        // doing such avoids over-complicated operations such as checking for operational bounds each iteration
        // the if the group number is an even number, then travel to the right
        // otherwise travel to the left by the specified distance.
        int direction = ((int) group_number % 2) == 0 ? 1 : -1;
        int target_process = rank + (distance * direction);

        /* COMMUNICATIONS WITH OTHER PROCESSES */

        double holder = 0; // buffer for the received value
        if (((int) group_number % 2) == 0) {

            // send output
            printf("Phase %d - P %d sending to P %d  -  value %lf\n", phase_number, rank, target_process, my_value);
            MPI_Ssend(&my_value, 1, MPI_DOUBLE, target_process, phase_number, MPI_COMM_WORLD);
            //receive input
            MPI_Recv(&holder, 1, MPI_DOUBLE, target_process, phase_number, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Phase %d - P %d receiving from P %d-value %lf\n", phase_number, rank, target_process, holder);

        } else {

            //receive input
            MPI_Recv(&holder, 1, MPI_DOUBLE, target_process, phase_number, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Phase %d - P %d receiving from P %d-value %lf\n", phase_number, rank, target_process, holder);

            // send output
            printf("Phase %d - P %d sending to P %d  -  value %lf\n", phase_number, rank, target_process, my_value);
            MPI_Ssend(&my_value, 1, MPI_DOUBLE, target_process, phase_number, MPI_COMM_WORLD);
        }
        my_value += holder;
        group_number = floor(group_number / 2);
    }
    *result = my_value;
}

