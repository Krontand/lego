#include "stdafx.h"
#include "../../stdafx.h"
#include "movement.h"

Movement::Movement()
{
}

Movement::~Movement()
{
}

void Movement::moveX(BaseObject* o)
{
	if (o->isVertex())
	{
		*(Vertex*)o = *(Vertex*)o * this->move;
	}
	else
	{
		*(Normal*)o = *(Normal*)o * this->nmove;
	}
}

void Movement::moveY(BaseObject* o)
{
	if (o->isVertex())
	{
		*(Vertex*)o = *(Vertex*)o * this->move;
	}
	else
	{
		*(Normal*)o = *(Normal*)o * this->nmove;
	}
}

void Movement::moveZ(BaseObject* o)
{
	if (o->isVertex())
	{
		*(Vertex*)o = *(Vertex*)o * this->move;
	}
	else
	{
		*(Normal*)o = *(Normal*)o * this->nmove;
	}
}

void Movement::initModification(Vertex* center)
{
	// Nothing to initialize :)
	// Just blessing our code to complete succesufully!
}

MovementX::MovementX()
{
}

MovementX::MovementX(double shift)
{
	this->shift = shift;
	this->move = matrixMove(shift, 0 ,0);
	this->nmove = this->move;
	this->nmove.transposition();
	this->nmove.inverse();
}

MovementX::~MovementX()
{
}

void MovementX::run(BaseObject* o)
{
	this->moveX(o);
}

MovementY::MovementY()
{
}

MovementY::MovementY(double shift)
{
	this->shift = shift;
	this->move = matrixMove(0, shift, 0);
	this->nmove = this->move;
	this->nmove.transposition();
	this->nmove.inverse();
}

MovementY::~MovementY()
{
}

void MovementY::run(BaseObject* o)
{
	this->moveY(o);
}


MovementZ::MovementZ()
{
}

MovementZ::MovementZ(double shift)
{
	this->shift = shift;
	this->move = matrixMove(0, 0, shift);
	this->nmove = this->move;
	this->nmove.transposition();
	this->nmove.inverse();
}

MovementZ::~MovementZ()
{
}

void MovementZ::run(BaseObject* o)
{
	this->moveZ(o);
}

