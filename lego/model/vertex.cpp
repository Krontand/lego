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
	this->X = other.getX();
	this->Y = other.getY();
	this->Z = other.getZ();
}

Vertex::Vertex(Vertex&& other)
{
	this->X = other.getX();
	this->Y = other.getY();
	this->Z = other.getZ();
}

Vertex::~Vertex()
{
	this->X = 0;
	this->Y = 0;
	this->Z = 0;
}

Vertex& Vertex::operator=(const Vertex& other)
{
	this->X = other.getX();
	this->Y = other.getY();
	this->Z = other.getZ();
	return *this;
}

void Vertex::setX(double X)
{
	this->X = X;
}

void Vertex::setY(double Y)
{
	this->Y = Y;
}

void Vertex::setZ(double Z)
{
	this->Z = Z;
}

double Vertex::getX()
{
	return this->X;
}

double Vertex::getX() const
{
	return this->X;
}

double Vertex::getY()
{
	return this->Y;
}

double Vertex::getY() const
{
	return this->Y;
}

double Vertex::getZ()
{
	return this->Z;
}

double Vertex::getZ() const
{
	return this->Z;
}

GVector Vertex::vector()
{
	GVector vec;
	vec.addItem(this->X);
	vec.addItem(this->Y);
	vec.addItem(this->Z);
	vec.addItem(1);
	return vec;
}

void Vertex::modificate(Modification* modification, Vertex* center)
{
	modification->setCenter(center);
	modification->run(this);
}

Vertex Vertex::operator*(GMatrix matrix)

{
	GVector tmp(4);
	tmp[0] = (*this).getX();
	tmp[1] = (*this).getY();
	tmp[2] = (*this).getZ();
	tmp[3] = 1;

	GVector result(0);
	for (unsigned long i = 0; i < matrix.columncount(); i++)
	{
		result.addItem(0);
		for (unsigned long j = 0; j < matrix.rowcount(); j++)
		{
			result[i] = result[i] + matrix[j][i] * tmp[j];
		}
	}
	(*this).setX(result[0]);
	(*this).setY(result[1]);
	(*this).setZ(result[2]);
	return (*this);
}