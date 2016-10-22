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
		(vertex->getX() - this->center->getX()) * cos(this->angle) -
		(vertex->getZ() - this->center->getZ()) * sin(this->angle);

	double tmpZ =
		(vertex->getX() - this->center->getX()) * sin(this->angle) +
		(vertex->getZ() - this->center->getZ()) * cos(this->angle);

	vertex->setX(tmpX);
	vertex->setZ(tmpZ);
}

void Rotation::rotateY(Vertex* vertex)
{
	double tmpY =
		(vertex->getY() - this->center->getY()) * cos(this->angle) -
		(vertex->getZ() - this->center->getZ()) * sin(this->angle);

	double tmpZ =
		(vertex->getY() - this->center->getY()) * sin(this->angle) +
		(vertex->getZ() - this->center->getZ()) * cos(this->angle);

	vertex->setY(tmpY);
	vertex->setZ(tmpZ);
}

void Rotation::rotateZ(Vertex* vertex)
{
	double tmpX =
		(vertex->getX() - this->center->getX()) * cos(this->angle) -
		(vertex->getY() - this->center->getY()) * sin(this->angle);

	double tmpY =
		(vertex->getX() - this->center->getX()) * sin(this->angle) +
		(vertex->getY() - this->center->getY()) * cos(this->angle);

	vertex->setX(tmpX);
	vertex->setY(tmpY);
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
