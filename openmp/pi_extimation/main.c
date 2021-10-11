#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/*http://selkie.macalester.edu/csinparallel/modules/MonteCarloSimulationExemplar/build/html/SeedingThreads/SeedEachThread.html
 * how to initiate seed */

double pi_estimation(int iterations, short n_threads) {
  int inside_points = 0;
  unsigned int x_seed, y_seed;
  int tid;

#pragma omp parallel private(x_seed, y_seed, tid)                              \
    shared(iterations, inside_points) default(none) num_threads(n_threads)
  {
    tid = omp_get_thread_num();
    x_seed = (time(NULL) & 0xFFFFFFF0) | (tid + 3);
    y_seed = (time(NULL) & 0xFFF0FFFF) | (tid + 7);

#pragma omp for reduction(+ : inside_points)
    for (auto i = 0; i < iterations; ++i) {

      double x = (double)rand_r(&x_seed) / RAND_MAX;
      double y = (double)rand_r(&y_seed) / RAND_MAX;

      if ((x * x + y * y) <= 1) {
        inside_points++;
      }
    }
  }
  double pi = (inside_points / (double)iterations) * 4;
  return pi;
}

int main() {
  const short n_threads = 10;
  const int iterations = 100000000;

  double start = omp_get_wtime();
  double pi = pi_estimation(iterations, n_threads);
  double end = omp_get_wtime();

  double execution_time = end - start;

  printf("Execution time: %f s\n", execution_time);
  printf("PI=%f\n", pi);

  return 0;
}
