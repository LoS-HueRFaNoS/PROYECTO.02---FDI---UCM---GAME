// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
//

#pragma once
#ifndef EVENT_HANDLER_H_
#define EVENT_HANDLER_H_

#include "checkML.h"

class EventHandler
{
public:
	virtual bool handleEvent(const SDL_Event& event) = 0;				// manejo de eventos de teclado
	virtual ~EventHandler() {};
};














// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
#endif