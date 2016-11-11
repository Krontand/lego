/*!
\file brick.h "model/brick.h"
\brief  Model basement
\author Dmitry Zaitsev
\copyright © BMSTU All rights violated.
\version 2.0
\date 16 October 2016

Contains model archetecture
*/

#pragma once
using std::vector;

#include "vertex.h"
#include "face.h"

/*!
\class Brick brick.h "model/brick.h"
\brief  Brick archetecture

Provide interface brick values
*/
class Brick : public BaseObject
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
	Constructor. Transfer incoming model.
	\param[in] brick Source model to transfer.
	*/
	Brick::Brick(Brick&& brick);

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
	\param[in] face Vector of 3 links
	*/
	void addFace(Face face);

	/*!
	Calculate normal to face. Set face normal.
	\param[in] A First vertex of triangle
	\param[in] B Second vertex of triangle
	\param[in] C Third vertex of triangle
	*/
	void calcNormal(int A, int B, int C);

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

	/*!
	Modificate coordinates (rotate/zoom etc)
	\param[in] modification Modification object
	*/
	virtual void modificate(Modification* modification, Vertex* center) override;

	Vertex center;		/*!< Brick center */

	vector<Vertex> vertex;				/*!< Vertex array */
	vector<vector<GVector>> VNormal;	/*!< Normal to each vertex */

	vector<Face> faces;			/*!< Faces array */
	vector<GVector> FNormal;	/*!< Normal to face */
};
