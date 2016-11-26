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

GMatrix::GMatrix(GMatrix& other)
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
	this->matrix.clear();
	for (size_t i = 0; i <= 3; i++)
	{
		this->matrix.push_back(other[i]);
	}

	return (*this);
}

GMatrix& GMatrix::operator=(GMatrix&& other)
{
	this->matrix.clear();
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

GMatrix GMatrix::operator*(const double value)
{
	GMatrix result(*this);
	for (size_t i = 0; i <= 3; i++)
	{
		for (size_t j = 0; j <= 3; j++)
		{
			result[i][j] = result[i][j] * value;
		}
	}
	return result;
}

GMatrix GMatrix::operator*(const GMatrix& other)
{
	GMatrix result(*this);
	for (size_t i = 0; i <= 3; i++)
	{
		GVector row((*this)[i]);
		for (size_t j = 0; j <= 3; j++)
		{
			GVector column(other[0][j], other[1][j], other[2][j], other[3][j]);
			double sum = 0;
			for (size_t k = 0; k <= 3; k++)
				sum += row[k] * column[k];
			result[i][j] = sum;
		}
	}
	return result;
}

bool GMatrix::inverse()
{
	GMatrix result;

	for (int i = 0; i <= 3; ++i)
	{
		for (int j = 0; j <= 3; ++j)
			result[i][j] = 0.0;

		result[i][i] = 1.0;
	}


	GMatrix tmp(*this);

	for (int k = 0; k <= 3; ++k)
	{
		if (fabs(tmp[k][k]) < 1e-8)
		{
			bool changed = false;
			for (int i = k + 1; i <= 3; ++i)
			{
				if (fabs(tmp[i][k]) > 1e-8)
				{
					std::swap(tmp[k], tmp[i]);
					std::swap(result[k], result[i]);

					changed = true;
					break;
				}
			}

			if (!changed)
			{
				return false;
			}
		}


		double div = tmp[k][k];
		for (int j = 0; j <= 3; ++j)
		{
			tmp[k][j] /= div;
			result[k][j] /= div;
		}

		for (int i = k + 1; i <= 3; ++i)
		{
			double multi = tmp[i][k];
			for (int j = 0; j <= 3; ++j)
			{
				tmp[i][j] -= multi * tmp[k][j];
				result[i][j] -= multi * result[k][j];
			}
		}
	}

	for (int k = 3; k > 0; --k)
	{
		for (int i = k - 1; i + 1 > 0; --i)
		{
			double multi = tmp[i][k];
			for (int j = 0; j <= 3; ++j)
			{
				tmp[i][j] -= multi * tmp[k][j];
				result[i][j] -= multi * result[k][j];
			}
		}
	}

	*this = result;

	return true;
}

GMatrix GMatrix::transposition()
{
	GMatrix result;
	for (int i = 0; i <= 3; i++)
	{
		for (int j = 0; j <= 3; j++)
		{
			result[i][j] = this->matrix[j][i];
		}
	}
	*this = result;
	return *this;
}
