#pragma once
#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "checkML.h"

#include "SDL_Object.h"

class PlayState;
class GameObject : public SDL_Object
{
protected:
	PlayState* game = nullptr;

	GameObject() : SDL_Object() {};
	GameObject(	Point2D p, 
				uint w, 
				uint h, 
				PlayState* g	) : SDL_Object(p, w, h), game(g) {};
public:
	virtual ~GameObject() {};
	virtual void update() = 0;
	virtual void render() = 0;
};














// developed by: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL)
#endif