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
	void rotateX(BaseObject* o);

	/*!
	Provide rotation in OY surface
	\param[in] vertex Object to transform
	*/
	void rotateY(BaseObject* o);

	/*!
	Provide rotation in OZ surface
	\param[in] vertex Object to transform
	*/
	void rotateZ(BaseObject* o);

	/*!
	Set center around which occur modificaion and calculate transform matrix
	\param[in] center Point of modification center
	*/
	virtual void initModification(Vertex* center) override;

	/*!
	Launches modification
	\param[in] o Object to modificate
	*/
	virtual void run(BaseObject* o) = 0;


protected:
	Vertex* center;				/*!< Rotation center */
	double angle;				/*!< Rotation angle in degrees */
	GMatrix rotate;				/*!< Rotation matrix */
	GMatrix vMatrixRotation;	/*!< Matrix to change vertex */
	GMatrix nMatrixRotation;	/*!< Matrix to change normal */
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
	\param[in] o Object to modificate
	*/
	virtual void run(BaseObject* o) override;

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
	\param[in] o Object to modificate
	*/
	virtual void run(BaseObject* o) override;
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
	\param[in] o Object to modificate
	*/
	virtual void run(BaseObject* o) override;

};
