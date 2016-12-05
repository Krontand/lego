#include "stdafx.h"
#include "../stdafx.h"
#include "../geometry\gmatrix.h"
#include "camera.h"
#include "cameramodification.h"

Camera::Camera()
{
}

Camera::Camera(GVector position, GVector target)
{
	this->position = position;
	this->target = target;

	this->right[0] = 1;
	this->right[1] = 0;
	this->right[2] = 0;
	this->right[3] = 0;

	this->up[0] = 0;
	this->up[1] = 1;
	this->up[2] = 0;
	this->up[3] = 0;

	this->direction = this->position - this->target;
}

void Camera::rotateHorizontalSphere(double angle)
{
	GMatrix rotation = matrixrotation(this->right[0], this->right[1], this->right[2], angle);
	this->up = this->up * rotation;
	this->direction = this->direction * rotation;
	GMatrix movementtoorigin = matrixmovement(this->target[0], this->target[1], this->target[2]);
	GMatrix movementback = matrixmovement(-this->target[0], -this->target[1], -this->target[2]);
	this->position = this->position * movementback * rotation * movementtoorigin;
}

void Camera::rotateVerticalSphere(double angle)
{
	GMatrix rotation = matrixrotation(this->up[0], this->up[1], this->up[2], angle);
	this->right = this->right * rotation;
	this->direction = this->direction * rotation;
	GMatrix movementtoorigin = matrixmovement(this->target[0], this->target[1], this->target[2]);
	GMatrix movementback = matrixmovement(-this->target[0], -this->target[1], -this->target[2]);
	this->position = this->position * movementback * rotation * movementtoorigin;
}

GMatrix Camera::cameraview()
{
	this->direction.normalize();
	if (this->direction == this->right || this->direction == this->right * (-1))
	{
		this->right = GVector::cross(this->up, this->direction).normalize();
		this->up = GVector::cross(this->direction, this->right).normalize();
	}
	else
	{
		this->up = GVector::cross(this->direction, this->right).normalize();
		this->right = GVector::cross(this->up, this->direction).normalize();
	}
	double X = -GVector::scalar(this->right, this->position);
	double Y = -GVector::scalar(this->up, this->position);
	double Z = -GVector::scalar(this->direction, this->position);

	GVector t(X, Y, Z, 1);

	GMatrix view;
	for (int i = 0; i < 4; i++)
	{
		view[i][0] = this->right[i];
		view[i][1] = this->up[i];
		view[i][2] = this->direction[i];
		view[i][3] = t[i];
	}

	view.transposition();
	this->cposition = this->position * view;
	return view;
}
