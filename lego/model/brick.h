/*!
\file brick.h "model/brick.h"
\brief  Model basement
\author Dmitry Zaitsev
\copyright © BMSTU All rights violated.
\version 1.0
\date 16 October 2016

Contains model archetecture
*/

#pragma once
using namespace std;

#include "vertex.h"

/*!
\class Brick brick.h "model/brick.h"
\brief  Brick archetecture

Provide interface brick values
*/
class Brick
{
public:
	/*!
	Emty constructor. No action.
	*/
	Brick();

	/*!
	Constructor. Copies incoming model.
	\param[in] brick Source model to copy.
	*/
	Brick(const Brick& brick);

	/*!
	Destructor. Clears vertex and faces array.
	*/
	~Brick();

	/*!
	Copies incoming model.
	\param[in] brick Source model to copy.
	\return Link to this object.
	*/
	Brick& operator=(const Brick& brick);

	/*!
	Adds vertex in model.
	\param[in] v Vertex to add in array.
	*/
	void addVertex(Vertex v);

	/*!
	Adds face in model.
	\param[in] A First point of face
	\param[in] B Second point of face
	\param[in] C Third point of face
	*/
	void addFace(int A, int B, int C);

	/*!
	Provides access to vertex array
	\return Vertex array
	*/
	vector<Vertex> getVertex() const;

	/*!
	Provides access to faces array
	\return Faces array
	*/
	vector<vector<int>> getFaces() const;

	/*!
	Amount of vertex in model
	\return Amount of items
	*/
	int vertexCount();

	/*!
	Amount of faces in model
	\return Amount of items
	*/
	int facesCount();

private:
	vector<Vertex> vertex;		/*!< Vertex array */
	vector<vector<int>> faces;	/*!< Faces array */
};
