#include "stdafx.h"
#include "../stdafx.h"
#include "gmatrix.h"

GMatrix::GMatrix()
{
	for (size_t i = 0; i <= 3; i++)
	{
		GVector tmp;
		this->matrix.push_back(tmp);
	}
}

GMatrix::GMatrix(const GMatrix& other)
{
	for (size_t i = 0; i <= 3; i++)
	{
		this->matrix.push_back(other[i]);
	}
}

GMatrix::GMatrix(GMatrix&& other)
{
	for (size_t i = 0; i <= 3; i++)
	{
		this->matrix.push_back(other[i]);
	}
}

GMatrix::~GMatrix()
{
	this->matrix.clear();
}

GMatrix& GMatrix::operator=(GMatrix& other)
{
	for (size_t i = 0; i <= 3; i++)
	{
		this->matrix.push_back(other[i]);
	}

	return (*this);
}

GMatrix& GMatrix::operator=(GMatrix&& other)
{
	for (size_t i = 0; i <= 3; i++)
	{
		this->matrix.push_back(other[i]);
	}

	return (*this);
}

GVector& GMatrix::operator[](const unsigned long index)
{
	return this->matrix[index];
}

const GVector& GMatrix::operator[](const unsigned long index) const
{
	return this->matrix[index];
}

GMatrix& GMatrix::operator-()
{
	return *this * (-1);
}

GMatrix& GMatrix::operator*(const double value)
{
	GMatrix result(*this);
	for (size_t i = 0; i <= 3; i++)
	{
		for (size_t j = 0; j <= 3; j++)
		{
			result[i][j] = result[i][j] * value;
		}
	}
	return (*this);
}

GMatrix& GMatrix::operator*(const GMatrix& other)
{
	GMatrix result(*this);
	for (size_t i = 0; i < 3; ++i)
		for (size_t j = 0; j < 3; ++j)
		{
			GVector row((*this)[i]);
			GVector column(other[0][j],other[1][j],other[2][j],other[3][j]);
			int sum = 0;
			for (size_t k = 0; k < 3; ++k)
				sum += row[k] * column[k];
			result[i][j] = sum;
		}
	return result;
}
