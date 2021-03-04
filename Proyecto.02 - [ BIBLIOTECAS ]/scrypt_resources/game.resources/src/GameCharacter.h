// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
//

#pragma once
#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "checkML.h"
#include <fstream>

#include "SDL_Object.h"
#include "Texture.h"

class GameCharacter : public SDL_Object
{
protected:
	Point2D posIni;
	uint rowF, colF;		// coordenadas del frame
	Vector2D dir;
	Texture* text = nullptr;

protected:
	GameCharacter() : SDL_Object(), posIni(), rowF(), colF(), dir() {};
	GameCharacter(	Point2D pIni,
					uint r,
					uint c,
					Texture* t,
					uint w,
					uint h		) : SDL_Object(pIni, w, h), posIni(pIni), rowF(r), colF(c), dir(), text(t) {};
	
	virtual const void saveToFile(ofstream& file);
	GameCharacter(ifstream& file, Texture* t);

	virtual ~GameCharacter() {};

	Point2D const centerPos(const SDL_Rect rect);

public:
	virtual void render();
};














// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
#endif