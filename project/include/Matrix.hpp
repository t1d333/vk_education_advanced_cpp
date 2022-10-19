#ifndef PROJECT_INCLUDE_MATRIX_HPP_
#define PROJECT_INCLUDE_MATRIX_HPP_
#include <array>
#include <cstddef>
#include <iostream>
#include <istream>

template<size_t rows, size_t cols>
class Matrix {
 private:
    double* buffer;
    double* get_matrix_winthout_row_and_col(const double* buf, size_t rows_size,
    size_t cols_size, size_t row, size_t col) const;
    double get_minor(const double* buf, size_t rows_size, size_t cols_size, size_t row, size_t col) const;

 public:
    static constexpr double Epsilon = 1e-7;

    // Constructors
    Matrix(): buffer(new double[rows* cols]) {}

    Matrix(const Matrix<rows, cols> &other);
    explicit Matrix(std::istream &is);

    template<size_t rows_other, size_t cols_other, size_t count>
    explicit Matrix(const std::array<Matrix<rows_other, cols_other>, count> &arr);

    template<size_t count>
    explicit Matrix(const std::array<double, count> &arr);

    // Operators

    Matrix<rows, cols>& operator=(const Matrix<rows, cols> &rhs);

    double operator()(size_t i, size_t j) const;
    double &operator()(size_t i, size_t j);

    template<size_t rows_other, size_t cols_other>
    bool operator==(const Matrix<rows_other, cols_other> &other);

    template<size_t rows_rhs, size_t cols_rhs>
    Matrix<rows, cols> operator+(const Matrix<rows_rhs, cols_rhs> &rhs) const;

    template<size_t rows_rhs, size_t cols_rhs>
    Matrix<rows, cols> operator-(const Matrix<rows_rhs, cols_rhs> &rhs) const;

    template<size_t rows_rhs, size_t cols_rhs>
    Matrix<rows, cols_rhs> operator*(const Matrix<rows_rhs, cols_rhs> &rhs) const;

    template<size_t rows_rhs, size_t cols_rhs>
    Matrix<rows, cols>& operator+=(const Matrix<rows_rhs, cols_rhs> &rhs);

    template<size_t rows_rhs, size_t cols_rhs>
    Matrix<rows, cols>& operator-=(const Matrix<rows_rhs, cols_rhs> &rhs);

    template<size_t rows_rhs, size_t cols_rhs>
    Matrix<rows, cols_rhs>& operator*=(const Matrix<rows_rhs, cols_rhs> &rhs);
    // Getters
    Matrix<1, cols> get_row(size_t n) const;
    Matrix<rows, 1> get_col(size_t n) const;
    Matrix<rows, cols> get_diag() const;

    // Multiplication
    template<size_t rows_other, size_t cols_other>
    Matrix<rows, cols> mul_elem(const Matrix<rows_other, cols_other> &other);

    // Matrix operations
    Matrix<cols, rows> transp() const;
    Matrix<rows, cols> adj() const;
    Matrix<rows, cols> inv() const;
    double det() const;

    // Destructor
    ~Matrix() {delete[] buffer;}
};

#include "../src/Matrix.cpp"
#endif  // PROJECT_INCLUDE_MATRIX_HPP_
