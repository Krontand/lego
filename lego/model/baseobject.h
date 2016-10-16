/*!
\file baseobject.h "model/baseobject.h"
\brief  Base object
\author Dmitry Zaitsev
\copyright © BMSTU All rights violated.
\version 1.0
\date 16 October 2016

Parent of visible scene objects
*/

#pragma once

/*!
\class BaseObject baseobject.h "model/baseobject.h"
\brief  Base object. Virtual class. No realisation.

Parent of visible scene objects
*/
class BaseObject
{
public:
	/*!
	Modificate object`s coordinates (rotation/zoom etc)
	*/
	virtual void modificate() = 0;

	/*!
	Add object in composite (only for composite object)
	\param[in] obj Object to add in composite
	*/
	virtual void add(BaseObject* obj) {};

	/*!
	Different meanings: 
		In composite - get highest ID of objects.
		In brick - get ID of this brick.
	\return ID
	*/
	virtual int getID() { return -1; };
};