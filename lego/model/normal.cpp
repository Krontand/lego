#include "stdafx.h"
#include "../stdafx.h"
#include "normal.h"

Normal::Normal() : GVector() {}
Normal::Normal(const GVector& v) : GVector(v) {}
Normal::Normal(GVector&& v) : GVector(v) {}
Normal::Normal(const Normal& other) : GVector(other) {}
Normal::Normal(Normal&& other) : GVector(other) {}
Normal::Normal(double X, double Y, double Z, double length) : GVector(X, Y, Z, length) {}
Normal::~Normal() {}

Normal& Normal::operator=(Normal other)
{
	return Normal(static_cast<GVector&>(*this) = static_cast<GVector>(other));
}

Normal Normal::operator+(const Normal& other)
{
	return Normal(static_cast<GVector>(*this) + static_cast<GVector>(other));
}

Normal Normal::operator-(const Normal& other)
{
	return Normal(static_cast<GVector>(*this) - static_cast<GVector>(other));
}

Normal Normal::operator/(const double value)
{
	return Normal(static_cast<GVector>(*this) / value);
}

Normal Normal::operator*(const double value)
{
	return Normal(static_cast<GVector>(*this) * value);
}

double& Normal::operator[](const size_t index)
{
	return static_cast<GVector>(*this)[index];
}

const double& Normal::operator[](const size_t index) const
{
	return static_cast<GVector>(*this)[index];
}

Normal Normal::operator*(GMatrix matrix)
{
	Normal result = Normal(static_cast<GVector>(*this) * matrix);
	return result;
}

void Normal::modificate(Modification* modification, Vertex* center)
{
	modification->run(this);
}