#pragma once
#ifndef ERROR_H_
#define ERROR_H_

//#include "checkML.h"

// inherits
#include <stdexcept>

using namespace std;
class error : public logic_error
{
protected:
	error(const char* info) : logic_error(info) {};
	error(string info) : logic_error(info) {};
public:
	virtual char const* what() const { return logic_error::what(); };
};

#endif
