#ifndef GLOBAL_SUM_WITH_MPI_FUNCTIONS_H
#define GLOBAL_SUM_WITH_MPI_FUNCTIONS_H

void global_sum_forgetful_edition(double *result, int rank, int size, double my_value);
void global_sum(double *result, int rank, int size, double my_value);

#endif //GLOBAL_SUM_WITH_MPI_FUNCTIONS_H