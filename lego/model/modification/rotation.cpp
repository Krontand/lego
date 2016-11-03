#include "stdafx.h"
#include "../../stdafx.h"
#include "rotation.h"

Rotation::Rotation()
{
}

Rotation::~Rotation()
{
}

void Rotation::rotateX(Vertex* vertex)
{
	double tmpX =
		this->center->X + (vertex->X - this->center->X) * cos(this->angle) -
		(vertex->Z - this->center->Z) * sin(this->angle);

	double tmpZ =
		this->center->Z + (vertex->X - this->center->X) * sin(this->angle) +
		(vertex->Z - this->center->Z) * cos(this->angle);

	vertex->X = tmpX;
	vertex->Z = tmpZ;
}

void Rotation::rotateY(Vertex* vertex)
{
	double tmpY =
		this->center->Y + (vertex->Y - this->center->Y) * cos(this->angle) -
		(vertex->Z - this->center->Z) * sin(this->angle);

	double tmpZ =
		this->center->Z + (vertex->Y - this->center->Y) * sin(this->angle) +
		(vertex->Z - this->center->Z) * cos(this->angle);

	vertex->Y = tmpY;
	vertex->Z = tmpZ;
}

void Rotation::rotateZ(Vertex* vertex)
{
	double tmpX =
		this->center->X + (vertex->X - this->center->X) * cos(this->angle) -
		(vertex->Y - this->center->Y) * sin(this->angle);

	double tmpY =
		this->center->Y + (vertex->X - this->center->X) * sin(this->angle) +
		(vertex->Y - this->center->Y) * cos(this->angle);

	vertex->X = tmpX;
	vertex->Y = tmpY;
}

void Rotation::setCenter(Vertex* center)
{
	this->center = center;
}

RotationX::RotationX()
{
}

RotationX::RotationX(double angle)
{
	this->angle = angle;
}

RotationX::~RotationX()
{
}

void RotationX::run(Vertex* vertex)
{
	this->rotateX(vertex);
}

RotationY::RotationY()
{
}

RotationY::RotationY(double angle)
{
	this->angle = angle;
}

RotationY::~RotationY()
{
}

void RotationY::run(Vertex* vertex)
{
	this->rotateY(vertex);
}

RotationZ::RotationZ()
{
}

RotationZ::RotationZ(double angle)
{
	this->angle = angle;
}

RotationZ::~RotationZ()
{
}

void RotationZ::run(Vertex* vertex)
{
	this->rotateZ(vertex);
}
