// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
//

#pragma once
#ifndef GAMEMAP_H_
#define GAMEMAP_H_

#include "checkML.h"

#include "SDL_Object.h"
#include "Serializable.h"

enum MapCell { Empty, Wall, Food, Vitamins, Door };		// enum de tipos de celdas

class GameMap : public SDL_Object
{
protected:
	friend class logic_game;									// clase amiga: ahora puede acceder a variables privadas de esta clase.

	int rows = 0;										// numero de filas en la matriz SDL
	int cols = 0;										// numero de columnas en la matriz SDL
	MapCell** cells = nullptr;							// array dinamico de MapCell dinamicos

public:
	GameMap	(	Point2D pIni,
				uint rs,
				uint cs,
				uint w,
				uint h		);
	GameMap(ifstream& file);
	virtual ~GameMap();									// destructor

	virtual void update() {};
	virtual void render();								// anade los elementos del mapa a la escena
	virtual const void saveToFile(ofstream& file);

	int getRows() const { return rows; };
	int getCols() const { return cols; };

	bool intersectsWall(SDL_Rect rect);		// comprueba si hay colision con alguna casillas de alrededor
};














// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
#endif