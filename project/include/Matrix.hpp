#pragma once
#include <array>
#include <cmath>
#include <cstddef>
#include <istream>
#include <stdexcept>



template<size_t rows, size_t cols>
class Matrix {
	private:
		double* buffer;
		double* get_matrix_winthout_row_and_col(size_t row, size_t col) const;
		double get_minor(size_t row, size_t col) const;
		Matrix(double* buf);
	public:
		static constexpr double Epsilon = 1e-7;
		

		//Constructors
		Matrix(): buffer(new double[rows* cols]) {}

		Matrix(const Matrix<rows, cols> &other);
  		explicit Matrix(std::istream &is);
		

		template<size_t rows_other, size_t cols_other, size_t count>
		Matrix(const std::array<Matrix<rows_other, cols_other>, count> &arr);

		template<size_t count>
		Matrix(const std::array<double, count> &arr);


		//Operators

		Matrix<rows, cols>& operator=(const Matrix<rows, cols> &rhs);

		double operator()(size_t i, size_t j) const;
  		double &operator()(size_t i, size_t j);

		template<size_t rows_other, size_t cols_other>
		bool operator==(const Matrix<rows_other, cols_other> &other);

			template<size_t rows_rhs, size_t cols_rhs>
		Matrix<rows, cols> operator+(const Matrix<rows_rhs, cols_rhs> &rhs) const;

		template<size_t rows_rhs, size_t cols_rhs>
		Matrix<rows, cols> operator-(const Matrix<rows_rhs, cols_rhs> &rhs);
		
		template<size_t rows_rhs, size_t cols_rhs>
		Matrix<rows, cols_rhs> operator*(const Matrix<rows_rhs, cols_rhs> &rhs);

		template<size_t rows_rhs, size_t cols_rhs>
		Matrix<rows, cols>& operator+=(const Matrix<rows_rhs, cols_rhs> &rhs);

		template<size_t rows_rhs, size_t cols_rhs>
		Matrix<rows, cols>& operator-=(const Matrix<rows_rhs, cols_rhs> &rhs);

		template<size_t rows_rhs, size_t cols_rhs>
		Matrix<rows, cols_rhs>& operator*=(const Matrix<rows_rhs, cols_rhs> &rhs);
		
		// Getters
		size_t get_rows_count() const;
		size_t get_cols_count() const;
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


template<size_t rows, size_t cols>
Matrix<rows, cols>::Matrix(double* buffer) {
	this->buffer = new double[rows * cols];
	std::copy(buffer, buffer + rows * cols, buffer);
}

template<size_t rows, size_t cols>
Matrix<rows, cols>::Matrix(std::istream& is) {
    bool flag = !is.bad();
    buffer = flag ? new double[rows * cols] : nullptr;
	for (size_t i = 0; (i < rows * cols) && flag; i++) {
		if (!(is >> buffer[i])) {
			flag = false;
        }
	}
	if (!flag) {
		delete[] buffer;
        throw std::runtime_error("Failde to create matrix from input stream");
	}

}
template<size_t rows, size_t cols>
Matrix<rows, cols>::Matrix(const Matrix<rows, cols> &other) : buffer(new double[rows * cols]) {
	std::copy(other.buffer, other.buffer + cols * rows, buffer);
}


template<size_t rows, size_t cols>
Matrix<rows, cols>& Matrix<rows, cols>::operator=(const Matrix<rows, cols> &rhs) {
	if (this != &rhs) {
		std::copy(rhs.buffer, rhs.buffer + rows * cols, buffer);
	}
	return *this;
}


template<size_t rows, size_t cols>
template<size_t count>
Matrix<rows, cols>::Matrix(const std::array<double, count> &arr) {
	if (count != rows * cols) {
		throw "Failed to create matrix from numbers";
	}
	buffer = new double[rows * cols];
	std::copy(arr.begin(), arr.end(), buffer);
}


template<size_t rows, size_t cols>
template<size_t rows_other, size_t cols_other>
bool Matrix<rows, cols>::operator==(const Matrix<rows_other, cols_other> &other) {
	bool flag = ((rows == rows_other) == (cols == cols_other));
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
template<size_t rows_other, size_t cols_other, size_t count>
Matrix<rows, cols>::Matrix(const std::array<Matrix<rows_other, cols_other>, count> &arr) {
	if ((rows_other == 1) && (cols_other == cols) && (count == rows)) {
		buffer = new double[rows * cols];
		for (size_t i = 0; i < rows; i++) {
			for (size_t j = 0; j < cols; j++) {
				buffer[i * cols + j] = arr[i](0, j);
			}
		}	
	} else if ((rows_other == rows) && (cols_other == 1) && (count == cols)) {
		buffer = new double[rows * cols];
		for (size_t i = 0; i < rows; i++) {
			for (size_t j = 0; j < cols; j++) {
				buffer[i * cols + j] = arr[j](i, 0);
			}
		}
	} else {
		throw std::runtime_error("Failed to create matrix from vectors");
	}
}


template<size_t rows, size_t cols>
double& Matrix<rows, cols>::operator()(size_t i, size_t j) {
	if ((i > rows) || (j > cols)) {
		throw std::out_of_range("Indexes out of range");
	}
	return buffer[i * cols + j];
}


template <size_t rows, size_t cols>
double Matrix<rows, cols>::operator()(size_t i, size_t j) const{
	return buffer[i * cols + j];
}


template<size_t rows, size_t cols>
size_t Matrix<rows, cols>::get_rows_count() const {
	return rows;
}


template<size_t rows, size_t cols>
size_t Matrix<rows, cols>::get_cols_count() const {
	return cols;
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
Matrix<rows, cols> Matrix<rows, cols>::mul_elem(const Matrix<rows_other, cols_other> &other) {
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
Matrix<rows, cols> Matrix<rows, cols>::operator-(const Matrix<rows_rhs, cols_rhs> &rhs) {
	if ((rows_rhs != rows) || (cols_rhs != cols)) {
		throw std::runtime_error("Dimension mismatch");
	}
	return rhs + (-1) * rhs; 
}


template<size_t rows, size_t cols>
Matrix<1, cols> Matrix<rows, cols>::get_row(size_t n) const {
	Matrix<1, cols>	result;
	for (size_t i = 0; i < cols; i++) {
		result(0, i) = buffer[n * cols + i];	
	}
	return result;
}


template<size_t rows, size_t cols>
Matrix<rows, 1> Matrix<rows, cols>::get_col(size_t n) const {
	Matrix<rows, 1>	result;
	for (size_t i = 0; i < rows; i++) {
		result(i, 0) = buffer[i * cols + n];	
	}
	return result;
}


template<size_t rows, size_t cols>
Matrix<rows, cols> Matrix<rows, cols>::get_diag() const {
	if (rows != cols) {
		throw std::runtime_error("Invalid matrix");
	}
	Matrix<rows, cols>result;
	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < cols; j++) {
			result(i, j) = (i == j) ? (*this)(i, j) : 0;
		}
	}
	return result;
}



template<size_t rows, size_t cols>
template<size_t rows_rhs, size_t cols_rhs>
Matrix<rows, cols_rhs> Matrix<rows, cols>::operator*(const Matrix<rows_rhs, cols_rhs> &rhs) {
	if (cols != rows_rhs) {
		throw std::runtime_error("Dimension mismatch");
	}
	Matrix<rows, cols_rhs> result;
	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < cols_rhs; j++) {
			result(i, j) = 0;
			for(size_t k = 0; k < cols; k++) {
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
	*this = *this + rhs;
	return *this;
}


template<size_t rows, size_t cols>
template<size_t rows_rhs, size_t cols_rhs>
Matrix<rows, cols>& Matrix<rows, cols>::operator-=(const Matrix<rows_rhs, cols_rhs> &rhs) {
	if ((rows_rhs != rows) || (cols_rhs != cols)) {
		throw std::runtime_error("Dimension mismatch");
	}
	*this = *this - rhs;
	return *this;
}


template<size_t rows, size_t cols>
template<size_t rows_rhs, size_t cols_rhs>
Matrix<rows, cols_rhs>& Matrix<rows, cols>::operator*=(const Matrix<rows_rhs, cols_rhs> &rhs) {
	if ((rows_rhs != rows) || (cols_rhs != cols)) {
		throw std::runtime_error("Dimension mismatch");
	}		
	*this = *this * rhs;
	return *this;
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
double*  Matrix<rows, cols>::get_matrix_winthout_row_and_col(size_t row, size_t col) const {
	size_t offsetX = 0;
	size_t offsetY = 0;
	double* result = new double[(rows - 1) * (cols - 1)];
	for (size_t i = 0; i < rows - 1; i++) {
		if (i == row) {
			offsetY = 1;
		}
		offsetX = 0;
		for (size_t j = 0; j < cols - 1; j++) {
			if (j == col) {
				offsetX = 1;
			}
			result[i * (cols - 1) + j] = (*this)(i + offsetY, j + offsetX);
		}
	} 
	return result;
}


template<size_t rows, size_t cols>
double Matrix<rows, cols>::get_minor(size_t row, size_t col) const {
	double* tmp = get_matrix_winthout_row_and_col(row, col);
	switch (rows - 1) {
		case 1:
			return tmp[0];
		case 2:
			return tmp[0] * tmp[3] - tmp[1] * tmp[2];
		default:
			double det = 0;
			double deg = 1;
			for (size_t i = 0; i < cols - 1; i++) {
				det += deg * tmp[i] * get_minor(0, i);
				deg *= -1;
			}
			return det;	
	}
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
	for (size_t i = 0; i < cols; i++) {
		det += deg * (*this)(0, i) * get_minor(0, i);
		deg *= -1;
	}
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
	Matrix<rows, cols>	result;
	double deg = 1;
	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < cols; j++) {
			result(i, j) = deg * get_minor(j, i);
			deg *= -1;
		}
	}
	return result;
}
