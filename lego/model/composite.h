/*!
\file composite.h "model/composite.h"
\brief  Composite class
\author Dmitry Zaitsev
\copyright � BMSTU All rights violated.
\version 1.0
\date 16 October 2016

Contains loaded bricks
*/

#pragma once

#include "brick.h"
#include "exception.h"

/*!
\class Composite composite.h "model/composite.h"
\brief  Contains loaded bricks

Array of bricks. Interface for add/delete/modificate any of bricks.
*/
class Composite : public BaseObject
{
public:
	/*!
	Empty constructor. Initialise ID with zero.
	*/
	Composite();

	/*!
	Destructor. Clears objects array and free memory.
	*/
	~Composite();

	/*!
	Add brick into array
	\param[in] obj Brick to add
	*/
	virtual void add(BaseObject* obj) override;

	/*!
	Remove brick with user`s ID
	\param[in] ID ID of brick to remove
	*/
	void remove(int ID);

	/*!
	Modificate brick in array
	\todo ~~~
	*/
	virtual void modificate() override;

	/*!
	Get next highest ID from objects array. Need for getting unique ID for new bricks
	\return Next highest ID
	*/
	virtual int getID() override;

	/*!
	Clears objects array and free memory.
	*/
	void clear();

	int ID;							/*!< Highest id from objects array */
	vector<BaseObject*> objects;	/*!< Array of bricks */
};
