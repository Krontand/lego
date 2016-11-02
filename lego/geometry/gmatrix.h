#pragma once
 
#include "gvector.h"

using namespace std;

class GMatrix
{
public:
	GMatrix();
	GMatrix(unsigned long rows, unsigned long cols);
	GMatrix(const GMatrix& other);
	GMatrix(GMatrix&& other);

	~GMatrix();

	GMatrix& operator=(GMatrix& other);
	GMatrix& operator=(GMatrix&& other);
	GVector& operator[](const unsigned long index);
	const GVector& operator[](const unsigned long index) const;

	GMatrix& operator-();
	GMatrix& operator*(const double value);

	unsigned long columncount();
	unsigned long columncount() const;
	unsigned long rowcount();
	unsigned long rowcount() const;

private:
	vector<GVector> matrix;
	unsigned long ccount;
	unsigned long rcount;
};