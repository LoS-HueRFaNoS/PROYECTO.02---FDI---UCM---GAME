#pragma once
#ifndef SDL_ERROR_H_
#define SDL_ERROR_H_

//#include "checkML.h"

// inherits
#include "error.h"

class SDLerror : public error
{
public:
	SDLerror(char const* e) : error("SDL error: " + string(e) + "\n") {};
};

#endif