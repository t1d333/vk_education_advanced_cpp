#include "../include/utils.hpp"
#include <cmath>
#include <cstddef>
#include <fstream>
#include <gtest/gtest.h>
#include <array>

TEST(GettersTest, GetElem) {
    fs::path data_path{glob_test_dir / "getters" };
    std::ifstream is(data_path / "in1.txt");  
    Matrix<4, 6> m = create_matrix_from_file<4, 6>(is);
    size_t i = 0;
    size_t j = 0;
    is >> i >> j;
    is.close();
    is.open(data_path/"out1.txt");
    double val = 0;
    is >> val;
    is.close();
    ASSERT_EQ(val, m(i, j));
}

TEST(GettersTest, GetRow) {
    fs::path data_path{glob_test_dir / "getters" };
    std::ifstream is(data_path / "in2.txt");  
    Matrix<4, 5> m = create_matrix_from_file<4, 5>(is);
    size_t i = 0;
    is >> i;
    is.close();
    is.open(data_path/"out2.txt");
    MatrixData expected_row = create_matrix_data(is, 1, 5);
    is.close();
    ASSERT_EQ(expected_row, m.get_row(i));
}

TEST(GettersTest, GetCol) {
    fs::path data_path{glob_test_dir / "getters" };
    std::ifstream is(data_path / "in3.txt");  
    Matrix<6, 4> m = create_matrix_from_file<6, 4>(is);
    size_t i = 0;
    is >> i;
    is.close();
    is.open(data_path/"out3.txt");
    MatrixData expected_row = create_matrix_data(is, 6, 1);
    is.close();
    ASSERT_EQ(expected_row, m.get_col(i));
}

TEST(GettersTest, GetDiag) {
    fs::path data_path{glob_test_dir / "getters" };
    std::ifstream is(data_path / "in4.txt");  
    Matrix<5, 5> m = create_matrix_from_file<5, 5>(is);
    is.close();
    is.open(data_path/"out4.txt");
    MatrixData expected_diag = create_matrix_data(is, 5, 1);
    is.close();
    ASSERT_EQ(expected_diag, m.get_diag());
}
