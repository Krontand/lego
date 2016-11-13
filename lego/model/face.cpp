#include "stdafx.h"
#include "../stdafx.h"
#include "face.h"

Face::Face()
{
	for (int i = 0; i < 3; i++)
	{
		this->Vertices.push_back(0);
	}
	this->viterator = this->Vertices.begin();

	for (int i = 0; i < 3; i++)
	{
		this->Normals.push_back(0);
	}
	this->niterator = this->Normals.begin();
}

Face::Face(int A, int nA, int B, int nB, int C, int nC)
{
	this->Vertices.push_back(A);
	this->Vertices.push_back(B);
	this->Vertices.push_back(C);
	this->Normals.push_back(nA);
	this->Normals.push_back(nB);
	this->Normals.push_back(nC);

	this->viterator = this->Vertices.begin();
	this->niterator = this->Normals.begin();
}

Face::Face(const Face& other)
{
	this->Vertices = other.Vertices;
	this->viterator = this->Vertices.begin();
	this->Normals = other.Normals;
	this->niterator = this->Normals.begin();
}

Face::Face(Face&& other)
{
	this->Vertices = other.Vertices;
	this->viterator = this->Vertices.begin();
	this->Normals = other.Normals;
	this->niterator = this->Normals.begin();
}

Face::~Face()
{
}

Face& Face::operator=(const Face& face)
{
	this->Vertices = face.Vertices;
	this->viterator = this->Vertices.begin();
	this->Normals = face.Normals;
	this->niterator = this->Normals.begin();
	return *this;
}

int Face::A()
{
	return this->Vertices[0];
}

int Face::B()
{
	return this->Vertices[1];
}

int Face::C()
{
	return this->Vertices[2];
}

int Face::nA()
{
	return this->Normals[0];
}

int Face::nB()
{
	return this->Normals[1];
}

int Face::nC()
{
	return this->Normals[2];
}

int Face::getVertex()
{
	return *(this->viterator);
}

int Face::getNextVertex()
{
	this->viterator++;
	if (this->viterator == this->Vertices.end())
	{
		this->viterator = this->Vertices.begin();
	}
	return *(this->viterator);
}

int Face::getNormal()
{
	return *(this->niterator);
}

int Face::getNextNormal()
{
	this->niterator++;
	if (this->niterator == this->Normals.end())
	{
		this->niterator = this->Normals.begin();
	}
	return *(this->niterator);
}
