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
	\param[in] modification Type of modification
	\param[in] center Modification center
	*/
	virtual BaseObject* modificate(Modification* modification, Vertex* center = nullptr) { return this; };

	/*!
	Brick object doesn't modificate itself but safes new vertices/normals
	This function set modified parameters for whole object
	*/
	virtual void applyModification() = 0;

	/*!
	In modification methods we need to know 
	what kind of object we use: vertex or normal
	so here we know
	\return true if object is vertex, false in other case
	*/
	virtual bool isVertex() { return false; }

	/*!
	Different meanings: 
		In composite - get highest ID of objects.
		In brick - get ID of this brick.
	*/
	int ID;
};