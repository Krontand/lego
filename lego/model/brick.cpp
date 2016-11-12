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
	this->svertex = brick.svertex;
	this->faces = brick.faces;
	this->VNormal = brick.VNormal;
	this->FNormal = brick.FNormal;
	this->center = brick.center;
}

Brick::Brick(Brick&& brick)
{
	this->vertex = brick.vertex;
	this->svertex = brick.svertex;
	this->faces = brick.faces;
	this->VNormal = brick.VNormal;
	this->FNormal = brick.FNormal;
	this->center = brick.center;
}

Brick::~Brick()
{
	this->vertex.clear();
	this->svertex.clear();
	this->faces.clear();
	this->VNormal.clear();
	this->FNormal.clear();
}

Brick& Brick::operator=(const Brick& brick)
{
	this->vertex = brick.vertex;
	this->svertex = brick.svertex;
	this->faces = brick.faces;
	this->VNormal = brick.VNormal;
	this->FNormal = brick.FNormal;
	this->center = brick.center;
	return *this;
}

void Brick::addVertex(Vertex v)
{
	this->vertex.push_back(v);
	this->svertex.push_back(v);
}

void Brick::addFace(Face face)
{
	this->faces.push_back(face);
}

void Brick::calcNormal(int vA, int vB, int vC)
{
	Vertex A = this->vertex[vA - 1];
	Vertex B = this->vertex[vB - 1];
	Vertex C = this->vertex[vC - 1];

	double nA = A.Y * (B.Z - C.Z) + B.Y * (C.Z - A.Z) + C.Y * (A.Z - B.Z);
	double nB = A.Z * (B.X - C.X) + B.Z * (C.X - A.X) + C.Z * (A.X - B.X);
	double nC = A.X * (B.Y - C.Y) + B.X * (C.Y - A.Y) + C.X * (A.Y - B.Y);

	this->FNormal.push_back(GVector(nA, nB, nC, 0));

	this->FNormal[FNormal.size() - 1].normalize();

	vector<GVector> tmp;
	for (int i = 0; i < 3; i++)
	{
		tmp.push_back(this->FNormal[FNormal.size() - 1]);
	}
	this->VNormal.push_back(tmp);
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