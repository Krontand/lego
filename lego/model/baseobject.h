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
#include "modification\modification.h"

class Vertex;
class Modification;

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
	virtual void modificate(Modification* modification, Vertex* center) = 0;

	/*!
	Different meanings: 
		In composite - get highest ID of objects.
		In brick - get ID of this brick.
	\return ID
	*/
	virtual int getID() { return -1; };
};