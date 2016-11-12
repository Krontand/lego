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
#include "..\model\vertex.h"

class Light : public Vertex
{
public:
	/*!
	Emty constructor. No action.
	*/
	Light() : Vertex() {}

	/*!
	Constructor. Settin light position
	\param[in] X Light position X
	\param[in] X Light position Y
	\param[in] X Light position Z
	*/
	Light(double X, double Y, double Z) : Vertex(X, Y, Z) {}

};
