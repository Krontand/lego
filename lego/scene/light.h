/*!
\file light.h "scene/light.h"
\brief  Light object
\author Dmitry Zaitsev
\copyright © BMSTU All rights violated.
\version 2.0
\date 02 November 2016

Provide lighting -> brightness of object
*/

#pragma once
#include "cameramodification.h"

class GVector;
class GMatrix;

class Light
{
public:
	/*!
	Emty constructor. No action.
	*/
	Light();

	/*!
	Constructor. Settin light with it's position and target look
	\param[in] position Light position point
	\param[in] target Light target point
	*/
	Light(GVector position, GVector direction);

	/*!
	Rotate light around target point in horizontal surface
	\param[in] angle Rotation angle
	*/
	void rotateHorizontalSphere(double angle);

	/*!
	Rotate light around target point in vertical surface
	\param[in] angle Rotation angle
	*/
	void rotateVerticalSphere(double angle);

	GVector position;	/*!< Light position */
	GVector target;		/*! Point on which looks camera */

	GVector direction;	/*! "Z" axis of light coordinate system */
	GVector sdirection;	/*! "Z" axis of light coordinate system in camera CO */
private:
	GVector right;		/*! "X" axis of light coordinate system */
	GVector up;			/*! "Y" axis of light coordinate system */

};
