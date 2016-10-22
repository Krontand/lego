#include "stdafx.h"
#include "../stdafx.h"
#include "composite.h"

Composite::Composite()
{
	this->ID = 0;
}

Composite::~Composite()
{
	this->clear();
}

void Composite::add(Brick* obj)
{
	if (!obj)
	{
		throw CompositeAddNULLError();
	}
	this->objects.push_back(obj);
	this->ID++;
}

void Composite::modificate(Modification* modification, Vertex* center)
{
	for (int i = 0; i < this->objects.size(); i++)
	{
		this->objects[i]->modificate(modification, center);
	}
}

int Composite::getID()
{
	return this->ID;
}

void Composite::remove(int ID)
{
	for (int i = 0; i < this->objects.size(); i++)
	{
		if (this->objects[i]->getID() == ID)
		{
			delete this->objects[i];
			this->objects.erase(this->objects.begin() + i);
			break;
		}
	}
}

void Composite::clear()
{
	for (int i = 0; i < this->objects.size(); i++)
	{
		delete this->objects[i];
		this->objects.erase(this->objects.begin() + i);
	}
}