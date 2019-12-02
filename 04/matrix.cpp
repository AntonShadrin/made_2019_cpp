#include <vector>
#include "matrix.h"


size_t Matrix::getRows() const
{
	return matrix.size();
}

size_t Matrix::getColumns() const
{
	if (matrix.empty())
		return 0;
	return matrix[0].size();
}

Matrix::Matrix(size_t n_rows, size_t n_col)
{
	matrix.resize(n_rows);
	for (size_t i = 0; i < n_rows; ++i)
	{
		matrix[i].resize(n_col);
	}
}

Matrix* Matrix::operator *= (const int vol)
{
	for (size_t i = 0; i < matrix.size(); ++i)
	{
		for (size_t j = 0; j < matrix[i].size(); ++j)
		{
			matrix[i][j] *= vol;
		}
	}
	return this;
}

bool Matrix::operator == (const Matrix& other) const
{
	if (this == &other)
		return true;
	for (size_t i = 0; i < matrix.size(); ++i)
		if (matrix[i] != other.matrix[i]) return false;
	return true;
}

bool Matrix::operator != (const Matrix& other) const
{
	return !(*this == other);
}

Matrix::Proxy Matrix::operator [] (int i)
{
	if (i >= matrix.size())
		throw std::out_of_range("Matrix: axis 0 out of range!");
	return Proxy(matrix[i]);
}

const Matrix::constProxy Matrix::operator [] (int i) const
{
	if (i >= matrix.size())
		throw std::out_of_range("Matrix: axis 0 out of range!");
	return constProxy(matrix[i]);
}

int& Matrix::Proxy::operator [] (int j)
{
	if (j >= rowPtr.size())
		throw std::out_of_range("Matrix: axis 1 out of range!");
	return (rowPtr[j]);
}

const int& Matrix::constProxy::operator [] (int j) const
{
	if (j >= rowPtr_const.size())
		throw std::out_of_range("Matrix: axis 1 out of range!");
	return (rowPtr_const[j]);
}
