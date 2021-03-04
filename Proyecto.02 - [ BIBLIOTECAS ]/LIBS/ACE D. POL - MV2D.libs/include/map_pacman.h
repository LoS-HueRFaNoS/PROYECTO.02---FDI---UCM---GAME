// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
//

#pragma once
#ifndef MAP_H_
#define MAP_H_

#include "checkML.h"

#include "GameMap.h"

class map_pacman : public GameMap
{
public:
	map_pacman(	Point2D pIni,
				uint rs,
				uint cs,
				uint w,
				uint h		) : GameMap(pIni, rs, cs, w, h) {};
	
	map_pacman(ifstream& file);
	virtual ~map_pacman() {};							// destructor
};














// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
#endif