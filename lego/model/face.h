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
	Face(int A, int nA, int B, int nB, int C, int nC);

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
	Get first link of vertex
	\return first link from array
	*/
	int A();

	/*!
	Get second link of vertex
	\return second link from array
	*/
	int B();

	/*!
	Get third link of vertex
	\return third link from array
	*/
	int C();

	/*!
	Get first link of normal
	\return first link from array
	*/
	int nA();

	/*!
	Get second link of normal
	\return second link from array
	*/
	int nB();

	/*!
	Get third link of normal
	\return third link from array
	*/
	int nC();

	/*!
	Get current link of vertex
	\return current link from array
	*/
	int getVertex();

	/*!
	Get next link of vertex
	\return next link from array
	*/
	int getNextVertex();

	/*!
	Get current link of normal
	\return current link from array
	*/
	int getNormal();

	/*!
	Get next link of normal
	\return next link from array
	*/
	int getNextNormal();

	vector<int> Vertices;			/*!< Links array */
	vector<int> Normals;			/*!< Links array */

private:
	vector<int>::iterator viterator;	/*!< Iterator for links array */
	vector<int>::iterator niterator;	/*!< Iterator for links array */
};
