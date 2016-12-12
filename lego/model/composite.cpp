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
	obj->ID = this->ID;
	this->objects.push_back(obj);
	this->ID++;
}

BaseObject* Composite::modificate(Modification* modification, Vertex* center)
{
	for (int i = 0; i < this->objects.size(); i++)
	{
		this->objects[i]->modificate(modification, center);
	}
	return this;
}

void Composite::remove(int ID)
{
	this->ID--;
	for (int i = 0; i < this->objects.size(); i++)
	{
		if (this->objects[i]->ID == ID)
		{
			delete this->objects[i];
			for (int j = i + 1; j < this->objects.size(); j++)
			{
				this->objects[j]->ID--;
			}
			this->objects.erase(this->objects.begin() + i);
			return;
		}
	}
}

Brick* Composite::get(int ID)
{
	for (int i = 0; i < this->objects.size(); i++)
	{
		if (this->objects[i]->ID == ID)
		{
			return this->objects[i];
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
	this->ID = 0;
}