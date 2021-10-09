#!/bin/bash

for optimization_flag in '-g' '-O3'
do
  echo "Optimization flag : $optimization_flag"
  make OPTIMIZE=$optimization_flag
  for matrix_size in 500 512 1000 1024 2000 2048
  do
    ./matrix_multiplication $matrix_size
    ./matrix_multiplication $matrix_size strassen
  done
done
