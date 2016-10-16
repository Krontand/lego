#pragma once

#include "../exception.h"

class LoaderError : public BaseException
{
public:
	virtual const char* what() const
	{
		return "Can not load model!";
	}
};

class LoaderOpenFileError : public BaseException
{
public:
	virtual const char* what() const
	{
		return "Can not open file! Please check if file exists!";
	}
};

class LoaderBadFile : public BaseException
{
public:
	virtual const char* what() const
	{
		return "Wrong file structure!";
	}
};

class CompositeAddNULLError : public BaseException
{
public:
	virtual const char* what() const
	{
		return "Attempting to add NULL item into composite!";
	}
};
