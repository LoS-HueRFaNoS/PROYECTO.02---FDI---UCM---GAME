#pragma once
#ifndef MENU_OBJECT_H_
#define MENU_OBJECT_H_

#include "checkML.h"

#include "SDL_Object.h"
#include "EventHandler.h"
#include "Texture.h"                                                                                                                                                                                                               

typedef const char* word;

class menuMachine;
class MenuObject : public SDL_Object, public EventHandler
{
protected:
	Point2D RP;
	menuMachine* engine = nullptr;
	Texture* text = nullptr;
	bool hidden;
public:
	MenuObject() : SDL_Object(), text() {};
	MenuObject(Point2D rp, menuMachine* e, Texture* t, Point2D p, uint w, uint h) : SDL_Object(p, w, h), RP(rp), engine(e), text(t), hidden(false) {};
	virtual ~MenuObject() {};

	virtual void update() = 0;
	virtual void render() = 0;
	virtual bool handleEvent(const SDL_Event& event) = 0;		// manejo de eventos de teclado

	void setHidden(bool c) { hidden = c; };
	Point2D getMidPos();
};














// developed by: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL)
#endif