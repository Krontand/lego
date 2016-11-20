/*!
\file cameramodification.h "scene/cameramodification.h"
\brief  Modidy camera
\author Dmitry Zaitsev
\copyright © BMSTU All rights violated.
\version 2.0
\date 02 November 2016

Contains modification matrix for camera modification
*/

#pragma once
#include "../geometry/gmatrix.h"

class GMatrix;

/*!
Rotate camera around target point
\param[in] X X coordinate of vector around which camera rotates
\param[in] Y Y coordinate of vector around which camera rotates
\param[in] Z Z coordinate of vector around which camera rotates
\param[in] angle Rotation angle
*/
GMatrix matrixrotation(double X, double Y, double Z, double angle);

/*!
Move camera depends target point
\param[in] X X coordinate of target vector
\param[in] Y Y coordinate of target vector
\param[in] Z Z coordinate of target vector
*/
GMatrix matrixmovement(double X, double Y, double Z);

/*!
Scale camera
\param[in] k Coefficient of scale
*/
GMatrix matrixscale(double k);