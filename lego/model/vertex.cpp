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

Vertex& Vertex::operator=(const Vertex& other)
{
	this->X = other.X;
	this->Y = other.Y;
	this->Z = other.Z;
	return *this;
}

Vertex& Vertex::operator=(Vertex&& other)
{
	this->X = other.X;
	this->Y = other.Y;
	this->Z = other.Z;
	return *this;
}

GVector Vertex::vector()
{
	GVector vec(this->X, this->Y, this->Z, 1);
	return vec;
}

void Vertex::modificate(Modification* modification, Vertex* center)
{
	modification->setCenter(center);
	modification->run(this);
}

Vertex Vertex::operator*(GMatrix matrix)

{
	GVector tmp(this->X, this->Y, this->Z, 1);

	GVector result;
	for (size_t i = 0; i <= 3; i++)
	{
		for (size_t j = 0; j <= 3; j++)
		{
			result[i] = result[i] + matrix[j][i] * tmp[j];
		}
	}
	(*this).X = result[0];
	(*this).Y = result[1];
	(*this).Z = result[2];
	return (*this);
}