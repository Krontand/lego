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
}

Brick::Brick(Brick&& brick)
{
	this->vertex = brick.getVertex();
	this->faces = brick.getFaces();
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

void Brick::modificate()
{
	//todo
}

int Brick::getID()
{
	return this->ID;
}

void Brick::setID(int ID)
{
	this->ID = ID;
}