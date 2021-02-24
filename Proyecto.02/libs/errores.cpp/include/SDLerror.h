#pragma once
#ifndef SDL_ERROR_H_
#define SDL_ERROR_H_

#include "checkML.h"

// inherits
#include "Error.h"

class SDLerror : public Error
{
public:
	SDLerror(char const* e, char const* type) : Error(e + string(type) + end + string(e) + end) {};
private:
	string e = " Unable to initialize ";
	string end = ";\n";
};














// developed by: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
#endif