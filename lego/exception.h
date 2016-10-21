#pragma once
#include <exception>

class BaseException : public std::exception
{
public:
	virtual const char* what() const = 0;
};

class AllocationMemoryError : public std::exception
{
public:
	virtual const char* what() const
	{
		return "Can't allocate memory!";
	}
};