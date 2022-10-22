#pragma once
#include <bits/types/siginfo_t.h>
#include <cstddef>
#include <filesystem>
#include <fstream>
#include <gtest/gtest.h>
#include "../../include/Matrix.hpp"

namespace fs = std::filesystem; 

extern fs::path glob_test_dir;

using MatrixData = std::vector<std::vector<double>>;
using MatrixRow = std::vector<double>;


MatrixData create_matrix_data(std::istream& is, size_t rows, size_t cols);


template<size_t rows, size_t cols>
bool operator==(const Matrix<rows, cols>& matrix, const MatrixData& matrix_data) {
  size_t rows_other = matrix_data.size();
  size_t cols_other = matrix_data[0].size();

  if ((rows != rows_other) || (cols != cols_other)) {
    return false;
  }

  for (size_t i = 0; i < matrix_data.size(); ++i) {
    for (size_t j = 0; j < matrix_data[i].size(); ++j) {
      if (std::fabs((matrix(i, j) - matrix_data[i][j])) > 1e-10) {
        return false;
      }
    }
  }
  return true;
}

template<size_t rows, size_t cols>
bool operator==(const MatrixData& matrix_data, const Matrix<rows, cols>& matrix) {
  return matrix == matrix_data;
}

template<size_t rows, size_t cols>
Matrix<rows, cols> create_matrix_from_file(std::istream &is) {
    Matrix<rows, cols> result;
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            is >> result(i, j);
        }
    }
    return result;
}

std::ostream& operator<<(std::ostream& os, const MatrixData& matrix_data); 

