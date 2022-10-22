#include "../include/utils.hpp"
#include <cmath>
#include <cstddef>
#include <fstream>
#include <gtest/gtest.h>
#include <array>

TEST(MathOperation, NumberMulMatrix) {
    fs::path data_path{glob_test_dir / "mul" };
    std::ifstream is(data_path / "in1.txt");  
    Matrix<6, 4> m = create_matrix_from_file<6, 4>(is);
    double val = 0;
    is >> val;
    is.close();
    is.open(data_path/"out1.txt");
    MatrixData expected_matrix = create_matrix_data(is, 6, 4);
    is.close();
    ASSERT_EQ(val * m, expected_matrix);
}


TEST(MathOperation, MatrixMulVector) {
    fs::path data_path{glob_test_dir / "mul" };
    std::ifstream is(data_path / "in2.txt");  
    Matrix<3, 3> m = create_matrix_from_file<3, 3>(is);
    Matrix_col<3> vec = create_matrix_from_file<3, 1>(is);
    is.close();
    is.open(data_path/"out2.txt");
    MatrixData expected_matrix = create_matrix_data(is, 3, 1);
    is.close();
    ASSERT_EQ(m * vec, expected_matrix);
}

TEST(MathOperation, VecotrMulMatrix) {
    fs::path data_path{glob_test_dir / "mul" };
    std::ifstream is(data_path / "in3.txt");  
    Matrix<4, 5> m = create_matrix_from_file<4, 5>(is);
    Matrix_row<4> vec = create_matrix_from_file<1, 4>(is);
    is.close();
    is.open(data_path/"out3.txt");
    MatrixData expected_matrix = create_matrix_data(is, 1, 5);
    is.close();
    ASSERT_EQ(vec * m, expected_matrix);
}

TEST(MathOperation, MatrixMulMatrix) {
    fs::path data_path{glob_test_dir / "mul" };
    std::ifstream is(data_path / "in4.txt");  
    Matrix<4, 3> m_lhs = create_matrix_from_file<4, 3>(is);
    Matrix<3, 5> m_rhs = create_matrix_from_file<3, 5>(is);
    is.close();
    is.open(data_path/"out4.txt");
    MatrixData expected_matrix = create_matrix_data(is, 4, 5);
    is.close();
    ASSERT_EQ(m_lhs * m_rhs, expected_matrix);
}


TEST(MathOperation, Transp) {
    fs::path data_path{glob_test_dir / "transp" };
    std::ifstream is(data_path / "in.txt");  
    Matrix<4, 9> m = create_matrix_from_file<4, 9>(is);
    is.close();
    is.open(data_path/"out.txt");
    MatrixData expected_matrix = create_matrix_data(is, 9, 4);
    is.close();
    ASSERT_EQ(m.transp(), expected_matrix);
}


TEST(MathOperation, Det) {
    fs::path data_path{glob_test_dir / "det" };
    std::ifstream is(data_path / "in.txt");  
    Matrix<10, 10> m = create_matrix_from_file<10, 10>(is);
    is.close();
    is.open(data_path/"out.txt");
    double expexted = 0;
    is >> expexted; 
    is.close();
    ASSERT_NEAR(expexted, m.det(), 1e-6);
}


TEST(MathOperation, Inv) {
    fs::path data_path{glob_test_dir / "inv" };
    std::ifstream is(data_path / "in.txt");  
    Matrix<10, 10> m = create_matrix_from_file<10, 10>(is);
    is.close();
    is.open(data_path/"out.txt");
    MatrixData expected_matrix = create_matrix_data(is, 10, 10);
    is.close();
    ASSERT_EQ(m.inv(), expected_matrix);
}
