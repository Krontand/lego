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

class VectorIndexError : public BaseException
{
public:
	virtual const char* what() const
	{
		return "Vector size is 4. Index is out out of range!";
	}
};