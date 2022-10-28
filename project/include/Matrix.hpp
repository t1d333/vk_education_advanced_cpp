#pragma once  // NOLINT
#include <array>
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <istream>
#include <vector>

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

    Matrix<rows - 1, cols - 1> get_matrix_winthout_row_and_col(size_t row, size_t col) const;


    double get_minor(size_t row, size_t col) const;

 public:
    // Constructors
    Matrix() = default;

    Matrix(const Matrix<rows, cols> &other);

    explicit Matrix(const std::array<Matrix_row<cols>, rows> &arr);

    explicit Matrix(const std::array<Matrix_col<rows>, cols> &arr);

    explicit Matrix(const std::array<double, rows * cols> &arr);

    explicit Matrix(std::initializer_list<double> list);

    // Operators

    Matrix<rows, cols>& operator=(const Matrix<rows, cols> &rhs);

    double operator()(size_t i, size_t j) const;
    double& operator()(size_t i, size_t j);


    Matrix<rows, cols> operator+(const Matrix<rows, cols> &rhs) const;

    Matrix<rows, cols> operator-(const Matrix<rows, cols> &rhs) const;

    template<size_t cols_rhs>
    Matrix<rows, cols_rhs> operator*(const Matrix<cols, cols_rhs> &rhs) const;

    Matrix<rows, cols>& operator+=(const Matrix<rows, cols> &rhs);

    Matrix<rows, cols>& operator-=(const Matrix<rows, cols> &rhs);

    template<size_t cols_rhs>
    Matrix<rows, cols_rhs>& operator*=(const Matrix<cols, cols_rhs> &rhs);

    Matrix<rows, cols> operator+(double val) const;
    Matrix<rows, cols>& operator+=(double val);

    std::vector<double> slice(size_t i, size_t j, int k) const;

    std::vector<double> slice(size_t i, size_t j) const;

    std::vector<double> slice(size_t i) const;

    Matrix<rows, cols> operator-(double val) const;
    Matrix<rows, cols>& operator-=(double val);
    // Getters
    Matrix_row<cols> get_row(size_t n) const;
    Matrix_col<rows> get_col(size_t n) const;
    std::array<double, rows> get_diag() const;
    // Multiplication
    Matrix<rows, cols> mul_elem(const Matrix<rows, cols> &other) const;
    // Matrix operations
    template<size_t dim>
    Matrix<rows, cols> sum_row(Matrix_row<dim> row) const;

    template<size_t dim>
    Matrix<rows, cols> sum_col(Matrix_col<dim> col) const;

    template<size_t dim>
    Matrix<rows, cols> sub_row(Matrix_row<dim> row) const;

    template<size_t dim>
    Matrix<rows, cols> sub_row(Matrix_row<dim> row, size_t num) const;

    template<size_t dim>
    Matrix<rows, cols> sub_col(Matrix_col<dim> col) const;

    void swap_rows(size_t row1, size_t row2);

    Matrix<cols, rows> transp() const;
    Matrix<rows, cols> adj() const;
    Matrix<rows, cols> inv() const;
    double det() const;
    // Destructor
    ~Matrix() = default;
};

#include "../src/Matrix.cpp"
