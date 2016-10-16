/*!
\file vertex.h "model/vertex.h"
\brief  Define vertex consisting 3 double coordinates
\author Dmitry Zaitsev
\copyright © BMSTU All rights violated.
\version 1.0
\date 16 October 2016

Provide interface for vertex coordinates
*/

#pragma once

#include "baseobject.h"

/*!
\class Vertex vertex.h "model/vertex.h"
\brief  Define vertex consisting 3 double coordinates

Provide interface for vertex coordinates
*/
class Vertex : public BaseObject
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
	Destructor fills coordinates with zero values
	*/
	~Vertex();

	/*!
	Updates X coordinate with user`s values
	\param[in] X Value of X coordinate to set
	*/
	void setX(double X);

	/*!
	Updates Y coordinate with user`s values
	\param[in] Y Value of Y coordinate to set
	*/
	void setY(double Y);

	/*!
	Updates Z coordinate with user`s values
	\param[in] Z Value of Z coordinate to set
	*/
	void setZ(double Z);

	/*!
	Gets X value of vertex coordinate
	\return X value
	*/
	double getX();

	/*!
	Gets Y value of vertex coordinate
	\return Y value
	*/
	double getY();

	/*!
	Gets Z value of vertex coordinate
	\return Z value
	*/
	double getZ();

	/*!
	Modificate coordinates (rotate/zoom etc)
	\todo param[in] modification
	*/
	virtual void modificate() override;

private:
	double X;	/*!< X coordinate of vertex */
	double Y;	/*!< Y coordinate of vertex */
	double Z;	/*!< Z coordinate of vertex */
};