/*!
\file modification.h "model/modification/modification.h"
\brief  Base modification object class
\author Dmitry Zaitsev
\copyright © BMSTU All rights violated.
\version 1.0
\date 22 October 2016

Virtual class
*/

#pragma once
#include "../vertex.h"
#include "../normal.h"

class Vertex;
class Normal;

/*!
\class Modification modification.h "model/modification/modification.h"
\brief  Base modification object class

Virtual class
*/
class Modification
{
public:
	/*!
	Emty constructor. No action.
	*/
	Modification() {}

	/*!
	Detructor. No action.
	*/
	~Modification() {}

	/*!
	Set center around which occur modificaion
	\param[in] center Point of modification center
	*/
	virtual void setCenter(Vertex* center) = 0;

	/*!
	Launches modification
	\param[in] vertex Object to modificate
	*/
	virtual void run(Vertex* vertex) = 0;

	/*!
	Launches modification
	\param[in] normal Object to modificate
	*/
	virtual void run(Normal* normal) = 0;
};
