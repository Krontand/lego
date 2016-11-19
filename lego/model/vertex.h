/*!
\file vertex.h "model/vertex.h"
\brief  Define vertex consisting 3 double coordinates
\author Dmitry Zaitsev
\copyright © BMSTU All rights violated.
\version 2.0
\date 16 October 2016

Provide interface for vertex coordinates
*/

#pragma once

#include "modification\modification.h"
#include "baseobject.h"
#include "../geometry\gmatrix.h"

/*!
\class Vertex vertex.h "model/vertex.h"
\brief  Define vertex consisting 3 double coordinates

Provide interface for vertex coordinates
*/
class Vertex: public BaseObject
{
public:
	/*!
	Emty constructor. Fills coordinates with zero values.
	*/
	Vertex();

	/*!
	Constructor fills coordinates with user`s values
	\param[in] X X coordinate of vertex
	\param[in] Y Y coordinate of vertex
	\param[in] Z Z coordinate of vertex
	*/
	Vertex(double X, double Y, double Z);

	/*!
	Constructor copy
	\param[in] other Vertex object to copy
	*/
	Vertex(const Vertex& other);

	/*!
	Constructor transfer
	\param[in] other Vertex object to transfer
	*/
	Vertex(Vertex&& other);

	/*!
	Destructor fills coordinates with zero values
	*/
	~Vertex();

	/*!
	Copy vertex
	\param[in] other Vertex object to copy
	*/
	Vertex& operator=(const Vertex& other);

	/*!
	Transfer vertex
	\param[in] other Vertex object to transfer
	*/
	Vertex& operator=(Vertex&& other);

	/*!
	Transform vertex into vector format
	\return vector
	*/
	GVector vector();

	/*!
	Multiply this vertex by matrix
	\param[in] matrix Matrix to multiply
	\return Vertex multiplied by matrix
	*/
	Vertex operator*(GMatrix matrix);

	/*!
	Modificate coordinates (rotate/zoom etc)
	\param[in] modification Modification object
	*/
	virtual void modificate(Modification* modification, Vertex* center) override;

	double X;	/*!< X coordinate of vertex */
	double Y;	/*!< Y coordinate of vertex */
	double Z;	/*!< Z coordinate of vertex */
};