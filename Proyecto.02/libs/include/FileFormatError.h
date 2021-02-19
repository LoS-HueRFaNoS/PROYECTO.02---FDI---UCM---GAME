#pragma once
#ifndef FILEFORMAT_ERROR_H_
#define FILEFORMAT_ERROR_H_

#include "checkML.h"
// inherits
#include "Error.h"

class FileFormatError : public Error
{
public:
	FileFormatError(char const* e) : Error("File Format Error: " + string(e) + "\n;") {};
};














// developed by: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL)
#endif