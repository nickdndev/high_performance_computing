cmake_minimum_required(VERSION 3.15)
project(pi_estimation)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fopenmp")

add_executable(pi_estimation main.c)