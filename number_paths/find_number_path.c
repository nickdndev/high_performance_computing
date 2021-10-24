#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

void matmul(const int *matrix1, const int *matrix2, int *output, int N) {
  int tmp[N * N];

#pragma omp parallel for shared(tmp, N) default(none)
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < N; ++j)
      tmp[i * N + j] = 0;

#pragma omp parallel for shared(tmp, N, matrix1, matrix2) default(none)
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < N; ++j)
      for (int k = 0; k < N; ++k)
        tmp[i * N + j] += matrix1[i * N + k] * matrix2[k * N + j];

#pragma omp parallel for shared(tmp, N, output) default(none)
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < N; ++j)
      output[i * N + j] = tmp[i * N + j];
}

void pow2(int *p2, int *k2, const int k) {
  p2[0] = 0;
  k2[0] = 1;

  if (k <= 1)
    return;

  while (k2[0] <= k) {
    k2[0] <<= 1;
    ++p2[0];
  }

  if (k2[0] > k) {
    k2[0] >>= 1;
    --p2[0];
  }
}

void pow_matrix(int *matrix, int N, int power) {
  int k2 = 0, p2 = 0;
  int tmp_matrix[N * N];

  pow2(&p2, &k2, power);

#pragma omp parallel for shared(matrix, N, tmp_matrix) default(none)
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < N; ++j)
      tmp_matrix[i * N + j] = matrix[i * N + j];

  for (int i = 0; i < p2; ++i)
    matmul(&matrix[0], &matrix[0], &matrix[0], N);

  for (int i = 0; i < (power - k2); ++i)
    matmul(&tmp_matrix[0], &matrix[0], &matrix[0], N);
}

void fill_random_graph(int *matrix, int N, int seed) {
  srand(seed);
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      matrix[i * N + j] = matrix[i * N + j];
      if (i == j) {
        matrix[i * N + j] = 0;
      } else {
        matrix[i * N + j] = rand() & 1;
      }
    }
  }
}

void print_matrix(int *matrix, int N) {
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j)
      printf("%d ", matrix[i * N + j]);
    printf("\n");
  }
  printf("\n");
}

int main(int argc, char *argv[]) {

  int LENGTH_PATH = 8;
  int SEED = 56;
  int N = 4;
  int *input_matrix = malloc(N * N * sizeof(int));

  fill_random_graph(input_matrix, N, SEED);

  print_matrix(input_matrix, N);

  double start = omp_get_wtime();

  pow_matrix(input_matrix, N, LENGTH_PATH);

  double end = omp_get_wtime();
  double execution_time = end - start;

  printf("Matrix ^ %d\n", LENGTH_PATH);
  print_matrix(input_matrix, N);

  printf("Execution time : %f \n", execution_time);

  return 0;
}