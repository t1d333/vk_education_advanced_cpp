#include "../include/utils.hpp"
#include <cstddef>
#include <gtest/gtest.h>
#include <array>

TEST(MatrixCreation, CreationFromFile) {
    fs::path data_path{glob_test_dir / "creation" / "in1.txt"};
    std::ifstream m_stream(data_path);  
    const MatrixData expected_matrix = createMatrixData(m_stream, 3, 3);
    m_stream.seekg(0);
    const Matrix<3, 3> matrix(m_stream);
    m_stream.close();
    ASSERT_EQ(matrix, expected_matrix);
} 


TEST(MatrixCreation, CreationFromNumbersArray) {
    fs::path data_path{glob_test_dir / "creation" / "in2.txt"};
    std::ifstream m_stream(data_path);  
    const MatrixData expected_matrix = createMatrixData(m_stream, 3, 3);
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
    const MatrixData expected_matrix = createMatrixData(m_stream, 3, 4);
    m_stream.seekg(0);
    std::array<Matrix<1, 4>, 3> arr;
    for (size_t i = 0; i < 3; i++) {
        Matrix<1, 4> vec(m_stream); 
        arr[i] = vec;
    }
    const Matrix<3, 4> matrix(arr);
    m_stream.close();
    ASSERT_EQ(matrix, expected_matrix);
} 


TEST(MatrixCreation, CreationFromVectorsCollumns) {
    fs::path data_path{glob_test_dir / "creation"};
    std::ifstream m_stream(data_path / "in4.txt");  
    const MatrixData expected_matrix = createMatrixData(m_stream, 7, 5);
    m_stream.close();

    std::ifstream m_transp_stream(data_path / "in4_transp.txt");  
    
    std::array<Matrix<7, 1>, 5> arr;
    for (size_t i = 0; i < 5; i++) {
        Matrix<7, 1> vec(m_transp_stream); 
        arr[i] = vec;
    }
    const Matrix<7, 5> matrix(arr);
    m_transp_stream.close();
    ASSERT_EQ(matrix, expected_matrix);
} 
