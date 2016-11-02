#include "stdafx.h"
#include "../stdafx.h"
#include "gvector.h"
#include "gmatrix.h"

GVector::GVector()
{
}

GVector::GVector(unsigned long n)
{
	for (int i = 0; i < n; i++)
	{
		this->vec.push_back(0);
	}
}

GVector::GVector(const GVector& other)
{
	this->vec = other.getVec();
}

GVector::GVector(GVector&& other)
{
	this->vec = other.getVec();
}

GVector::~GVector()
{
	this->vec.clear();
}

GVector& GVector::operator=(GVector& other)
{
	this->vec = other.getVec();
	return *this;
}

GVector& GVector::operator=(GVector&& other)
{
	this->vec = other.getVec();
	return *this;
}

double& GVector::operator[](const unsigned long index)
{
	return this->vec[index];
}

const double& GVector::operator[](const unsigned long index) const
{
	return this->vec[index];
}

void GVector::addItem(double item)
{
	this->vec.push_back(item);
}

unsigned long GVector::size() const
{
	return this->vec.size();
}

vector<double> GVector::getVec() const
{
	return this->vec;
}

double GVector::length()
{
	if (this->size() != 4)
	{
		throw VectorSizeError();
	}

	double X = (*this)[0];
	double Y = (*this)[1];
	double Z = (*this)[2];

	return sqrt(X * X + Y * Y + Z * Z);
}

GVector GVector::normalize()
{
	if (this->size() != 4)
	{
		throw VectorSizeError();
	}

	double norm = 1 / (*this).length();
	for (int i = 0; i < 3; ++i)
	{
		(*this)[i] = (*this)[i] * norm;
	}

	return *this;
}

GVector GVector::cross(GVector first, GVector second)
{
	if (first.size() != 4 || second.size() != 4)
	{
		throw VectorSizeError();
	}

	GVector result(4);
	result[0] = first[2] * second[1] - first[1] * second[2]; // new X = Z1 * Y2 - Y1 * Z2
	result[1] = first[0] * second[2] - first[2] * second[0]; // new Y = X1 * Z2 - Z1 * X2
	result[2] = first[1] * second[0] - first[0] * second[1]; // new Z = Y1 * X2 - X1 * Y2
	result[3] = 1;

	return result;
}

double GVector::scalar(GVector first, GVector second)
{
	if (first.size() != 4 || second.size() != 4)
	{
		throw VectorSizeError();
	}

	return first[0] * second[0] + first[1] * second[1] + first[2] * second[2];
}

GVector GVector::operator*(GMatrix matrix)
{
	GVector result(0);
	for (unsigned long i = 0; i < matrix.columncount(); i++)
	{
		result.addItem(0);
		for (unsigned long j = 0; j < matrix.rowcount(); j++)
		{
			result[i] = result[i] + matrix[j][i] * vec[j];
		}
	}
	return result;
}