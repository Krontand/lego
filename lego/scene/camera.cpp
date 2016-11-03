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
	
	this->right.addItem(1);
	this->right.addItem(0);
	this->right.addItem(0);
	this->right.addItem(1);
	this->up.addItem(0);
	this->up.addItem(1);
	this->up.addItem(0);
	this->up.addItem(1);
	this->direction.addItem(0);
	this->direction.addItem(0);
	this->direction.addItem(1);
	this->direction.addItem(1);
}

void Camera::rotateHorizontalSphere(double angle)
{
	GMatrix rotation = matrixrotation(this->right[0], this->right[1], this->right[2], angle);
	this->up = this->up * rotation;
	this->direction = this->direction * rotation;
	GMatrix movement = matrixmovement(this->target[0], this->target[1], this->target[2]);
	this->position = this->position * (-movement) * rotation * movement;
}

void Camera::rotateVerticalSphere(double angle)
{
	GMatrix rotation = matrixrotation(this->up[0], this->up[1], this->up[2], angle);
	this->right = this->right * rotation;
	this->direction = this->direction * rotation;
	GMatrix movement = matrixmovement(this->target[0], this->target[1], this->target[2]);
	this->position = this->position * (-movement) * rotation * movement;
}

GMatrix Camera::cameraview()
{
	this->right = GVector::cross(this->up, this->direction).normalize();
	this->up = GVector::cross(this->direction, this->right).normalize();
	this->direction.normalize();

	double X = -GVector::scalar(this->right, this->position);
	double Y = -GVector::scalar(this->up, this->position);
	double Z = -GVector::scalar(this->direction, this->position);

	GMatrix view(4, 4);
	
	for (int i = 0; i < 3; i++)
	{
		view[i][0] = this->right[i];
		view[i][1] = this->up[i];
		view[i][2] = this->direction[i];
		view[i][3] = 1;
	}
	view[3][0] = X;
	view[3][1] = Y;
	view[3][2] = Z;
	view[3][3] = 1;

	return view;
}
