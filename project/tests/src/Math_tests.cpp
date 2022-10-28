#include <array>
#include <cmath>
#include <cstddef>
#include <fstream>
#include <gtest/gtest.h>
#include "../../include/Matrix.hpp"

TEST(MathOperation, NumberMulMatrix) {
    Matrix<6, 4> m{
        9, 6, 9, 2,
        8, 3, 3, 3,
        5, 3, 8, 0,
        4, 1, 6, 9,
        6, 8, 0, 1,
        5, 2, 2, 1
    };

    Matrix<6, 4> expected_matrix {
        27, 18, 27, 6, 
        24, 9, 9, 9,
        15, 9, 24, 0,
        12, 3, 18, 27, 
        18, 24, 0, 3,
        15, 6, 6, 3
    };

    ASSERT_EQ(3 * m, expected_matrix);
}


TEST(MathOperation, MatrixMulVector) {
    Matrix<3, 3> m{
        5, 0, -2,
        -3, 9, 11,
        2, 1, -4
    };

    Matrix_col<3> vec{1, 2, 0};

    Matrix<3, 1> expected_matrix {
        5, 15, 4
    };

    ASSERT_EQ(m * vec, expected_matrix);
}

TEST(MathOperation, VecotrMulMatrix) {
    Matrix<4, 5> m{
        4, 1, 2, 0, 5,
        -1, 2, 4, 2, 3,
        0, 9, 1, -3, 5,
        1, 2, -1, -1, 0
    };

    Matrix_row<4> vec {
        0, 3, -1, 2
    };

    Matrix<1, 5> expected_matrix{
        -1, 1, 9, 7, 4
    };

    ASSERT_EQ(vec * m, expected_matrix);
}

TEST(MathOperation, MatrixMulMatrix) {
    Matrix<4, 3> m_lhs {
        1.61859, 3.05513, 4.49552,
        2.98206, 6.41512, 1.64534,
        2.74265, 5.39112, 0.97126,
        5.21710, 6.70646, 5.42605


    };

    Matrix<3, 5> m_rhs {
        9.52616, 0.76610, 2.14494, 6.16911, 5.02391,
        1.02554, 8.54165, 5.08077, 7.81675, 7.09314,
        8.12931, 3.07961, 4.60008, 0.59174, 7.39499
    };

    Matrix<4, 5> expected_matrix {
        55.0975810258,	41.1803013107,	39.6739429263,	36.5266261872,	63.0464407399,
        48.3620217698,	62.1472714314,	46.558784646,	69.5156589182,	72.652218178,
        39.5514055594,	51.1413063216,	37.7417341542,	59.6354801939,	59.2012536657,
        100.6867148499,	77.9911722095,	70.2246113322,  87.818395813,	113.9056860349
    }; 

    ASSERT_EQ(m_lhs * m_rhs, expected_matrix);
}


TEST(MathOperation, Transp) {
    Matrix<4, 9> m {
        1.73443, 6.30384, 7.20002, 5.96675, 9.30543, 5.63272, 4.25484, 2.24643, 8.92434,
        3.64763, 9.56482, 4.68632, 5.46693, 8.41862, 7.98930, 2.21218, 7.74186, 4.45247,
        1.12037, 4.43321, 2.46543, 2.61990, 1.27902, 0.14719, 0.12994, 4.22951, 8.97465,
        0.82242, 5.39112, 2.29931, 0.78042, 5.52166, 6.94291, 4.02020, 6.19071, 9.49697
    };

    Matrix<9, 4> expected_matrix {
        1.73443, 3.64763, 1.12037, 0.82242,
        6.30384, 9.56482, 4.43321, 5.39112,
        7.20002, 4.68632, 2.46543, 2.29931,
        5.96675, 5.46693, 2.6199,	0.78042,
        9.30543, 8.41862, 1.27902, 5.52166,
        5.63272, 7.9893, 0.14719, 6.94291,
        4.25484, 2.21218, 0.12994, 4.0202,
        2.24643, 7.74186, 4.22951, 6.19071,
        8.92434, 4.45247, 8.97465, 9.49697
    };

    ASSERT_EQ(m.transp(), expected_matrix);
}


TEST(MathOperation, Det) {
    Matrix<5, 5> m {
        -7, -7, -1, -10, -7,
        -7, 6, -2, 6, 9,
        -3, -4, 4, 5, 8,
        -6, 9, 2, 4, 5,
         2, 6, 0, -2, -2
    }; 
    
    ASSERT_NEAR(17508, m.det(), 1e-7);
}


TEST(MathOperation, Inv) {
    Matrix<3, 3> m {
        7, 6, -1,
        9, 5, 5,
        3, -8, 9,
    }; 
 
   Matrix<3, 3> expected_matrix {
       0.29720279720279720279,	-0.16083916083916083919,	0.12237762237762237763,
       -0.23076923076923076927,	0.23076923076923076931,	-0.15384615384615384618,
        -0.30419580419580419582,	0.2587412587412587413,	-0.066433566433566433579
   };

    ASSERT_EQ(m.inv(), expected_matrix);
}

TEST(MathOperation, SumMatrix) {

    Matrix<5, 5> lhs {
        67, -7, 29, -33, -46, 
        -40, 65, -8, 46, -48,
        -47, 75, 82, 42, 14,
        -33, -46, 67, -38, 6,
        71, -32, 45, 30, 46

    };

    Matrix<5, 5> rhs {
        69, 23, -19, -36, -30,
        78, 100, -9, 57, 6,
        63, -22, -9, -27, -15,
        -29, 79, 96, 98, -33,
        90, 20, 36, 48, 90 
    };

    Matrix<5, 5> expected_matrix {
        136, 16, 10, -69, -76,
        38,	165, -17, 103, -42,
        16, 53,	73,	15,	-1,
        -62, 33, 163, 60, -27,
        161, -12, 81, 78, 136
    };

    ASSERT_EQ(lhs + rhs, expected_matrix);
}

TEST(MathOperation, SumRows) {

    Matrix_row<8> lhs{
        -40, -34, -30, -48, 15, -30, -41, 77
    };

    Matrix_row<8> rhs {
        39, -33, 12, -23, 6, 64, -49, 30
    }; 

    Matrix_row<8> expected_matrix {
        -1,	-67, -18, -71,	21,	34,	-90, 107
    }; 

    ASSERT_EQ(lhs + rhs, expected_matrix);
}

TEST(MathOperation, SumCols) {

    Matrix_col<6> lhs {
        45,
        48,
        19,
        42,
        -31,
        53,


    };

    Matrix_col<6> rhs {
        44,
        -2,
        -42,
        86,
        -13,
        5
    };

    Matrix_col<6> expected_matrix {
        89,
        46,
        -23,
        128,
        -44,
        58
    }; 

    ASSERT_EQ(lhs + rhs, expected_matrix);
}

TEST(MathOperation, SubMatrix) {
    Matrix<5, 5> lhs {
        67, -7, 29, -33, -46, 
        -40, 65, -8, 46, -48,
        -47, 75, 82, 42, 14,
        -33, -46, 67, -38, 6,
        71, -32, 45, 30, 46

    };

    Matrix<5, 5> rhs {
        69, 23, -19, -36, -30,
        78, 100, -9, 57, 6,
        63, -22, -9, -27, -15,
        -29, 79, 96, 98, -33,
        90, 20, 36, 48, 90 
    };

    Matrix<5, 5> expected_matrix {
        -2,	-30, 48,	3, -16,
        -118,	-35, 1, -11, -54,
        -110,	97,	91,	69,	29,
        -4,	-125, -29, -136, 39,
        -19, -52, 9, -18, -44,
    };

    ASSERT_EQ(lhs - rhs, expected_matrix);
}

TEST(MathOperation, SubRows) {

    Matrix_row<8> lhs{
        -40, -34, -30, -48, 15, -30, -41, 77
    };

    Matrix_row<8> rhs {
        39, -33, 12, -23, 6, 64, -49, 30
    }; 
    Matrix_row<8> expected_matrix {
        -79, -1, -42, -25,	9,	-94, 8,	47
    };

    ASSERT_EQ(lhs - rhs, expected_matrix);
}

TEST(MathOperation, SubCols) {

    Matrix_col<6> lhs {
        45,
        48,
        19,
        42,
        -31,
        53,


    };

    Matrix_col<6> rhs {
        44,
        -2,
        -42,
        86,
        -13,
        5
    };

    Matrix_col<6> expected_matrix {
        1,
        50,
        61,
        -44,
        -18,
        48
    }; 

    ASSERT_EQ(lhs - rhs, expected_matrix);
}


TEST(MathOperation, ElementWiseMultiplication) {
    Matrix<5, 6> lhs {
        -10, -8, -9, 9, 6, -7,
        5, 7, -1, 10, -9, -8,
        2, 7, 6, 6, -3, 6,
        -8, 8, 10, -1, 6, -1,
        -8, 9, 0, -8, -2, 10,
    };

    Matrix<5, 6> rhs {
        2, 2, 2, 2, 2, 2,
        2, 2, 2, 2, 2, 2,
        2, 2, 2, 2, 2, 2,
        2, 2, 2, 2, 2, 2,
        2, 2, 2, 2, 2, 2
    };

    Matrix<5, 6> expected_matrix  {
        -20, -16, -18, 18, 12, -14,
        10, 14, -2, 20, -18, -16,
        4, 14, 12, 12, -6, 12, 
        -16, 16, 20, -2, 12, -2,
        -16, 18, 0, -16, -4, 20
    };

    ASSERT_EQ(rhs.mul_elem(lhs), expected_matrix);
}

TEST(MathOperation, MatrixSumNum) {
    double val = 10;
    Matrix<4, 4> lhs {
        4, 3, 2, -1, 
        -1, 23, 3, 3,
        3, -10, 90, 90, 
        -30, 12, 12, -11
    };

    Matrix<4, 4> expected_matrix {
        14, 13, 12, 9,
        9, 33, 13, 13, 
        13, 0, 100, 100, 
        -20, 22, 22, -1, 
    };

    ASSERT_EQ(lhs + val, expected_matrix);
}
TEST(MathOperation,MatrixSubNum) {
    double val = 10;

    Matrix<4, 4> lhs {
        4, 3, 2, -1, 
        -1, 23, 3, 3,
        3, -10, 90, 90, 
        -30, 12, 12, -11
    };

    Matrix<4, 4> expected_matrix {
        -6, -7, -8, -11,
        -11, 13, -7, -7,
        -7, -20, 80, 80,
        -40, 2, 2, -21
    };
    ASSERT_EQ(lhs - val, expected_matrix);
}

TEST(MathOperation, MatrixSumRow) {
    Matrix<3, 7> lhs {
        3, 21,  31, 1, 22,  4, -3, 
        10, 11, 2, 0, 3, 2, 31,
        -10, 0, 0, 3, -2, -2, -3
    };

    Matrix_row<7> rhs {
        1, 2, 3, 2, 1, -1, 0
    };

    Matrix<3, 7> expected_matrix {
        4,  23, 34, 3, 23,  3, -3, 
        11, 13, 5,  2, 4,  1, 31,
        -9, 2,  3,  5, -1, -3, -3
    };

    ASSERT_EQ(lhs.sum_row(rhs), expected_matrix);
}

TEST(MathOperation, MatrixSumCol) {
    Matrix<3, 7> lhs {
        3, 21, 31, 1, 22, 4, -3, 
        10, 11, 2, 0, 3, 2, 31,
        -10, 0, 0, 3, -2, -2, -3,
    };

    Matrix_col<3> rhs {
        1, 2, 3 
    };

    Matrix<3, 7> expected_matrix {
        4, 22,  32, 2, 23,  5, -2, 
        12, 13, 4, 2, 5, 4, 33,
        -7, 3, 3, 6, 1, 1, 0
    };

    ASSERT_EQ(lhs.sum_col(rhs), expected_matrix);
}
