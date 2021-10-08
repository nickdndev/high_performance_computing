#!/bin/bash

for optimization_flag in '-g' '-O3'
do
  echo "Optimization flag : $optimization_flag"
  make OPTIMIZE=$optimization_flag
  for matrix_size in 512 1024 2048 4096
  do
    ./matrix_multiplication $matrix_size
    ./matrix_multiplication $matrix_size strassen
  done
done
