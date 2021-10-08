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

  return product_matrix;
}

double Matrix::get(size_t row, size_t col) const {
  return data[row * columns + col];
};

void Matrix::set(size_t row, size_t col, double val) {
  data[row * columns + col] = val;
}

Matrix Matrix::strassen_product(const Matrix &matrix) const {

  size_t N = this->rows;

  if (N <= 32) {
    return (*this) * matrix;
  }

  size_t k = N / 2;

  Matrix A11 = Matrix(k, k);
  Matrix A12 = Matrix(k, k);
  Matrix A21 = Matrix(k, k);
  Matrix A22 = Matrix(k, k);

  Matrix B11 = Matrix(k, k);
  Matrix B12 = Matrix(k, k);
  Matrix B21 = Matrix(k, k);
  Matrix B22 = Matrix(k, k);

  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      if (i < k && j < k) {
        A11.set(i, j, (*this).get(i, j));
        B11.set(i, j, matrix.get(i, j));
      } else if (i < k && j >= k) {
        A12.set(i, j - k, (*this).get(i, j));
        B12.set(i, j - k, matrix.get(i, j));
      } else if (i >= k && j < k) {
        A21.set(i - k, j, (*this).get(i, j));
        B21.set(i - k, j, matrix.get(i, j));
      } else if (i >= k && j >= k) {
        A22.set(i - k, j - k, (*this).get(i, j));
        B22.set(i - k, j - k, matrix.get(i, j));
      }
    }
  }
  Matrix P11 = A11 + A22;
  Matrix P12 = B11 + B22;
  Matrix P1 = P11.strassen_product(P12);

  Matrix P21 = A21 + A22;
  Matrix P22 = B11;
  Matrix P2 = P21.strassen_product(P22);

  Matrix P31 = A11;
  Matrix P32 = B12 + B22 * (-1);
  Matrix P3 = P31.strassen_product(P32);

  Matrix P41 = A22;
  Matrix P42 = B21 - B11;
  Matrix P4 = P41.strassen_product(P42);

  Matrix P51 = A11 + A12;
  Matrix P52 = B22;
  Matrix P5 = P51.strassen_product(P52);

  Matrix P61 = A21 - A11;
  Matrix P62 = B11 + B12;
  Matrix P6 = P61.strassen_product(P62);

  Matrix P71 = A12 - A22;
  Matrix P72 = B21 + B22;
  Matrix P7 = P71.strassen_product(P72);

  Matrix C11 = P1 + P4 - P5 + P7;
  Matrix C12 = P3 + P5;
  Matrix C21 = P2 + P4;
  Matrix C22 = P1 - P2 + P3 + P6;

  Matrix C = Matrix(N, N);

  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      if (i < k && j < k) {
        C.set(i, j, C11.get(i, j));
      } else if (i < k && j >= k) {
        C.set(i, j, C12.get(i, j - k));
      } else if (i >= k && j < k) {
        C.set(i, j, C21.get(i - k, j));
      } else if (i >= k && j >= k) {
        C.set(i, j, C22.get(i - k, j - k));
      }
    }
  }

  return C;
}