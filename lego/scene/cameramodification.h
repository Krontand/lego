/*!
\file camera.h "scene/cameramodification.h"
\brief  Modidy camera
\author Dmitry Zaitsev
\copyright © BMSTU All rights violated.
\version 2.0
\date 02 November 2016

Contains modification matrix for camera modification
*/

#pragma once
#include "../stdafx.h"

/*!
Rotate camera around target point
\param[in] X X coordinate of vector around which camera rotates
\param[in] Y Y coordinate of vector around which camera rotates
\param[in] Z Z coordinate of vector around which camera rotates
\param[in] angle Rotation angle
*/
GMatrix matrixrotation(double X, double Y, double Z, double angle)
{
	double cosa = cos(angle);
	double sina = sin(angle);

	GMatrix transform;

	transform[0][0] = cosa + (1 - cosa) * X * X;
	transform[0][1] = (1 - cosa) * X * Y + sina * Z;
	transform[0][2] = (1 - cosa) * X * Z - sina * Y;
	transform[0][3] = 0;

	transform[1][0] = (1 - cosa) * X * Y - sina * Z;
	transform[1][1] = cosa + (1 - cosa) * Y * Y;
	transform[1][2] = (1 - cosa) * Z * Y + sina * X;
	transform[1][3] = 0;

	transform[2][0] = (1 - cosa) * X * Z + sina * Y;
	transform[2][1] = (1 - cosa) * Y * Z - sina * X;
	transform[2][2] = cosa + (1 - cosa) * Z * Z;
	transform[2][3] = 0;

	transform[3][0] = 0;
	transform[3][1] = 0;
	transform[3][2] = 0;
	transform[3][3] = 1;

	return transform;
}

/*!
Move camera depends target point
\param[in] X X coordinate of target vector
\param[in] Y Y coordinate of target vector
\param[in] Z Z coordinate of target vector
*/
GMatrix matrixmovement(double X, double Y, double Z)
{
	GMatrix transform;

	transform[0][0] = 1;
	transform[0][1] = 0;
	transform[0][2] = 0;
	transform[0][3] = 0;

	transform[1][0] = 0;
	transform[1][1] = 1;
	transform[1][2] = 0;
	transform[1][3] = 0;

	transform[2][0] = 0;
	transform[2][1] = 0;
	transform[2][2] = 1;
	transform[2][3] = 0;

	transform[3][0] = X;
	transform[3][1] = Y;
	transform[3][2] = Z;
	transform[3][3] = 1;

	return transform;
}

/*!
Scale camera
\param[in] k Coefficient of scale
*/
GMatrix matrixscale(double k)
{
	GMatrix transform;

	transform[0][0] = k;
	transform[0][1] = 0;
	transform[0][2] = 0;
	transform[0][3] = 0;

	transform[1][0] = 0;
	transform[1][1] = k;
	transform[1][2] = 0;
	transform[1][3] = 0;

	transform[2][0] = 0;
	transform[2][1] = 0;
	transform[2][2] = k;
	transform[2][3] = 0;

	transform[3][0] = 0;
	transform[3][1] = 0;
	transform[3][2] = 0;
	transform[3][3] = k;

	return transform;
}