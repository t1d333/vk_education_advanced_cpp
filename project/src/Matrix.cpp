#include <array>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <istream>
#include <iterator>
#include <stdexcept>
#include <limits>
#include <iomanip>

template<size_t rows, size_t cols>
Matrix<rows, cols>::Matrix(const Matrix<rows, cols> &other) {
    std::copy(other.buffer.begin(), other.buffer.end() , buffer.begin());
}

template<size_t rows, size_t cols>
Matrix<rows, cols>& Matrix<rows, cols>::operator=(const Matrix<rows, cols> &rhs) {
    if (this != &rhs) {
        std::copy(rhs.buffer.begin(), rhs.buffer.end(), buffer.begin());
    }
    return *this;
}

template<size_t rows, size_t cols>
template<size_t cols_other, size_t count>
Matrix<rows, cols>::Matrix(const std::array<Matrix_row<cols_other>, count> &arr) {
    if ((cols_other != cols) || (count != rows)) {
        throw std::runtime_error("Failed to create matrix");
    }

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            buffer[i * cols + j] = arr[i](0, j);
        }
    }
}

template<size_t rows, size_t cols>
template<size_t rows_other, size_t count>
Matrix<rows, cols>::Matrix(const std::array<Matrix_col<rows_other>, count> &arr) {
    if ((rows_other != rows) || (cols != count)) {
        throw std::runtime_error("Failed to create matrix");
    }

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            buffer[i * cols + j] = arr[j](i, 0);
        }
    }
}


template<size_t rows, size_t cols>
template<size_t count>
Matrix<rows, cols>::Matrix(const std::array<double, count> &arr) {
    if (count != rows * cols) {
        throw "Failed to create matrix from numbers";
    }
    std::copy(arr.begin(), arr.end(), buffer.begin());
}


template<size_t rows, size_t cols, size_t rows_other, size_t cols_other>
bool operator==(const Matrix<rows, cols> &lhs, const Matrix<rows_other, cols_other> &rhs) {
    bool flag = ((rows == rows_other) && (cols == cols_other));

    if (flag) {
        for (size_t i = 0; i <  rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                if (std::fabs(lhs(i, j) - rhs(i, j)) > 1e-6) {
                    return false;
                }
            }
        }
    }

    return flag;
}

template<size_t rows, size_t cols>
double& Matrix<rows, cols>::operator()(size_t i, size_t j) {
    if ((i > rows) || (j > cols)) {
        throw std::out_of_range("Indexes out of range");
    }
    return buffer[i * cols + j];
}

template <size_t rows, size_t cols>
double Matrix<rows, cols>::operator()(size_t i, size_t j) const {
    return buffer[i * cols + j];
}

template<size_t rows, size_t cols>
Matrix<rows, cols> operator*(double val, const Matrix<rows, cols>& matrix) {
    Matrix<rows, cols> result;
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            result(i, j) = matrix(i, j)  * val;
        }
    }
    return result;
}


template<size_t rows, size_t cols>
Matrix<rows, cols> operator*(const Matrix<rows, cols>& matrix, double val) {
    return val * matrix;
}


template<size_t rows, size_t cols>
Matrix<rows, cols> Matrix<rows, cols>::operator+(const Matrix<rows, cols> &rhs) const {
    Matrix<rows, cols> result;
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            result(i, j) = (*this)(i, j) + rhs(i, j);
        }
    }
    return result;
}


template<size_t rows, size_t cols>
Matrix<rows, cols> Matrix<rows, cols>::mul_elem(const Matrix<rows, cols> &other) const {
    Matrix<rows, cols> result;
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            result(i, j) = (*this)(i, j) * other(i, j);
        }
    }
    return result;
}


template<size_t rows, size_t cols>
Matrix<rows, cols> Matrix<rows, cols>::operator-(const Matrix<rows, cols> &rhs) const {
    return *this + (-1) * rhs;
}

template<size_t rows, size_t cols>
Matrix<rows, cols> Matrix<rows, cols>::operator+(double val) const {
    Matrix<rows, cols> result;

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            result(i, j) = (*this)(i, j) + val;
        }
    }

    return result;
}

template<size_t rows, size_t cols>
Matrix<rows, cols> operator+(double val, const Matrix<rows, cols>& m) {
    return m + val;
}

template<size_t rows, size_t cols>
Matrix<rows, cols>& Matrix<rows, cols>::operator+=(double val) {
    return (*this = *this + val);
}

template<size_t rows, size_t cols>
Matrix_row<cols> Matrix<rows, cols>::get_row(size_t n) const {
    Matrix_row<cols> result;
    for (size_t i = 0; i < cols; i++) {
        result(0, i) = buffer[n * cols + i];
    }
    return result;
}

template<size_t rows, size_t cols>
Matrix<rows, cols> Matrix<rows, cols>::operator-(double val) const {
    return *this + (-1) * val;
}

template<size_t rows, size_t cols>
Matrix<rows, cols> operator-(double val, const Matrix<rows, cols>& m) {
    return (-1) * m + val;
}

template<size_t rows, size_t cols>
Matrix<rows, cols>& Matrix<rows, cols>::operator-=(double val) {
    return (*this = *this - val);
}

template<size_t rows, size_t cols>
template<size_t dim>
Matrix<rows, cols> Matrix<rows, cols>::sum_row(Matrix_row<dim> row) const {
    if (dim != cols) {
        throw std::runtime_error("Dimension mismatch");
    }
    Matrix<rows, cols> result;
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            result(i, j) = (*this)(i, j) + row(0, j);
        }
    }
    return result;
}

template<size_t rows, size_t cols>
template<size_t dim>
Matrix<rows, cols> Matrix<rows, cols>::sum_col(Matrix_col<dim> col) const {
    if (dim != rows) {
        throw std::runtime_error("Dimension mismatch");
    }
    Matrix<rows, cols> result;
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            result(i, j) = (*this)(i, j) + col(i, 0);
        }
    }
    return result;
}


template<size_t rows, size_t cols>
Matrix_col<rows> Matrix<rows, cols>::get_col(size_t n) const {
    Matrix_col<rows> result;
    for (size_t i = 0; i < rows; i++) {
        result(i, 0) = buffer[i * cols + n];
    }
    return result;
}


template<size_t rows, size_t cols>
Matrix_col<rows> Matrix<rows, cols>::get_diag() const {
    if (rows != cols) {
        throw std::runtime_error("Invalid matrix");
    }
    Matrix_col<rows>result;
    for (size_t i = 0; i < rows; i++) {
            result(i, 0) = (*this)(i, i);
    }
    return result;
}



template<size_t rows, size_t cols>
template<size_t cols_rhs>
Matrix<rows, cols_rhs> Matrix<rows, cols>::operator*(const Matrix<cols, cols_rhs> &rhs) const {
    Matrix<rows, cols_rhs> result;
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols_rhs; j++) {
            result(i, j) = 0;
            for (size_t k = 0; k < cols; k++) {
                result(i, j) += (*this)(i, k) * rhs(k, j);
            }
        }
    }
    return result;
}


template<size_t rows, size_t cols>
Matrix<rows, cols>& Matrix<rows, cols>::operator+=(const Matrix<rows, cols> &rhs) {
    return *this = *this + rhs;
}


template<size_t rows, size_t cols>
Matrix<rows, cols>& Matrix<rows, cols>::operator-=(const Matrix<rows, cols> &rhs) {
    return *this = *this - rhs;
}


template<size_t rows, size_t cols>
template<size_t cols_rhs>
Matrix<rows, cols_rhs>& Matrix<rows, cols>::operator*=(const Matrix<cols, cols_rhs> &rhs) {
    return *this = *this * rhs;
}


template<size_t rows, size_t cols>
Matrix<cols, rows> Matrix<rows, cols>::transp() const {
    Matrix<cols, rows> result;
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            result(j, i) = (*this)(i, j);
        }
    }
    return result;
}

template<size_t rows, size_t cols>
Matrix<rows - 1, cols - 1> Matrix<rows, cols>::get_matrix_winthout_row_and_col(size_t row, size_t col) const {
    Matrix<rows - 1, cols - 1> result;
    size_t offset_y = 0;
    for (size_t i = 0; i < rows - 1; i++) {
        if (i == row) {
            offset_y = 1;
        }

        size_t offset_x = 0;
        for (size_t j = 0; j < cols - 1; j++) {
            if (j == col) {
                offset_x = 1;
            }
            result(i, j) = (*this)(i + offset_y, j + offset_x);
        }
    }
    return result;
}


template<size_t rows, size_t cols>
std::ostream& operator<<(std::ostream &os, const Matrix<rows, cols> &matrix) {
    os << rows << " " << cols << std::endl;
    for (size_t i = 0; i < rows; i++) {
        size_t j;
        for (j = 0; j < cols - 1; j++) {
            os << std::setprecision(std::numeric_limits<double>::max_digits10) << matrix(i, j) << " ";
        }
        os << std::setprecision(std::numeric_limits<double>::max_digits10) << matrix(i, j) << std::endl;
    }
    return os;
}
template<size_t rows, size_t cols>
double Matrix<rows, cols>::get_minor(size_t row, size_t col) const {
    return get_matrix_winthout_row_and_col(row, col).det();
}

template<size_t rows, size_t cols>
void Matrix<rows, cols>::swap_rows(size_t row1, size_t row2) {
    for (size_t i = 0; i < cols; i++) {
        std::swap((*this)(row1, i), (*this)(row2, i));
    }
}

template<size_t rows, size_t cols>
double Matrix<rows, cols>::det() const {
    double res = 1;
    Matrix<rows, cols> tmp(*this);
    for (size_t i = 0; i < rows - 1; i++) {
        size_t j = i;
        if (tmp(i, i) == 0) {
            for (; (tmp(j, i) == 0) && (j < rows); j++) {}

            if (tmp(j, i) == 0) {
                continue;
            }

            tmp.swap_rows(i, j);
        }

        for (j = i + 1; j < rows; j++) {
            double mul = tmp(j, i) / tmp(i, i);
            for (size_t k = 0; k < cols; k++) {
               tmp(j, k) -= tmp(i, k) * mul;
            }
        }
    }

    for (size_t i = 0; i < rows; i++) {
        res *= tmp(i, i);
    }

    return res;
}

template<size_t rows, size_t cols>
Matrix<rows, cols> Matrix<rows, cols>::inv() const {
    double d = det();

    if (d == 0) {
        throw std::runtime_error("Singulal matrix");
    }

    return adj() * (1 / d);
}


template<size_t rows, size_t cols>
Matrix<rows, cols> Matrix<rows, cols>::adj() const {
    Matrix<rows, cols>  result;
    double deg = 1;
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            result(i, j) = deg * get_minor(j, i);
            deg *= -1;
        }
        deg *= -1;
    }
    return result;
}
