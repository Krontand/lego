#include "stdafx.h"
#include "../stdafx.h"
#include "gvector.h"
#include "gmatrix.h"

GVector::GVector()
{
	for (int i = 0; i < 4; i++)
	{
		this->vec.push_back(0);
	}
}

GVector::GVector(double X, double Y, double Z, double hc)
{
	this->vec.push_back(X);
	this->vec.push_back(Y);
	this->vec.push_back(Z);
	this->vec.push_back(hc);
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

GVector& GVector::operator=(GVector other)
{
	this->vec = other.getVec();
	return *this;
}

GVector GVector::operator+(const GVector other)
{
	GVector result;
	result[0] = (*this)[0] + other[0];
	result[1] = (*this)[1] + other[1];
	result[2] = (*this)[2] + other[2];
	result[3] = (*this)[3] + other[3];
	return result;
}

GVector GVector::operator-(const GVector other)
{
	GVector result;
	result[0] = (*this)[0] - other[0];
	result[1] = (*this)[1] - other[1];
	result[2] = (*this)[2] - other[2];
	result[3] = (*this)[3] - other[3];
	return result;
}

GVector GVector::operator/(const double value)
{
	GVector result;
	result[0] = (*this)[0] / value;
	result[1] = (*this)[1] / value;
	result[2] = (*this)[2] / value;
	result[3] = (*this)[3] / value;
	return result;
}

GVector GVector::operator*(const double value)
{
	GVector result;
	result[0] = (*this)[0] * value;
	result[1] = (*this)[1] * value;
	result[2] = (*this)[2] * value;
	result[3] = (*this)[3] * value;
	return result;
}

double& GVector::operator[](const size_t index)
{
	if (index > 3 || index < 0)
	{
		throw VectorIndexError();
	}
	return this->vec[index];
}

const double& GVector::operator[](const size_t index) const
{
	if (index > 3 || index < 0)
	{
		throw VectorIndexError();
	}
	return this->vec[index];
}

vector<double> GVector::getVec() const
{
	return this->vec;
}

double GVector::length()
{
	double X = (*this)[0];
	double Y = (*this)[1];
	double Z = (*this)[2];

	return sqrt(X * X + Y * Y + Z * Z);
}

GVector GVector::normalize()
{
	double length = (*this).length();
	if (length == 0)
	{
		return *this;
	}

	double norm = 1 / length;
	for (int i = 0; i < 3; ++i)
	{
		(*this)[i] = (*this)[i] * norm;
	}

	return *this;
}

GVector GVector::cross(GVector first, GVector second)
{
	GVector result;
	result[0] = first[1] * second[2] - first[2] * second[1]; // new X = Y1 * Z2 - Z1 * Y2
	result[1] = first[2] * second[0] - first[0] * second[2]; // new Y = Z1 * X2 - X1 * Z2
	result[2] = first[0] * second[1] - first[1] * second[0]; // new Z = X1 * Y2 - Y1 * X2
	result[3] = 0;

	return result;
}

double GVector::scalar(GVector first, GVector second)
{
	return first[0] * second[0] + first[1] * second[1] + first[2] * second[2];
}

double GVector::angle(GVector first, GVector second)
{
	double angle = acos(scalar(first, second) / (first.length() * second.length()));
	angle *= 180 / M_PI;

	if (angle > 180)
	{
		angle -= 180;
	}

	return angle;
}

GVector GVector::operator*(GMatrix matrix)
{
	GVector result;
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			result[i] = result[i] + matrix[j][i] * this->vec[j];
		}
	}
	return result;
}

bool GVector::operator==(const GVector& other) const
{
	for (int i = 0; i < 4; i++)
	{
		if (round(this->vec[i] * 100) / 100. != round(other[i] * 100) / 100.)
		{
			return false;
		}
	}
	return true;
}

bool GVector::operator!=(const GVector& other) const
{
	for (int i = 0; i < 4; i++)
	{
		if (round(this->vec[i] * 100) / 100. != round(other[i] * 100) / 100.)
		{
			return true;
		}
	}
	return false;
}
