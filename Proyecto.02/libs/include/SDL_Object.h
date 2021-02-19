#pragma once
#ifndef SDL_OBJECT_H_
#define SDL_OBJECT_H_

#include "checkML.h"

#include "SDL.h"
#include "Vector2D.h"
#include <list>

class SDL_Object
{
protected:
	Point2D pos;
	uint width, height;
	list <SDL_Object*>::iterator itList;
protected:
	SDL_Object() : pos(), width(), height() {};
	SDL_Object(Point2D p, uint w, uint h) : pos(p), width(w), height(h) {};
	
public:
	virtual ~SDL_Object() {};
	virtual void update() = 0;
	virtual void render() = 0;

	virtual SDL_Rect const getDestRect();
	virtual Point2D const getPosAct() const { return pos; };			// devuelve la poscición actual

	void const setItList(list<SDL_Object*>::iterator it) { itList = it; };
};














// developed by: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL)
#endif