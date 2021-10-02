# Optimization matrix multiplication via parallelization

### Compile
```
gcc matmul_omp.c -O3 -o test_omp -fopenmp -lpthread

```

![image](https://user-images.githubusercontent.com/49230518/135718128-5525a64b-0312-4266-a550-322666bd5f46.png)

```
After parallelization via openmp we can reduce x5 execution time from 0.48 to 0.093
```

