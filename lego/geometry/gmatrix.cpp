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

	this->iterator = this->matrix.begin();
}

GMatrix::GMatrix(const GMatrix& other)
{
	this->rcount = other.rowcount();
	this->ccount = other.columncount();

	for (unsigned long i = 0; i < this->rcount; i++)
	{
		this->matrix.push_back(other[i]);
	}

	this->iterator = this->matrix.begin();
}

GMatrix::GMatrix(GMatrix&& other)
{
	this->rcount = other.rowcount();
	this->ccount = other.columncount();

	for (unsigned long i = 0; i < this->rcount; i++)
	{
		this->matrix.push_back(other[i]);
	}

	this->iterator = this->matrix.begin();
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

	this->iterator = this->matrix.begin();
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

	this->iterator = this->matrix.begin();
	return (*this);
}

GVector& GMatrix::operator[](const unsigned long index)
{
	this->iterator[index];
	return *(this->iterator);
}

GVector& GMatrix::operator[](const unsigned long index) const
{
	this->iterator[index];
	return *(this->iterator);
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