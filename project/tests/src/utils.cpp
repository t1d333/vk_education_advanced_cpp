#include "../include/utils.hpp"
#include <cstddef>

MatrixData createMatrixData(std::istream& is, size_t rows, size_t cols) {

  if (!is) {
    throw std::runtime_error("Failed to create matrix_data from input stream");
  }

  MatrixData matrix_data(rows, MatrixRow(cols, 0.0));
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      is >> matrix_data[i][j];
      if (!is) {
        throw std::runtime_error("MatrixData reading failed");
      }
    }
  }

  return matrix_data;
}




std::ostream& operator<<(std::ostream& os, const MatrixData& matrix_data) {

  for (auto& row: matrix_data) {
    for (auto& data: row) {
      os << data << ' ';
    }
    os << std::endl;
  }

  return os;
}

