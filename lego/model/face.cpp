#include "stdafx.h"
#include "../stdafx.h"
#include "face.h"

Face::Face()
{
	for (int i = 0; i < 3; i++)
	{
		this->Vertices.push_back(0);
	}
	this->iterator = this->Vertices.begin();
}

Face::Face(int A, int B, int C)
{
	this->Vertices.push_back(A);
	this->Vertices.push_back(B);
	this->Vertices.push_back(C);
	this->iterator = this->Vertices.begin();
}

Face::Face(const Face& other)
{
	this->Vertices = other.getFace();
	this->iterator = this->Vertices.begin();
}

Face::Face(Face&& other)
{
	this->Vertices = other.getFace();
	this->iterator = this->Vertices.begin();
}

Face::~Face()
{
	for (int i = 0; i < 3; i++)
	{
		this->Vertices.push_back(0);
	}
}

vector<int> Face::getFace()
{
	return this->Vertices;
}

vector<int> Face::getFace() const
{
	return this->Vertices;
}

int Face::getA()
{
	return this->Vertices[0];
}

int Face::getB()
{
	return this->Vertices[1];
}

int Face::getC()
{
	return this->Vertices[2];
}

int Face::getCurrent()
{
	return *(this->iterator);
}

int Face::getNext()
{
	this->iterator++;
	if (this->iterator == this->Vertices.end())
	{
		this->iterator = this->Vertices.begin();
	}
	return *(this->iterator);
}