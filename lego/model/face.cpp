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
	this->Vertices = other.Vertices;
	this->Normal = other.Normal;
	this->VNormal = other.VNormal;
	this->iterator = this->Vertices.begin();
}

Face::Face(Face&& other)
{
	this->Vertices = other.Vertices;
	this->Normal = other.Normal;
	this->VNormal = other.VNormal;
	this->iterator = this->Vertices.begin();
}

Face::~Face()
{
	for (int i = 0; i < 3; i++)
	{
		this->Vertices.push_back(0);
	}
}

Face& Face::operator=(const Face& face)
{
	this->Vertices = face.Vertices;
	this->Normal = face.Normal;
	this->VNormal = face.VNormal;
	this->iterator = this->Vertices.begin();
	return *this;
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

void Face::calcNormal(Vertex A, Vertex B, Vertex C)
{
	double nA = A.Y * (B.Z - C.Z) + B.Y * (C.Z - A.Z) + C.Y * (A.Z - B.Z);
	double nB = A.Z * (B.X - C.X) + B.Z * (C.X - A.X) + C.Z * (A.X - B.X);
	double nC = A.X * (B.Y - C.Y) + B.X * (C.Y - A.Y) + C.X * (A.Y - B.Y);

	this->Normal[0] = nA;
	this->Normal[1] = nB;
	this->Normal[2] = nC;

	this->Normal.normalize();

	this->VNormal.clear();

	this->VNormal.push_back(this->Normal);
	this->VNormal.push_back(this->Normal);
	this->VNormal.push_back(this->Normal);
}