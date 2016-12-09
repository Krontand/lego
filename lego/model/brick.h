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

#include "normal.h"
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
	Brick& operator=(Brick brick);

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
	Adds normal in model.
	\param[in] noraml Normal to face
	*/
	void addNormal(Normal normal);

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
	virtual BaseObject* modificate(Modification* modification, Vertex* center) override;

	virtual void applyModification() override;

	Vertex sourceCenter;	/*!< Brick center after modification */
	Vertex center;			/*!< Brick center */

	vector<Vertex> sourceVertex;	/*!< Vertex array after modification */
	vector<Vertex> vertex;			/*!< Vertex array before modification (rotation, move) */
	vector<Vertex> svertex;			/*!< Vertex array in scene coordinates */

	vector<vector<Normal>> sourceNormal;	/*!< Normal to each vertex after modification */
	vector<vector<Normal>> VNormal;			/*!< Normal to each vertex before modification */
	vector<vector<Normal>> sVNormal;		/*!< Normal to each vertex in scene coordinates*/

	vector<Normal> FNormal;	/*!< Normals from object file */

	vector<Face> faces;		/*!< Faces array */

	COLORREF color;

	float t;
};
