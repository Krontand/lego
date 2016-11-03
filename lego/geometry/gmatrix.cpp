#include "stdafx.h"
#include "../stdafx.h"
#include "gmatrix.h"

GMatrix::GMatrix()
{
	for (unsigned long i = 0; i <= 3; i++)
	{
		GVector tmp;
		this->matrix.push_back(tmp);
	}
}

GMatrix::GMatrix(const GMatrix& other)
{
	for (unsigned long i = 0; i <= 3; i++)
	{
		this->matrix.push_back(other[i]);
	}
}

GMatrix::GMatrix(GMatrix&& other)
{
	for (unsigned long i = 0; i <= 3; i++)
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
	for (unsigned long i = 0; i <= 3; i++)
	{
		this->matrix.push_back(other[i]);
	}

	return (*this);
}

GMatrix& GMatrix::operator=(GMatrix&& other)
{
	for (unsigned long i = 0; i <= 3; i++)
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
	for (unsigned long i = 0; i <= 3; i++)
	{
		for (unsigned long j = 0; j <= 3; j++)
		{
			result[i][j] = result[i][j] * value;
		}
	}
	return (*this);
}