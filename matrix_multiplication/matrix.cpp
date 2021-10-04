#include "matrix.h"

Matrix::Matrix(size_t rows_size, size_t columns_size) {
  rows = rows_size;
  columns = columns_size;

  data.resize(rows * columns * 1);
  for (int i = 0; i < rows * columns; ++i) {
    data[i] = i + 1;
  }
}

Matrix Matrix::operator+(const Matrix &matrix) const {
  assert(matrix.rows == rows);
  assert(matrix.columns == columns);

  Matrix new_matrix = Matrix(rows, columns);

  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < rows; ++j) {
      auto val = get(i, j) + matrix.get(i, j);
      new_matrix.set(i, j, val);
    }
  }

  return new_matrix;
}

Matrix Matrix::operator-(const Matrix &matrix) const {
  return *this + matrix * (-1);
}

Matrix Matrix::operator*(double num) const {

  Matrix new_matrix = Matrix(rows, columns);

  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < columns; ++j) {
      double val = get(i, j) * num;
      new_matrix.set(i, j, val);
    }
  }
  return new_matrix;
}

Matrix Matrix::operator*(const Matrix &matrix) const {
  assert(this->columns == matrix.rows);
  size_t N = this->columns;
  size_t dummy = 0;
  size_t i, j, k;

  Matrix product_matrix = Matrix(this->rows, matrix.columns);

  for (k = 0; k < N; k++)
    for (i = 0; i < N; i++) {
      dummy = i * N;
      for (j = 0; j < N; j++)
        product_matrix.data[dummy + j] =
            product_matrix.data[dummy + j] +
            this->data[dummy + k] * matrix.data[k * N + j];
    }

  //  Matrix product_matrix = Matrix(this->rows, matrix.columns);
  //  for (size_t i = 0; i < this->rows; ++i) {
  //    for (size_t j = 0; j < matrix.columns; ++j) {
  //      double sum = 0;
  //      for (size_t n = 0; n < this->columns; ++n) {
  //        sum += this->get(i, n) * matrix.get(n, j);
  //      }
  //      product_matrix.set(i, j, sum);
  //    }
  //  }
  return product_matrix;
}

double Matrix::get(size_t row, size_t col) const {
  return data[row * columns + col];
};

void Matrix::set(size_t row, size_t col, double val) {
  data[row * columns + col] = val;
}
