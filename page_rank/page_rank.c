#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>


void norm_cols_matrix(int N, double *input_matrix, double eps) {
  double sum[N];

#pragma omp parallel for shared(sum, N) default(none)
  for (int i = 0; i < N; ++i)
    sum[i] = 0;

#pragma omp parallel for shared(sum, input_matrix, N) default(none)
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < N; ++j)
      sum[i] += input_matrix[j * N + i];
#pragma omp parallel for shared(sum, input_matrix, N, eps) default(none)
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < N; ++j)
      if (abs(sum[j]) > eps)
        input_matrix[i * N + j] /= sum[j];
}

double norm2(int N, const double *vector) {
  double norm = 0;
#pragma omp parallel for shared(vector, N) reduction(+ : norm) default(none)
  for (int i = 0; i < N; ++i)
    norm += vector[i] * vector[i];
  return sqrt(norm);
}

double norm2_vector(int N, double *vector, double eps) {
  double norm = norm2(N, &vector[0]);

  if (abs(norm) > eps) {
#pragma omp parallel for shared(vector, N, norm) default(none)
    for (int i = 0; i < N; ++i)
      vector[i] /= norm;
  }
  return norm;
}

void mult_matrix_on_vector(double *input_matrix, const double *vector, int N,double *res) {
  double tmp[N];
#pragma omp parallel for shared(tmp, N) default(none)
  for (int i = 0; i < N; ++i)
    tmp[i] = 0;
#pragma omp parallel for shared(tmp, N, input_matrix, vector) default(none)
  for (int i = 0; i < N; ++i)
    for (int k = 0; k < N; ++k)
      tmp[i] += input_matrix[i * N + k] * vector[k];
#pragma omp parallel for shared(tmp, N, input_matrix, res) default(none)
  for (int i = 0; i < N; ++i)
    res[i] = tmp[i];
}

void pagerank(int N, double *input_matrix, double *ranks, const double eps) {
#pragma omp parallel for shared(ranks, N) default(none)
  for (int i = 0; i < N; ++i)
    ranks[i] = 1;

  double norm_cur, norm_last;
  norm_last = norm2_vector(N, &ranks[0], eps);

  norm_cols_matrix(N, input_matrix, eps);

  mult_matrix_on_vector( &input_matrix[0], &ranks[0],N, &ranks[0]);
  norm_cur = norm2_vector(N, &ranks[0], eps);

  while (abs(norm_cur - norm_last) >= eps) {
    norm_last = norm_cur;
    mult_matrix_on_vector( &input_matrix[0], &ranks[0],N, &ranks[0]);
    norm_cur = norm2_vector(N, &ranks[0], eps);
  }
}

void generate_random_graph(double *input_matrix, const int N) {

  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j)
      if (i != j)
        input_matrix[i * N + j] = rand() % (2);
      else
        input_matrix[i * N + j] = 0;
  }
}

void calculate_naive_rank(double *input_matrix, double *naive_ranks, int N) {
#pragma omp parallel for shared(naive_ranks, input_matrix, N) default(none)
  for (int i = 0; i < N; ++i) {
    naive_ranks[i] = 0;
    for (int j = 0; j < N; ++j)
      naive_ranks[i] += input_matrix[i * N + j];
  }
}
void print_matrix(const int N, const double *M) {
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j)
      printf("%f ", M[i * N + j]);
    printf("\n");
  }
}


void print_ranks(const int N, const double *V) {
  for (int i = 0; i < N; ++i)
    printf("%f ", V[i]);
  printf("\n");
}


int main(int argc, char *argv[]) {
  const double EPS = 0.0001;
  const int N = 3;
  double input_matrix[N * N];
  double ranks[N];

  double naive_ranks[N];

  generate_random_graph(input_matrix, N);

  printf("Input graph\n");
  print_matrix(N, input_matrix);
  printf("\n");

  calculate_naive_rank(input_matrix, naive_ranks, N);

  pagerank(N, &input_matrix[0], &ranks[0], EPS);
  printf("Pagerank ->\n");
  print_ranks(N, &ranks[0]);
  printf("\n");

  printf("Naive approach->\n");
  print_ranks(N, &naive_ranks[0]);
  printf("\n");

  return 0;
}