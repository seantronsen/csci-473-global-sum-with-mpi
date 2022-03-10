cmake_minimum_required(VERSION 3.21)
project(global_sum_with_mpi C)

set(CMAKE_C_STANDARD 99)
find_package(MPI REQUIRED)

add_executable(global_sum_with_mpi gsum.c functions.c functions.h)
target_link_libraries("${PROJECT_NAME}" PUBLIC MPI::MPI_C)