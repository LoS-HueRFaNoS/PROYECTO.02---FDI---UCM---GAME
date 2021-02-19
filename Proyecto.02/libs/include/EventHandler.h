#pragma once
#ifndef EVENT_HANDLER_H_
#define EVENT_HANDLER_H_

#include "checkML.h"
#include "SDL.h"

class EventHandler
{
public:
	virtual bool handleEvent(const SDL_Event& event) = 0;				// manejo de eventos de teclado
	virtual ~EventHandler() {};
};














// developed by: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL)
#endif