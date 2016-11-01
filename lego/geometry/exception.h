#pragma once

#include "../exception.h"

class VectorSizeError : public BaseException
{
public:
	virtual const char* what() const
	{
		return "Geometric vector size should be 4!";
	}
};