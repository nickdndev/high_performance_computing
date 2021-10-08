#include "matrix.h"
#include <chrono>
#include <iostream>
#include <string>

int main(int argc, char **argv) {

  int matrix_size = 512;
  std::string matrix_multiplication_type="classic";

  if (argc > 1 && argv[1]) {
    matrix_size = std::stoi(argv[1]);
  }

  if (argc > 2 && argv[2]) {
    matrix_multiplication_type = argv[2];
  }

  Matrix matrix_left = Matrix(matrix_size, matrix_size);
  Matrix matrix_right = Matrix(matrix_size, matrix_size);

  auto start = std::chrono::high_resolution_clock::now();

  if (matrix_multiplication_type.compare("strassen") == 1) {
    Matrix product_matrix = matrix_left.strassen_product(matrix_right);
  } else {
    Matrix product_matrix = matrix_left * matrix_right;
  }

  auto end = std::chrono::high_resolution_clock::now();

  auto duration =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  std::cout << "Duration: [" << duration.count() << "] ms, Matrix size: ["
            << matrix_size << "x" << matrix_size << "] ("
            << matrix_multiplication_type << ")" << std::endl;

  return 0;
}