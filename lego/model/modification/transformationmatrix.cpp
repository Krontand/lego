#include "stdafx.h"
#include "../../stdafx.h"

#include "transformationmatrix.h"

GMatrix matrixrotationX(double angle)
{
	double cosa = cos(angle);
	double sina = sin(angle);

	GMatrix transform;

	transform[0][0] = cosa;
	transform[0][1] = 0;
	transform[0][2] = sina;
	transform[0][3] = 0;

	transform[1][0] = 0;
	transform[1][1] = 1;
	transform[1][2] = 0;
	transform[1][3] = 0;

	transform[2][0] = -sina;
	transform[2][1] = 0;
	transform[2][2] = cosa;
	transform[2][3] = 0;

	transform[3][0] = 0;
	transform[3][1] = 0;
	transform[3][2] = 0;
	transform[3][3] = 1;

	return transform;
}

GMatrix matrixrotationY(double angle)
{
	angle *= -1;
	double cosa = cos(angle);
	double sina = sin(angle);

	GMatrix transform;

	transform[0][0] = 1;
	transform[0][1] = 0;
	transform[0][2] = 0;
	transform[0][3] = 0;

	transform[1][0] = 0;
	transform[1][1] = cosa;
	transform[1][2] = -sina;
	transform[1][3] = 0;

	transform[2][0] = 0;
	transform[2][1] = sina;
	transform[2][2] = cosa;
	transform[2][3] = 0;

	transform[3][0] = 0;
	transform[3][1] = 0;
	transform[3][2] = 0;
	transform[3][3] = 1;

	return transform;
}

GMatrix matrixrotationZ(double angle)
{
	double cosa = cos(angle);
	double sina = sin(angle);

	GMatrix transform;

	transform[0][0] = cosa;
	transform[0][1] = -sina;
	transform[0][2] = 0;
	transform[0][3] = 0;

	transform[1][0] = sina;
	transform[1][1] = cosa;
	transform[1][2] = 0;
	transform[1][3] = 0;

	transform[2][0] = 0;
	transform[2][1] = 0;
	transform[2][2] = 1;
	transform[2][3] = 0;

	transform[3][0] = 0;
	transform[3][1] = 0;
	transform[3][2] = 0;
	transform[3][3] = 1;

	return transform;
}

GMatrix matrixMove(double X, double Y, double Z)
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