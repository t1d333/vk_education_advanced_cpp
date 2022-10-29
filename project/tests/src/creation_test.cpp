#include <array>
#include <cstddef>
#include <gtest/gtest.h>
#include "../../include/Matrix.hpp"

TEST(MatrixCreation, CreationFromNumbersArray) {
    std::array<double, 9> arr {
        1, 6, 1,
        4, 8, 3,
        0, 1, 7
    };

    const Matrix<3, 3> matrix(arr);

    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 3; j++) {
            ASSERT_EQ(arr[3 * i + j], matrix(i, j));
        }
    }
} 
TEST(MatrixCreation, CreationFromInitializerList) {
    Matrix<2, 2> matrix{1, 2, 3, 4};
    Matrix<2, 2> expected_matrix;
    expected_matrix(0, 0) = 1;
    expected_matrix(0, 1) = 2;
    expected_matrix(1, 0) = 3;
    expected_matrix(1, 1) = 4;
    ASSERT_EQ(matrix, expected_matrix);
}
TEST(MatrixCreation, CreationFromVectorsRows) {
    Matrix<3, 4> expected_matrix{
        8, 8, 1, 8,
        6, 9, 0, 0,
        8, 6, 3, 7
    };

    std::array<Matrix_row<4>, 3> arr{
        Matrix_row<4>{8, 8, 1, 8},
        Matrix_row<4>{6, 9, 0, 0},
        Matrix_row<4>{8, 6, 3, 7}

    };

    Matrix<3, 4> matrix(arr);

    ASSERT_EQ(matrix, expected_matrix);
} 


TEST(MatrixCreation, CreationFromVectorsCollumns) {
    Matrix<7, 5> expected_matrix{
        6, 7, 6, 0, 5,
        7, 3, 1, 7, 4,
        4, 0, 0, 5, 6,
        3, 8, 3, 8, 6,
        8, 5, 3, 4, 2,
        8, 0, 6, 5, 1,
        7, 6, 2, 0, 8


    };
    std::array<Matrix_col<7>, 5> arr{
        Matrix_col<7>{6, 7, 4, 3, 8, 8, 7},
        Matrix_col<7>{7, 3, 0, 8, 5, 0, 6},
        Matrix_col<7>{6, 1,	0, 3, 3, 6, 2},
        Matrix_col<7>{0, 7, 5, 8, 4, 5, 0},
        Matrix_col<7>{5, 4, 6, 6, 2, 1, 8}
    };
    Matrix<7, 5> matrix(arr);
    ASSERT_EQ(matrix, expected_matrix);
} 
