#pragma once
#include <bits/types/siginfo_t.h>
#include <cstddef>
#include <filesystem>
#include <fstream>
#include <gtest/gtest.h>
#include "../../include/Matrix.hpp"

namespace fs = std::filesystem; 

extern fs::path glob_test_dir;

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

