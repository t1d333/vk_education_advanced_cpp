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


template<size_t rows, size_t cols>
template<size_t rows_other, size_t cols_other>
bool Matrix<rows, cols>::operator==(const Matrix<rows_other, cols_other> &other) {
    const double Epsilon = 1e-7;
    bool flag = ((rows == rows_other) && (cols == cols_other));
    if (flag) {
        for (size_t i = 0; i < cols * rows; i++) {
            if (std::fabs(buffer[i] - other.buffer[i]) > Epsilon) {
                return false;
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
template<size_t rows_rhs, size_t cols_rhs>
Matrix<rows, cols> Matrix<rows, cols>::operator+(const Matrix<rows_rhs, cols_rhs> &rhs) const {
    if ((rows_rhs != rows) || (cols_rhs != cols)) {
        throw std::runtime_error("Dimension mismatch");
    }
    Matrix<rows, cols> result;
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            result(i, j) = (*this)(i, j) + rhs(i, j);
        }
    }
    return result;
}


template<size_t rows, size_t cols>
template<size_t rows_other, size_t cols_other>
Matrix<rows, cols> Matrix<rows, cols>::mul_elem(const Matrix<rows_other, cols_other> &other) const {
    if ((rows != rows_other) || (cols_other != cols)) {
        throw std::runtime_error("Dimension mismatch");
    }
    Matrix<rows, cols> result;
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            result(i, j) = (*this)(i, j) * other(i, j);
        }
    }
    return result;
}


template<size_t rows, size_t cols>
template<size_t rows_rhs, size_t cols_rhs>
Matrix<rows, cols> Matrix<rows, cols>::operator-(const Matrix<rows_rhs, cols_rhs> &rhs) const {
    if ((rows_rhs != rows) || (cols_rhs != cols)) {
        throw std::runtime_error("Dimension mismatch");
    }
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
template<size_t rows_rhs, size_t cols_rhs>
Matrix<rows, cols_rhs> Matrix<rows, cols>::operator*(const Matrix<rows_rhs, cols_rhs> &rhs) const {
    if (cols != rows_rhs) {
        throw std::runtime_error("Dimension mismatch");
    }
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
template<size_t rows_rhs, size_t cols_rhs>
Matrix<rows, cols>& Matrix<rows, cols>::operator+=(const Matrix<rows_rhs, cols_rhs> &rhs) {
    if ((rows_rhs != rows) || (cols_rhs != cols)) {
        throw std::runtime_error("Dimension mismatch");
    }
    return *this = *this + rhs;
}


template<size_t rows, size_t cols>
template<size_t rows_rhs, size_t cols_rhs>
Matrix<rows, cols>& Matrix<rows, cols>::operator-=(const Matrix<rows_rhs, cols_rhs> &rhs) {
    if ((rows_rhs != rows) || (cols_rhs != cols)) {
        throw std::runtime_error("Dimension mismatch");
    }

    return *this = *this - rhs;
}


template<size_t rows, size_t cols>
template<size_t rows_rhs, size_t cols_rhs>
Matrix<rows, cols_rhs>& Matrix<rows, cols>::operator*=(const Matrix<rows_rhs, cols_rhs> &rhs) {
    if ((rows_rhs != rows) || (cols_rhs != cols)) {
        throw std::runtime_error("Dimension mismatch");
    }
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
double*  Matrix<rows, cols>::get_matrix_winthout_row_and_col(const double* buf, size_t rows_size,
    size_t cols_size, size_t row, size_t col) const {
    double* result = new double[(rows_size - 1) * (cols_size - 1)];
    size_t offset_y = 0;
    for (size_t i = 0; i < rows_size - 1; i++) {
        if (i == row) {
            offset_y = 1;
        }

        size_t offset_x = 0;
        for (size_t j = 0; j < cols_size - 1; j++) {
            if (j == col) {
                offset_x = 1;
            }
            result[i * (cols_size - 1) + j] = buf[cols_size * (i + offset_y) + j + offset_x];
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
double Matrix<rows, cols>::get_minor(const double *buf,  size_t rows_size,
    size_t cols_size, size_t row, size_t col) const {
    double* tmp = get_matrix_winthout_row_and_col(buf, rows_size, cols_size, row, col);
    double res  = 0;
    switch (rows_size - 1) {
        case 1:
            res = tmp[0];
            break;
        case 2:
            res = tmp[0] * tmp[3] - tmp[1] * tmp[2];
            break;
        default:
            double det = 0;
            double deg = 1;
            for (size_t i = 0; i < cols_size - 1; i++) {
                det += deg * tmp[i] * get_minor(tmp, rows_size - 1, cols_size - 1, 0, i);
                deg *= -1;
            }
            res = det;
    }
    delete[] tmp;
    return res;
}


template<size_t rows, size_t cols>
double Matrix<rows, cols>::det() const {
    if (rows != cols) {
        throw std::runtime_error("Invalid matrix");
    }
    if (rows == 1) {
        return (*this)(0, 0);
    }
    double det = 0;
    double deg = 1;
    double* tmp = new double[rows * cols];
    std::copy(buffer.begin(), buffer.end(), tmp);
    for (size_t i = 0; i < cols; i++) {
        det += deg * (*this)(0, i) * get_minor(tmp, rows, cols, 0, i);
        deg *= -1;
    }
    delete[] tmp;
    return det;
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
    double* tmp = new double[rows * cols];
    std::copy(buffer.begin(), buffer.end(), tmp);
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            result(i, j) = deg * get_minor(tmp, rows, cols, j, i);
            deg *= -1;
        }
        deg *= -1;
    }
    delete[] tmp;
    return result;
}
