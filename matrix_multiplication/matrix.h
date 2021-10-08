#ifndef MATRIX_MATMUL_MATRIX_H
#define MATRIX_MATMUL_MATRIX_H

#include "assert.h"
#include <iostream>
#include <vector>

class Matrix {
public:
  Matrix(size_t rows_num, size_t cols_num);

  double get(size_t row, size_t col) const;

  void set(size_t row, size_t col, double val);

  Matrix strassen_product(const Matrix &matrix) const;

  Matrix operator+(const Matrix &matrix) const;

  Matrix operator-(const Matrix &matrix) const;

  Matrix operator*(const Matrix &matrix) const;

  Matrix operator*(double num) const;

  std::vector<double> data;
  size_t rows;
  size_t columns;
};

#endif // MATRIX_MATMUL_MATRIX_H
