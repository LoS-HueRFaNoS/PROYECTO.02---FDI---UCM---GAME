// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
//

#pragma once
#ifndef FILENOTFOUND_ERROR_H_
#define FILENOTFOUND_ERROR_H_

#include "checkML.h"

// inherits
#include "Error.h"

class FileNotFoundError : public Error
{
public:
	FileNotFoundError(string e) : Error("File Not Found error: " + e + "\n;") {};
};














// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
#endif