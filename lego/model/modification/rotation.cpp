#include "stdafx.h"
#include "../../stdafx.h"
#include "rotation.h"

Rotation::Rotation()
{
}

Rotation::~Rotation()
{
}

void Rotation::rotateX(BaseObject* o)
{
	if (o->isVertex())
	{
		*(Vertex*)o = *(Vertex*)o * this->vMatrixRotation;
	}
	else
	{
		*(Normal*)o = *(Normal*)o * this->nMatrixRotation;
	}
}

void Rotation::rotateY(BaseObject* o)
{
	if (o->isVertex())
	{
		*(Vertex*)o = *(Vertex*)o * this->vMatrixRotation;
	}
	else
	{
		*(Normal*)o = *(Normal*)o * this->nMatrixRotation;
	}
}

void Rotation::rotateZ(BaseObject* o)
{
	if (o->isVertex())
	{
		*(Vertex*)o = *(Vertex*)o * this->vMatrixRotation;
	}
	else
	{
		*(Normal*)o = *(Normal*)o * this->nMatrixRotation;
	}
}

void Rotation::initModification(Vertex* center)
{
	this->center = center;

	GMatrix moveToOrigin = matrixMove(-this->center->X, -this->center->Y, -this->center->Z);
	GMatrix moveBack = matrixMove(this->center->X, this->center->Y, this->center->Z);
	
	this->vMatrixRotation = moveToOrigin * rotate * moveBack;

	this->nMatrixRotation = this->vMatrixRotation;
	this->nMatrixRotation.transposition();
	this->nMatrixRotation.inverse();
}

RotationX::RotationX()
{
}

RotationX::RotationX(double angle)
{
	this->angle = angle;
	this->rotate = matrixrotationX(this->angle);
}

RotationX::~RotationX()
{
}

void RotationX::run(BaseObject* o)
{
	this->rotateX(o);
}

RotationY::RotationY()
{
}

RotationY::RotationY(double angle)
{
	this->angle = angle;
	this->rotate = matrixrotationY(this->angle);
}

RotationY::~RotationY()
{
}

void RotationY::run(BaseObject* o)
{
	this->rotateY(o);
}


RotationZ::RotationZ()
{
}

RotationZ::RotationZ(double angle)
{
	this->angle = angle;
	this->rotate = matrixrotationZ(this->angle);
}

RotationZ::~RotationZ()
{
}

void RotationZ::run(BaseObject* o)
{
	this->rotateZ(o);
}

