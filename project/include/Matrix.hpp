#pragma once  // NOLINT
#include <array>
#include <cstddef>
#include <iostream>
#include <istream>


template<size_t rows, size_t cols>
class Matrix;

template<size_t cols>
using Matrix_row = Matrix<1, cols>;

template<size_t rows>
using Matrix_col = Matrix<rows, 1>;

template<size_t rows, size_t cols>
class Matrix {
 private:
    std::array<double, rows * cols> buffer;

    double* get_matrix_winthout_row_and_col(const double* buf, size_t rows_size,
    size_t cols_size, size_t row, size_t col) const;
    double get_minor(const double* buf, size_t rows_size, size_t cols_size, size_t row, size_t col) const;

 public:

    // Constructors
    Matrix() = default;

    Matrix(const Matrix<rows, cols> &other);

    template<size_t cols_other, size_t count>
    explicit Matrix(const std::array<Matrix_row<cols_other>, count> &arr);

    template<size_t rows_other, size_t count>
    explicit Matrix(const std::array<Matrix_col<rows_other>, count> &arr);

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

    Matrix<rows, cols> operator+(double val) const;
    Matrix<rows, cols>& operator+=(double val);

    Matrix<rows, cols> operator-(double val) const;
    Matrix<rows, cols>& operator-=(double val);
    // Getters
    Matrix_row<cols> get_row(size_t n) const;
    Matrix_col<rows> get_col(size_t n) const;
    Matrix_col<rows> get_diag() const;
    // Multiplication
    template<size_t rows_other, size_t cols_other>
    Matrix<rows, cols> mul_elem(const Matrix<rows_other, cols_other> &other) const;
    // Matrix operations
    template<size_t dim>
    Matrix<rows, cols> sum_row(Matrix_row<dim> row) const;

    template<size_t dim>
    Matrix<rows, cols> sum_col(Matrix_col<dim> col) const;

    template<size_t dim>
    Matrix<rows, cols> sub_row(Matrix_row<dim> row) const;

    template<size_t dim>
    Matrix<rows, cols> sub_col(Matrix_col<dim> col) const;


    Matrix<cols, rows> transp() const;
    Matrix<rows, cols> adj() const;
    Matrix<rows, cols> inv() const;
    double det() const;

    // Destructor
    ~Matrix() = default;
};

#include "../src/Matrix.cpp"
