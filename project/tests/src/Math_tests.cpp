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
    Matrix<6, 4> expected_matrix = create_matrix_from_file<6, 4>(is);
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
    Matrix<3, 1> expected_matrix = create_matrix_from_file<3, 1>(is);
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
    Matrix<1, 5> expected_matrix = create_matrix_from_file<1, 5>(is);
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
    Matrix<4, 5> expected_matrix = create_matrix_from_file<4, 5>(is);
    is.close();
    ASSERT_EQ(m_lhs * m_rhs, expected_matrix);
}


TEST(MathOperation, Transp) {
    fs::path data_path{glob_test_dir / "transp" };
    std::ifstream is(data_path / "in.txt");  
    Matrix<4, 9> m = create_matrix_from_file<4, 9>(is);
    is.close();
    is.open(data_path/"out.txt");
    Matrix<9, 4> expected_matrix = create_matrix_from_file<9, 4>(is);
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
    Matrix<10, 10> expected_matrix = create_matrix_from_file<10, 10>(is);
    is.close();
    ASSERT_EQ(m.inv(), expected_matrix);
}

TEST(MathOperation, SumMatrix) {
    fs::path data_path{glob_test_dir / "sum" };
    std::ifstream is(data_path / "in1.txt");  
    Matrix<6, 9> lhs = create_matrix_from_file<6, 9>(is);
    Matrix<6, 9> rhs = create_matrix_from_file<6, 9>(is);
    is.close();
    is.open(data_path/"out1.txt");
    Matrix<6, 9> expected_matrix = create_matrix_from_file<6, 9>(is);
    is.close();
    ASSERT_EQ(lhs + rhs, expected_matrix);
}

TEST(MathOperation, SumRows) {
    fs::path data_path{glob_test_dir / "sum" };
    std::ifstream is(data_path / "in2.txt");  
    Matrix_row<8> lhs = create_matrix_from_file<1, 8>(is);
    Matrix_row<8> rhs = create_matrix_from_file<1, 8>(is);
    is.close();
    is.open(data_path/"out2.txt");
    Matrix_row<8> expected_matrix = create_matrix_from_file<1, 8>(is);
    is.close();
    ASSERT_EQ(lhs + rhs, expected_matrix);
}

TEST(MathOperation, SumCols) {
    fs::path data_path{glob_test_dir / "sum" };
    std::ifstream is(data_path / "in3.txt");  
    Matrix_col<6> lhs = create_matrix_from_file<6, 1>(is);
    Matrix_col<6> rhs = create_matrix_from_file<6, 1>(is);
    is.close();
    is.open(data_path/"out3.txt");
    Matrix_col<6> expected_matrix = create_matrix_from_file<6, 1>(is);
    is.close();
    ASSERT_EQ(lhs + rhs, expected_matrix);
}

TEST(MathOperation, SubMatrix) {
    fs::path data_path{glob_test_dir / "sub" };
    std::ifstream is(data_path / "in1.txt");  
    Matrix<6, 9> lhs = create_matrix_from_file<6, 9>(is);
    Matrix<6, 9> rhs = create_matrix_from_file<6, 9>(is);
    is.close();
    is.open(data_path/"out1.txt");
    Matrix<6, 9> expected_matrix = create_matrix_from_file<6, 9>(is);
    is.close();
    ASSERT_EQ(lhs - rhs, expected_matrix);
}

TEST(MathOperation, SubRows) {
    fs::path data_path{glob_test_dir / "sub" };
    std::ifstream is(data_path / "in2.txt");  
    Matrix_row<8> lhs = create_matrix_from_file<1, 8>(is);
    Matrix_row<8> rhs = create_matrix_from_file<1, 8>(is);
    is.close();
    is.open(data_path/"out2.txt");
    Matrix_row<8> expected_matrix = create_matrix_from_file<1, 8>(is);
    is.close();
    ASSERT_EQ(lhs - rhs, expected_matrix);
}

TEST(MathOperation, SubCols) {
    fs::path data_path{glob_test_dir / "sub" };
    std::ifstream is(data_path / "in3.txt");  
    Matrix_col<6> lhs = create_matrix_from_file<6, 1>(is);
    Matrix_col<6> rhs = create_matrix_from_file<6, 1>(is);
    is.close();
    is.open(data_path/"out3.txt");
    Matrix_col<6> expected_matrix = create_matrix_from_file<6, 1>(is);
    is.close();
    ASSERT_EQ(lhs - rhs, expected_matrix);
}


TEST(MathOperation, ElementWiseMultiplication) {
    fs::path data_path{glob_test_dir / "elemWiseMul" };
    std::ifstream is(data_path / "in.txt");  
    Matrix<5, 6> lhs = create_matrix_from_file<5, 6>(is);
    Matrix<5, 6> rhs = create_matrix_from_file<5, 6>(is);
    is.close();
    is.open(data_path/"out.txt");
    Matrix<5, 6> expected_matrix = create_matrix_from_file<5, 6>(is);
    is.close();
    ASSERT_EQ(rhs.mul_elem(lhs), expected_matrix);
}

TEST(MathOperation, MatrixSumNum) {
    fs::path data_path{glob_test_dir / "sum" };
    std::ifstream is(data_path / "in4.txt");  
    double val = 0;
    Matrix<4, 8> lhs = create_matrix_from_file<4, 8>(is);
    is >> val;
    is.close();
    is.open(data_path/"out4.txt");
    Matrix<4, 8> expected_matrix = create_matrix_from_file<4, 8>(is);
    is.close();
    ASSERT_EQ(lhs + val, expected_matrix);
}
TEST(MathOperation,MatrixSubNum) {
    fs::path data_path{glob_test_dir / "sub" };
    std::ifstream is(data_path / "in4.txt");  
    double val = 0;
    Matrix<4, 8> lhs = create_matrix_from_file<4, 8>(is);
    is >> val;
    is.close();
    is.open(data_path/"out4.txt");
    Matrix<4, 8> expected_matrix = create_matrix_from_file<4, 8>(is);
    is.close();
    ASSERT_EQ(lhs - val, expected_matrix);
}

TEST(MathOperation, MatrixSumRow) {
    fs::path data_path{glob_test_dir / "sum" };
    std::ifstream is(data_path / "in5.txt");  
    Matrix<3, 7> lhs = create_matrix_from_file<3, 7>(is);
    Matrix_row<7> rhs = create_matrix_from_file<1, 7>(is);
    is.close();
    is.open(data_path/"out5.txt");
    Matrix<3, 7> expected_matrix = create_matrix_from_file<3, 7>(is);
    is.close();
    ASSERT_EQ(lhs.sum_row(rhs), expected_matrix);
}

TEST(MathOperation, MatrixSumCol) {
    fs::path data_path{glob_test_dir / "sum" };
    std::ifstream is(data_path / "in6.txt");  
    Matrix<3, 7> lhs = create_matrix_from_file<3, 7>(is);
    Matrix_col<3> rhs = create_matrix_from_file<3, 1>(is);
    is.close();
    is.open(data_path/"out6.txt");
    Matrix<3, 7> expected_matrix = create_matrix_from_file<3, 7>(is);
    is.close();
    ASSERT_EQ(lhs.sum_col(rhs), expected_matrix);
}
