# Optimization matrix multiplication via parallelization

![image](https://user-images.githubusercontent.com/49230518/135718235-05e55a1a-5627-47c1-ba57-06f49cd29192.png)

### Compile
```
gcc matmul_omp.c -O3 -o test_omp -fopenmp -lpthread

```

![image](https://user-images.githubusercontent.com/49230518/135718128-5525a64b-0312-4266-a550-322666bd5f46.png)

```
After parallelization via openmp we can reduce x5 execution time from 0.48 to 0.093
```

