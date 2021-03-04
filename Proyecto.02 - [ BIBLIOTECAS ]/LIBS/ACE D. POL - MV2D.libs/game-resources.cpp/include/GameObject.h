// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
//

#pragma once
#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "checkML.h"

#include "SDL_Object.h"

class logic;
class GameObject : public SDL_Object
{
protected:
	logic* game = nullptr;

	GameObject() : SDL_Object() {};
	GameObject(	Point2D p, 
				uint w, 
				uint h, 
				logic* g	) : SDL_Object(p, w, h), game(g) {};
public:
	virtual ~GameObject() {};
	virtual void update() = 0;
	virtual void render() = 0;
};














// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
#endif