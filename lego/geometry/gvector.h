#pragma once

#include "exception.h"

using namespace std;

class GMatrix;

class GVector {
public:
	GVector();
	GVector(unsigned long n);
	GVector(const GVector& other);
	GVector(GVector&& other);

	~GVector();

	GVector& operator=(GVector& other);
	GVector& operator=(GVector&& other);
	double* operator[](const unsigned long index);
	const double* operator[](const unsigned long index) const;

	void addItem(double item);
	unsigned long size() const;
	vector<double> getVec() const;

	double length();

	GVector normalize();

	GVector static cross(GVector first, GVector second);
	double static scalar(GVector first, GVector second);

	GVector operator*(GMatrix matrix);

private:
	vector<double> vec;
};