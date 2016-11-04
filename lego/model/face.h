/*!
\file face.h "model/face.h"
\brief  Define face consisting 3 links to vetices
\author Dmitry Zaitsev
\copyright © BMSTU All rights violated.
\version 1.0
\date 16 October 2016

Contains links to verices
*/

#pragma once

#include "vertex.h"
#include "../geometry/gvector.h"

using std::vector;

/*!
\class Face face.h "model/face.h"
\brief Define face consisting 3 links to vetices

Contains links to verices
*/
class Face
{
public:
	/*!
	Emty constructor. Fills links with zero values.
	*/
	Face();

	/*!
	Constructor fills coordinates with user`s values
	\param[in] A first link of face
	\param[in] B second link of face
	\param[in] C third link of face
	*/
	Face(int A, int B, int C);

	/*!
	Constructor copy
	\param[in] other Face object to copy
	*/
	Face(const Face& other);

	/*!
	Constructor transfer
	\param[in] other Vertex object to transfer
	*/
	Face(Face&& other);

	/*!
	Destructor fills links with zero values
	*/
	~Face();

	/*!
	Copies incoming face.
	\param[in] face Source face to copy.
	\return Link to this object.
	*/
	Face& operator=(const Face& face);

	/*!
	Get first link of face
	\return first link from array
	*/
	int getA();

	/*!
	Get second link of face
	\return second link from array
	*/
	int getB();

	/*!
	Get third link of face
	\return third link from array
	*/
	int getC();

	/*!
	Get current link of face
	\return current link from array
	*/
	int getCurrent();

	/*!
	Get next link of face
	\return next link from array
	*/
	int getNext();

	/*!
	Calculate nurmal to face. Set face normal and vertices normal.
	\param[in] A First vertex of triangle
	\param[in] B Second vertex of triangle
	\param[in] C Third vertex of triangle
	*/
	void calcNormal(Vertex A, Vertex B, Vertex C);

	vector<int> Vertices;			/*!< Links array */

	GVector Normal;					/*!< Normal to face */
	vector<GVector> VNormal;		/*!< Normal to each vertex */

private:
	vector<int>::iterator iterator;	/*!< Iterator for links array */
};
