cmake_minimum_required(VERSION 3.17)
project(operations C)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fopenmp")

#add_executable(omp_parfoc omp_parfoc.c.c)
add_executable(omp_reduction omp_reduction.c)