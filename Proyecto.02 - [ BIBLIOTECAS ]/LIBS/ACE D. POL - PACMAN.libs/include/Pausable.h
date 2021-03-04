// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
//

#pragma once
#ifndef PAUSABLE_H_
#define PAUSABLE_H_

#include "checkML.h"

class Pausable
{
protected:
	bool pause;
	virtual void cancelPause() { pause = false; };				// reanuda el bucle principal
	virtual void setPause() { pause = true; };					// entra en modo pausa (inhibe la actualizacion de datos)
	virtual ~Pausable() {};
};














// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
#endif