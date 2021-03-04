// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
//

#pragma once
#ifndef ACEDPOL_PACMAN_H_
#define ACEDPOL_PACMAN_H_

#include "checkML.h"
// inherits
#include "Singleton.h"

class acedpol_pacman : public Singleton<acedpol_pacman>
{
	friend Singleton<acedpol_pacman>;
public:
	acedpol_pacman();
	virtual ~acedpol_pacman() {};

	void run();
};

inline acedpol_pacman& acedPac() {
	return *acedpol_pacman::instance();
}














// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
#endif