// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
//

#pragma once
#ifndef MOTOR_H_
#define MOTOR_H_

#include "checkML.h"

class motor
{
protected:
	virtual void run() = 0;									// bucle principal
	virtual void update() = 0;								// actualizador
	virtual void render() = 0;								// draw estado actual
	virtual bool handleEvent(const SDL_Event& event) = 0;	// manejo de eventos
};














// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
#endif