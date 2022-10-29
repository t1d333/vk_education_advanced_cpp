#include <array>
#include <cmath>
#include <cstddef>
#include <fstream>
#include <gtest/gtest.h>
#include <vector>
#include "../../include/Matrix.hpp"

TEST(GettersTest, GetElem) {
    Matrix<4, 6> m{3, 4, 21, 31, 321, 3,
                   1, 0, 9, -2, 8, -10,
                   7, -56, 43, 23, 1, -11,
                   23, 44, -9, 87, 13, 43

    };

    ASSERT_EQ(m(3, 4), 13);
}

TEST(GettersTest, GetRow) {
    Matrix<4, 5> m{
        23, -2, 31, 1, 10,
        90, 84, 12, 7, 777,
        228, 3, 3,  4, -9,
        12,  3, 4, -3, -3,
    };

    Matrix_row<5> expected_row{
        228, 3, 3,  4, -9
    };

    ASSERT_EQ(expected_row, m.get_row(2));
}

TEST(GettersTest, GetCol) {
    Matrix<6, 4> m{
        3, 12, 3, 432,
        -90, 21, 2, 31,
        100, -21, 3,  43,
        89, 77, 64, 34,
        -71, -13, -12, 11,
        32, 21, 32, 32
    };

    Matrix_col<6> expected_col{
        3, -90, 100, 89, -71, 32 
    };

    ASSERT_EQ(expected_col, m.get_col(0));
}

TEST(GettersTest, GetDiag) {
    Matrix<5, 5> m{
        3, -10, 2, 4, 45,
        -1, 2, 0, 19, 23,
        10, -1, -3, 12, 12,
        63, 23, -16, -90, 0,
        17, 12, -13, -10, 0
    };

    std::array<double, 5> expected_diag{
        3, 2, -3, -90, 0
    };

    ASSERT_EQ(expected_diag, m.get_diag());
}

TEST(GettersTest, Slice1) {
    Matrix<3, 3> m {
        1, 2, 3,
        4, 5, 6,
        7, 8, 10
    };
    std::vector<double> expected {1, 4, 7};
    ASSERT_EQ(m.slice(0, 9, 3), expected);
}


TEST(GettersTest, Slice2) {
    Matrix<3, 3> m {
        1, 2, 3,
        4, 5, 6,
        7, 8, 10
    };
    std::vector<double> expected {5, 4, 3, 2};
    ASSERT_EQ(m.slice(4,  0, -1), expected);
}

TEST(GettersTest, Slice3) {
    Matrix<3, 3> m {
        1, 2, 3,
        4, 5, 6,
        7, 8, 10
    };
    std::vector<double> expected {4, 5, 6, 7};
    ASSERT_EQ(m.slice(3,  7), expected);
}

TEST(GettersTest, Slice4) {
    Matrix<3, 3> m {
        1, 2, 3,
        4, 5, 6,
        7, 8, 10
    };
    std::vector<double> expected {7, 8, 10};
    ASSERT_EQ(m.slice(6), expected);
}

TEST(GettersTest, Slice5) {
    Matrix<3, 3> m {
        1, 2, 3,
        4, 5, 6,
        7, 8, 10
    };
    std::vector<double> expected {1, 3, 5, 7};
    ASSERT_EQ(m.slice(0, 7, 2), expected);
}
TEST(GettersTest, SliceRows1) {
    Matrix<5, 3> m {
        1, 2, 3,
        4, 5, 6,
        7, 8, 10,
        11, 12, 13,
        14, 14, 15
    };
    std::vector<Matrix_row<3>> expected(2);
    expected[0] = Matrix_row<3>{1, 2, 3};
    expected[1] = Matrix_row<3>{11, 12, 13};
    ASSERT_EQ(m.slice_row(0, 5, 3), expected);
}


TEST(GettersTest, SliceRows2) {
    Matrix<5, 3> m {
        1, 2, 3,
        4, 5, 6,
        7, 8, 10,
        11, 12, 13,
        14, 14, 15
    };
    std::vector<Matrix_row<3>> expected(2);
    expected[0] = Matrix_row<3>{7, 8, 10};
    expected[1] = Matrix_row<3>{4, 5, 6};
    ASSERT_EQ(m.slice_row(2, 0, -1), expected);
}

TEST(GettersTest, SliceRows3) {
    Matrix<5, 3> m {
        1, 2, 3,
        4, 5, 6,
        7, 8, 10,
        11, 12, 13,
        14, 14, 15
    };
    std::vector<Matrix_row<3>> expected(2);
    expected[0] = Matrix_row<3>{11, 12, 13};
    expected[1] = Matrix_row<3>{14, 14, 15};
    ASSERT_EQ(m.slice_row(3, 5), expected);
}

TEST(GettersTest, SliceRows4) {
    Matrix<5, 3> m {
        1, 2, 3,
        4, 5, 6,
        7, 8, 10,
        11, 12, 13,
        14, 14, 15
    };
    std::vector<Matrix_row<3>> expected(1);
    expected[0] = Matrix_row<3>{14, 14, 15};
    ASSERT_EQ(m.slice_row(4), expected);
}

TEST(GettersTest, SliceCols1) {
    Matrix<3, 5> m {
        1, 2, 3, 4, 5,
        6, 7, 8, 9, 10, 
        11, 12, 13, 14, 15
    };
    std::vector<Matrix_col<3>> expected(2);
    expected[0] = Matrix_col<3>{1, 6, 11};
    expected[1] = Matrix_col<3>{4, 9, 14};
    ASSERT_EQ(m.slice_col(0, 5, 3), expected);
}


TEST(GettersTest, SliceCols2) {
    Matrix<3, 5> m {
        1, 2, 3, 4, 5,
        6, 7, 8, 9, 10, 
        11, 12, 13, 14, 15
    };
    std::vector<Matrix_col<3>> expected(2);
    expected[0] = Matrix_col<3>{5, 10, 15};
    expected[1] = Matrix_col<3>{4, 9, 14};
    ASSERT_EQ(m.slice_col(4, 2, -1), expected);
}

TEST(GettersTest, SliceCols3) {
    Matrix<3, 5> m {
        1, 2, 3, 4, 5,
        6, 7, 8, 9, 10, 
        11, 12, 13, 14, 15
    };
    std::vector<Matrix_col<3>> expected(3);
    expected[0] = Matrix_col<3>{3, 8, 13};
    expected[1] = Matrix_col<3>{4, 9, 14};
    expected[2] = Matrix_col<3>{5, 10, 15};
    ASSERT_EQ(m.slice_col(2, 5), expected);
}

TEST(GettersTest, SliceCols4) {
    Matrix<3, 5> m {
        1, 2, 3, 4, 5,
        6, 7, 8, 9, 10, 
        11, 12, 13, 14, 15
    };
    std::vector<Matrix_col<3>> expected(2);
    expected[0] = Matrix_col<3>{4, 9, 14};
    expected[1] = Matrix_col<3>{5, 10, 15};
    ASSERT_EQ(m.slice_col(3), expected);
}
