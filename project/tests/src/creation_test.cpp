#include "../include/utils.hpp"
#include <cstddef>
#include <gtest/gtest.h>
#include <array>

TEST(MatrixCreation, CreationFromNumbersArray) {
    fs::path data_path{glob_test_dir / "creation" / "in2.txt"};
    std::ifstream m_stream(data_path);  
    const MatrixData expected_matrix = create_matrix_data(m_stream, 3, 3);
    m_stream.seekg(0);
    std::array<double, 9> arr; 
    for (size_t i = 0; i < 9; i++) {
        m_stream >> arr[i];
    }
    const Matrix<3, 3> matrix(arr);
    m_stream.close();
    ASSERT_EQ(matrix, expected_matrix);
} 

TEST(MatrixCreation, CreationFromVectorsRows) {
    fs::path data_path{glob_test_dir / "creation" / "in3.txt"};
    std::ifstream m_stream(data_path);  
    const MatrixData expected_matrix = create_matrix_data(m_stream, 3, 4);
    m_stream.seekg(0);
    std::array<Matrix_row<4>, 3> arr;
    for (size_t i = 0; i < 3; i++) {
        Matrix_row<4> row = create_matrix_from_file<1, 4>(m_stream); 
        arr[i] = row;
    }
    const Matrix<3, 4> matrix(arr);
    m_stream.close();
    ASSERT_EQ(matrix, expected_matrix);
} 


TEST(MatrixCreation, CreationFromVectorsCollumns) {
    fs::path data_path{glob_test_dir / "creation"};
    std::ifstream m_stream(data_path / "in4.txt");  
    const MatrixData expected_matrix = create_matrix_data(m_stream, 7, 5);
    
    std::array<Matrix_col<7>, 5> arr;
    for (size_t i = 0; i < 5; i++) {
        arr[i] = create_matrix_from_file<7, 1>(m_stream); 
    }
    const Matrix<7, 5> matrix(arr);
    m_stream.close();
    ASSERT_EQ(matrix, expected_matrix);
} 
