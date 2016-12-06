#include "stdafx.h"
#include "../stdafx.h"
#include "vertex.h"

Vertex::Vertex()
{
	this->X = 0;
	this->Y = 0;
	this->Z = 0;
}

Vertex::Vertex(double X, double Y, double Z)
{
	this->X = X;
	this->Y = Y;
	this->Z = Z;
}

Vertex::Vertex(const Vertex& other)
{
	this->X = other.X;
	this->Y = other.Y;
	this->Z = other.Z;
}

Vertex::Vertex(Vertex&& other)
{
	this->X = other.X;
	this->Y = other.Y;
	this->Z = other.Z;
}

Vertex::~Vertex()
{
	this->X = 0;
	this->Y = 0;
	this->Z = 0;
}

Vertex& Vertex::operator=(Vertex other)
{
	this->X = other.X;
	this->Y = other.Y;
	this->Z = other.Z;
	return *this;
}

GVector Vertex::vector()
{
	GVector vec(this->X, this->Y, this->Z, 0);
	return vec;
}

void Vertex::modificate(Modification* modification, Vertex* center)
{
	modification->run(this);
}

Vertex Vertex::operator*(GMatrix matrix)

{
	GVector tmp(this->X, this->Y, this->Z, 1);

	tmp = tmp * matrix;

	Vertex vresult;

	if (tmp[3] < 0.1) tmp[3] = 0.1;

	vresult.X = tmp[0] / tmp[3];
	vresult.Y = tmp[1] / tmp[3];
	vresult.Z = tmp[2] / tmp[3];

	return vresult;
}