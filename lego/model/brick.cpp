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
	this->sVNormal = brick.sVNormal;
	this->FNormal = brick.FNormal;
	this->center = brick.center;
}

Brick::Brick(Brick&& brick)
{
	this->vertex = brick.vertex;
	this->svertex = brick.svertex;
	this->faces = brick.faces;
	this->VNormal = brick.VNormal;
	this->sVNormal = brick.sVNormal;
	this->FNormal = brick.FNormal;
	this->center = brick.center;
}

Brick::~Brick()
{
	this->vertex.clear();
	this->svertex.clear();
	this->faces.clear();
	this->VNormal.clear();
	this->sVNormal.clear();
	this->FNormal.clear();
}

Brick& Brick::operator=(const Brick& brick)
{
	this->vertex = brick.vertex;
	this->svertex = brick.svertex;
	this->faces = brick.faces;
	this->VNormal = brick.VNormal;
	this->sVNormal = brick.sVNormal;
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
	vector<Normal> tmp;
	for (int i = 0; i < 3; i++)
	{
		tmp.push_back(Normal(this->FNormal[face.getNormal() - 1]));
		face.getNextNormal();
	}
	this->VNormal.push_back(tmp);
	this->sVNormal.push_back(tmp);
}

void Brick::addNormal(Normal normal)
{
	this->FNormal.push_back(normal);
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

	modification->initModification(center);

#pragma omp parallel for
	for(int i = 0; i < this->vertexCount(); i++)
	{
		this->vertex[i].modificate(modification, center);	
	}

	for (int i = 0; i < this->facesCount(); i++)
	{
		for (int j = 0; j < 3; j++)
		{
			this->VNormal[i][j].modificate(modification, center);
		}
	}

}	