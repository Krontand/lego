#include "stdafx.h"
#include "../stdafx.h"
#include "gmatrix.h"

GMatrix::GMatrix() : GMatrix(1, 1)
{
}

GMatrix::GMatrix(unsigned long rows, unsigned long cols)
{
	this->rcount = rows;
	this->ccount = cols;

	for (unsigned long i = 0; i < rows; i++)
	{
		GVector tmp(cols);
		this->matrix.push_back(tmp);
	}

}

GMatrix::GMatrix(const GMatrix& other)
{
	this->rcount = other.rowcount();
	this->ccount = other.columncount();

	for (unsigned long i = 0; i < this->rcount; i++)
	{
		this->matrix.push_back(other[i]);
	}

}

GMatrix::GMatrix(GMatrix&& other)
{
	this->rcount = other.rowcount();
	this->ccount = other.columncount();

	for (unsigned long i = 0; i < this->rcount; i++)
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
	this->rcount = other.rowcount();
	this->ccount = other.columncount();

	for (unsigned long i = 0; i < this->rcount; i++)
	{
		this->matrix.push_back(other[i]);
	}

	return (*this);
}

GMatrix& GMatrix::operator=(GMatrix&& other)
{
	this->rcount = other.rowcount();
	this->ccount = other.columncount();

	for (unsigned long i = 0; i < this->rcount; i++)
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
	for (unsigned long i = 0; i < this->rcount; i++)
	{
		for (unsigned long j = 0; j < ccount; j++)
		{
			result[i][j] = result[i][j] * value;
		}
	}
	return (*this);
}

unsigned long GMatrix::columncount()
{
	return this->ccount;
}

unsigned long GMatrix::columncount() const
{
	return this->ccount;
}

unsigned long GMatrix::rowcount()
{
	return this->rcount;
}

unsigned long GMatrix::rowcount() const
{
	return this->rcount;
}