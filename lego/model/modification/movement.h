/*!
\file movement.h "model/modification/movement.h"
\brief  Movement classes
\author Dmitry Zaitsev
\copyright © BMSTU All rights violated.
\version 1.0
\date 03 December 2016

OX OY and OZ movement classes
*/

#pragma once
#include "modification.h"

/*!
\class Movement movement.h "model/modification/movement.h"
\brief Base movement class

Define movement methods
*/
class Movement : public Modification
{
public:
	/*!
	Emty constructor. No action.
	*/
	Movement();

	/*!
	Destructor. No action.
	*/
	~Movement();

	/*!
	Provide movement in OX surface
	\param[in] o Object to transform
	*/
	void moveX(BaseObject* o);

	/*!
	Provide movement in OY surface
	\param[in] o Object to transform
	*/
	void moveY(BaseObject* o);

	/*!
	Provide movement in OZ surface
	\param[in] o Object to transform
	*/
	void moveZ(BaseObject* o);

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
	double shift;				/*!< Movement koefficient */
	GMatrix move;				/*!< Movement matrix */
	
	// The idea is that normals movement 
	// won't change normals at all. But
	// I'm gonna make this because I have
	// no idea what's wrong with cylinders lighting
	// Maybe this will help? I don't think so...
	GMatrix nmove;				/*!< Movement matrix (for normals)*/
};

/*!
\class MovementX movement.h "model/modification/movement.h"
\brief MovementX in OX surface

Provide movementX in OX surface
*/
class MovementX : public Movement
{
public:
	/*!
	Emty constructor. No action.
	*/
	MovementX();

	/*!
	Constructor. Set rotation angle.
	\param[in] angle Rotation angle
	*/
	MovementX(double angle);

	/*!
	Destructor. No action.
	*/
	~MovementX();

	/*!
	Launches modification
	\param[in] o Object to modificate
	*/
	virtual void run(BaseObject* o) override;

};

/*!
\class MovementY movement.h "model/modification/movement.h"
\brief MovementY in OY surface

Provide movementY in OY surface
*/
class MovementY : public Movement
{
public:
	/*!
	Emty constructor. No action.
	*/
	MovementY();

	/*!
	Constructor. Set rotation angle.
	\param[in] angle Rotation angle
	*/
	MovementY(double angle);

	/*!
	Destructor. No action.
	*/
	~MovementY();

	/*!
	Launches modification
	\param[in] o Object to modificate
	*/
	virtual void run(BaseObject* o) override;

};

/*!
\class MovementZ movement.h "model/modification/movement.h"
\brief MovementZ in OZ surface

Provide movementZ in OZ surface
*/
class MovementZ : public Movement
{
public:
	/*!
	Emty constructor. No action.
	*/
	MovementZ();

	/*!
	Constructor. Set rotation angle.
	\param[in] angle Rotation angle
	*/
	MovementZ(double angle);

	/*!
	Destructor. No action.
	*/
	~MovementZ();

	/*!
	Launches modification
	\param[in] o Object to modificate
	*/
	virtual void run(BaseObject* o) override;

};