// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
//

#pragma once
#ifndef SDL_OBJECT_H_
#define SDL_OBJECT_H_

#include "checkML.h"

#include "Serializable.h"
#include "Vector2D.h"
#include <list>

class SDL_Object : public Serializable
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

	virtual const void saveToFile(ofstream& file);

	virtual SDL_Rect const getDestRect();
	virtual Point2D const getPosAct() const { return pos; };			// devuelve la poscicion actual

	void const setItList(list<SDL_Object*>::iterator it) { itList = it; };
	list<SDL_Object*>::iterator getItList() { return itList; };
};














// developed by: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
#endif