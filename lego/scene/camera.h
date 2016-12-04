/*!
\file camera.h "scene/camera.h"
\brief  Camera object
\author Dmitry Zaitsev
\copyright © BMSTU All rights violated.
\version 2.0
\date 02 November 2016

Set viewer matrix.
*/

#pragma once

class GVector;
class GMatrix;

/*!
\class Camera camera.h "scene/camera.h"
\brief Camera object

Set viewer matrix.
*/
class Camera
{
public:
	/*!
	Emty constructor. No action.
	*/
	Camera();

	/*!
	Constructor. Settin samera with it's position and target look
	\param[in] position Camera position point
	\param[in] target Camera target point
	*/
	Camera(GVector position, GVector direction);
	
	/*!
	Rotate camera around target point in horizontal surface
	\param[in] angle Rotation angle
	*/
	void rotateHorizontalSphere(double angle);

	/*!
	Rotate camera around target point in vertical surface
	\param[in] angle Rotation angle
	*/
	void rotateVerticalSphere(double angle);

	/*!
	Returns View matrix which displays object depends ot camera position
	Change global coordinate system to camera CS
	\param[in] view matrix
	*/
	GMatrix cameraview();

	GVector position;	/*!< Camera position */
	GVector ñposition;	/*!< Camera position in camera system*/
	GVector target;		/*! Point on which looks camera */

private:
	GVector right;		/*! "X" axis of camera coordinate system */
	GVector up;			/*! "Y" axis of camera coordinate system */
	GVector direction;	/*! "Z" axis of camera coordinate system */

};
