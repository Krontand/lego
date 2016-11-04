#include "stdafx.h"
#include "../stdafx.h"
#include "../geometry\gmatrix.h"
#include "light.h"

Light::Light()
{
}

Light::Light(GVector position, GVector target)
{
	this->position = position;
	this->target = target;

	this->right[0] = 1;
	this->right[1] = 0;
	this->right[2] = 0;
	this->right[3] = 1;

	this->up[0] = 0;
	this->up[1] = 1;
	this->up[2] = 0;
	this->up[3] = 1;

	this->direction[0] = 0;
	this->direction[1] = 0;
	this->direction[2] = 1;
	this->direction[3] = 1;
}

void Light::rotateHorizontalSphere(double angle)
{
	GMatrix rotation = matrixrotation(this->right[0], this->right[1], this->right[2], angle);
	this->up = this->up * rotation;
	this->direction = this->direction * rotation;
	GMatrix movement = matrixmovement(this->target[0], this->target[1], this->target[2]);
	this->position = this->position * (-movement) * rotation * movement;
}

void Light::rotateVerticalSphere(double angle)
{
	GMatrix rotation = matrixrotation(this->up[0], this->up[1], this->up[2], angle);
	this->right = this->right * rotation;
	this->direction = this->direction * rotation;
	GMatrix movement = matrixmovement(this->target[0], this->target[1], this->target[2]);
	this->position = this->position * (-movement) * rotation * movement;
}
