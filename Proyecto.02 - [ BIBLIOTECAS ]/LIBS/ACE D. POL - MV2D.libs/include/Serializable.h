// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
//

#pragma once
#ifndef SERIALIZABLE_H_
#define SERIALIZABLE_H_

#include "checkML.h"

class Serializable
{
public:
	virtual const void saveToFile(ofstream& file) = 0;				// guardado en fichero
	virtual ~Serializable() {};
};














// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
#endif