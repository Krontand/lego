#pragma once
#include <exception>

class BaseException : public std::exception
{
public:
	virtual const char* what() const = 0;
};

class AllocationMemoryError : public BaseException
{
public:
	virtual const char* what() const
	{
		return "Can't allocate memory!";
	}
};

class ModelChoosingError : public BaseException
{
public:
	virtual const char* what() const
	{
		return "Choose model to add from top select field!";
	}
};

class BrickChoosingError : public BaseException
{
public:
	virtual const char* what() const
	{
		return "Choose brick to modifiate from bottom select field!";
	}
};