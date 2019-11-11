#include <vector>
#include <assert.h>
#include <stdexcept>
#include "matrix.h"


int Matrix::getRows() const
{
	return matrix.size();
}

int Matrix::getColumns() const
{
	assert(matrix.size() != 0);
	return matrix[0].size();
}

Matrix::Matrix(size_t n_rows, size_t n_col)
{
	matrix.resize(n_rows);
	for (int i = 0; i < n_rows; ++i)
	{
		matrix[i].resize(n_col);
	}
}

void Matrix::operator *= (const int& vol)
{
	for (int i = 0; i < matrix.size(); ++i)
	{
		for (int j = 0; j < matrix[i].size(); ++j)
		{
			matrix[i][j] *= vol;
		}
	}
}

bool Matrix::operator == (const Matrix& other) const
{
	if (this == &other)
		return true;
	for (int i = 0; i < matrix.size(); ++i)
		if (matrix[i] != other.matrix[i]) return false;
	return true;
}

bool Matrix::operator != (const Matrix& other) const
{
	return !(*this == other);
}

Matrix::Proxy Matrix::operator [] (int i)
{
	if (i > matrix.size() - 1)
		throw std::out_of_range("Matrix: axis 0 out of range!");
	return Proxy(&(matrix[i]));
}

int& Matrix::Proxy::operator [] (int j)
{
	if (j > (*rowPtr).size() - 1)
		throw std::out_of_range("Matrix: axis 1 out of range!");
	return ((*rowPtr)[j]);
}