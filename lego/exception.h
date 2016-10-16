#pragma once
#include <exception>

class BaseException : public std::exception
{
public:
	virtual const char* what() const = 0;
};