cmake_minimum_required(VERSION 3.17)
project(number_paths C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fopenmp")
set(CMAKE_C_STANDARD 99)

add_executable(number_path find_number_path.c)