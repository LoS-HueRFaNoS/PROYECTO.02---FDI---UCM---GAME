// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
//

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














// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
#endif