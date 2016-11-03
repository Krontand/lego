#include "stdafx.h"
#include "../stdafx.h"
#include "brick.h"
#include <time.h>

Brick::Brick()
{
}

Brick::Brick(const Brick& brick)
{
	this->vertex = brick.vertex;
	this->faces = brick.faces;
	this->center = brick.center;
}

Brick::Brick(Brick&& brick)
{
	this->vertex = brick.vertex;
	this->faces = brick.faces;
	this->center = brick.center;
}

Brick::~Brick()
{
	this->vertex.clear();
	this->faces.clear();
}

Brick& Brick::operator=(const Brick& brick)
{
	this->vertex = brick.vertex;
	this->faces = brick.faces;
	this->center = brick.center;
	return *this;
}

void Brick::addVertex(Vertex v)
{
	this->vertex.push_back(v);
}

void Brick::addFace(Face face)
{
	this->faces.push_back(face);
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
	if (!center)
	{
		center = &this->center;
	}

#pragma omp parallel for
	for (int i = 0; i < this->vertexCount(); i++)
	{
		this->vertex[i].modificate(modification, center);
	}
}