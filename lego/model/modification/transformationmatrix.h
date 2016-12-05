/*!
\file transformationmatrix.h "model/modification/transformationmatrix.h"
\brief  Matrix to modificate object in 3D surface
\author Dmitry Zaitsev
\copyright © BMSTU All rights violated.
\version 2.0
\date 20 November 2016

Contains modification matrix for object modification
*/

#pragma once
#include "../../geometry/gmatrix.h"

class GMatrix;

/*!
Rotate object around OX
\param[in] angle Rotation angle
*/
GMatrix matrixrotationX(double angle);

/*!
Rotate object around OY
\param[in] angle Rotation angle
*/
GMatrix matrixrotationY(double angle);

/*!
Rotate object around OZ
\param[in] angle Rotation angle
*/
GMatrix matrixrotationZ(double angle);

/*!
Move object
\param[in] x Move on X coordinate
\param[in] y Move on Y coordinate
\param[in] z Move on Z coordinate
*/
GMatrix matrixMove(double X, double Y, double Z);

/*!
Move object
\param[in] d Length of camera direction vector
*/
GMatrix matrixProjection(double d);
