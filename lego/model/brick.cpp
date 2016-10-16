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
	this->vertex.push_back(v);
}

void Brick::addFace(int A, int B, int C)
{
	vector<int> tmp(3);
	tmp[0] = A;
	tmp[1] = B;
	tmp[2] = C;
	this->faces.push_back(tmp);
}

vector<Vertex> Brick::getVertex() const
{
	return this->vertex;
}

vector<vector<int>> Brick::getFaces() const
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