/*!
\file face.h "model/modification/rotation.h"
\brief  Rotation classes
\author Dmitry Zaitsev
\copyright © BMSTU All rights violated.
\version 1.0
\date 22 October 2016

OX OY and OZ rotation classes
*/

#pragma once
#include "modification.h"

/*!
\class Rotation rotation.h "model/modification/rotation.h"
\brief Base rotation class

Define rotation methods
*/
class Rotation : public Modification
{
public:
	/*!
	Emty constructor. No action.
	*/
	Rotation();

	/*!
	Destructor. No action.
	*/
	~Rotation();

	/*!
	Provide rotation in OX surface
	\param[in] vertex Object to transform
	*/
	void rotateX(Vertex* vertex);

	/*!
	Provide rotation in OY surface
	\param[in] vertex Object to transform
	*/
	void rotateY(Vertex* vertex);

	/*!
	Provide rotation in OZ surface
	\param[in] vertex Object to transform
	*/
	void rotateZ(Vertex* vertex);

	/*!
	Set center around which occur modificaion
	\param[in] center Point of modification center
	*/
	virtual void setCenter(Vertex* center) override;

	/*!
	Launches modification
	\param[in] vertex Object to modificate
	*/
	virtual void run(Vertex* vertex) = 0;

protected:
	Vertex* center;	/*!< Rotation center */
	double angle;	/*!< Rotation angle in degrees */
};

/*!
\class RotationX rotation.h "model/modification/rotation.h"
\brief Rotation in OX surface

Provide rotation in OX surface
*/
class RotationX : public Rotation
{
public:
	/*!
	Emty constructor. No action.
	*/
	RotationX();

	/*!
	Constructor. Set rotation angle.
	\param[in] angle Rotation angle
	*/
	RotationX(double angle);

	/*!
	Destructor. No action.
	*/
	~RotationX();

	/*!
	Launches modification
	\param[in] vertex Object to modificate
	*/
	virtual void run(Vertex* vertex) override;
};

/*!
\class RotationY rotation.h "model/modification/rotation.h"
\brief Rotation in OY surface

Provide rotation in OY surface
*/
class RotationY : public Rotation
{
public:
	/*!
	Emty constructor. No action.
	*/
	RotationY();

	/*!
	Constructor. Set rotation angle.
	\param[in] angle Rotation angle
	*/
	RotationY(double angle);

	/*!
	Destructor. No action.
	*/
	~RotationY();

	/*!
	Launches modification
	\param[in] vertex Object to modificate
	*/
	virtual void run(Vertex* vertex) override;
};

/*!
\class RotationZ rotation.h "model/modification/rotation.h"
\brief Rotation in OZ surface

Provide rotation in OZ surface
*/
class RotationZ : public Rotation
{
public:
	/*!
	Emty constructor. No action.
	*/
	RotationZ();

	/*!
	Constructor. Set rotation angle.
	\param[in] angle Rotation angle
	*/
	RotationZ(double angle);

	/*!
	Destructor. No action.
	*/
	~RotationZ();

	/*!
	Launches modification
	\param[in] vertex Object to modificate
	*/
	virtual void run(Vertex* vertex) override;
};
