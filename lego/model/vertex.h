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
	Gets X value of vertex coordinate. Const method.
	\return X value
	*/
	double getX() const;

	/*!
	Gets Y value of vertex coordinate
	\return Y value
	*/
	double getY();

	/*!
	Gets X value of vertex coordinate. Const method.
	\return X value
	*/
	double getY() const;

	/*!
	Gets Z value of vertex coordinate
	\return Z value
	*/
	double getZ();

	/*!
	Gets X value of vertex coordinate. Const method.
	\return X value
	*/
	double getZ() const;

	/*!
	Modificate coordinates (rotate/zoom etc)
	\param[in] modification Modification object
	*/
	virtual void modificate(Modification* modification, Vertex* center) override;

private:
	double X;	/*!< X coordinate of vertex */
	double Y;	/*!< Y coordinate of vertex */
	double Z;	/*!< Z coordinate of vertex */
};