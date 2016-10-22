#include "stdafx.h"
#include "../stdafx.h"
#include "brick.h"

Brick::Brick()
{
}

Brick::Brick(const Brick& brick)
{
	this->vertex = brick.getVertex();
	this->faces = brick.getFaces();
	this->center = brick.getCenter();
}

Brick::Brick(Brick&& brick)
{
	this->vertex = brick.getVertex();
	this->faces = brick.getFaces();
	this->center = brick.getCenter();
}

Brick::~Brick()
{
	this->vertex.clear();
	this->faces.clear();
}

Brick& Brick::operator=(const Brick& brick)
{
	this->vertex = brick.getVertex();
	this->faces = brick.getFaces();
	this->center = brick.getCenter();
	return *this;
}

void Brick::addVertex(Vertex v)
{
	Vertex tmp = v;
	this->vertex.push_back(v);
}

void Brick::addFace(Face face)
{
	this->faces.push_back(face);
}

void Brick::setCenter(Vertex vertex)
{
	this->center = vertex;
}

Vertex Brick::getCenter()
{
	return this->center;
}

Vertex Brick::getCenter() const
{
	return this->center;
}

vector<Vertex> Brick::getVertex() const
{
	return this->vertex;
}

vector<Face> Brick::getFaces() const
{
	return this->faces;
}

int Brick::vertexCount()
{
	return this->vertex.size();
}

int Brick::facesCount()
{
	return this->faces.size();
}

void Brick::modificate(Modification* modification, Vertex* center)
{
	for (int i = 0; i < this->vertexCount(); i++)
	{
		center = &this->center;
		this->vertex[i].modificate(modification, center);
	}
}

int Brick::getID()
{
	return this->ID;
}

void Brick::setID(int ID)
{
	this->ID = ID;
}