#pragma once
#ifndef ERROR_H_
#define ERROR_H_

#include "checkML.h"

// inherits
#include <stdexcept>

using namespace std;
class Error : public logic_error
{
protected:
	Error(const char* info) : logic_error(info) {};
	Error(string info) : logic_error(info) {};
public:
	virtual char const* what() const { return logic_error::what(); };
};














// developed by: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL)
#endif