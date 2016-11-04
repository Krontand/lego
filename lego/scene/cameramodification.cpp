#include "stdafx.h"
#include "../stdafx.h"

#include "cameramodification.h"

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