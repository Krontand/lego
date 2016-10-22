#pragma once
#include "../vertex.h"

class Vertex;

class Modification
{
public:
	Modification() {}
	~Modification() {}

	virtual void setCenter(Vertex* center) = 0;
	virtual void run(Vertex* vertex) = 0;
};
