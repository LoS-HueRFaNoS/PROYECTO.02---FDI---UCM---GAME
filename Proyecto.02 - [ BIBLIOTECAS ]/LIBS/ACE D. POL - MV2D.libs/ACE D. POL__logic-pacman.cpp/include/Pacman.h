// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
//

#pragma once
#ifndef PACMAN_H_
#define PACMAN_H_

#include "checkML.h"

#include "GamePlayer.h"

const int VIDAS = 3;		// num vidas

class Pacman : public GamePlayer	// hereda de GamePlayer
{
private:
	Vector2D sigDir;										// siguiente direccion
	int energia;											// energia restante

public:
	Pacman() : GamePlayer(), sigDir() { energia = -1; };			// constructor por defecto
	Pacman(	Point2D pIni,	// GameCharacter
			uint r,			//fila y columna del frame del png
			uint c,
			Texture* t,		//puntero a la texture
			uint w,			//ancho y alto sdlRect 
			uint h	) : GamePlayer(pIni, r, c, t, w, h), sigDir(), energia(-1) {};
	
	Pacman(ifstream& file, Texture* t);
	virtual const void saveToFile(ofstream& file);

	virtual void update();									// actualiza el siguiente paso del pacman
	virtual bool handleEvent(const SDL_Event& event);		// manejo de eventos de teclado

	int getEnergy() const { return energia; };				// devuelve la energia actual

private:
	void efecto(const Point2D pAct);			// analiza el efecto de la siguiente posicion
	void animation(direction dir);				// ejecuta la animacion por frames
};














// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
#endif