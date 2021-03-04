// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
//

#pragma once
#ifndef GAME_PLAYER_H_
#define GAME_PLAYER_H_

#include "checkML.h"

#include "GameCharacter.h"
#include "EventHandler.h"

#include "FileFormatError.h"

class GamePlayer : public GameCharacter, public EventHandler
{
public:
	GamePlayer() : GameCharacter(), sigDir() {};			// constructor por defecto
	GamePlayer(	Point2D pIni,	// GameCharacter
				uint r,			//fila y columna del frame del png
				uint c,
				Texture* t,		//puntero a la texture
				uint w,			//ancho y alto sdlRect 
				uint h		) : GameCharacter(pIni, r, c, t, w, h), sigDir() {};

	virtual const void saveToFile(ofstream& file) {};
	GamePlayer(ifstream& file, Texture* t) {};

	virtual void update() = 0;									// actualiza el siguiente paso del pacman
	virtual bool handleEvent(const SDL_Event& event) = 0;		// manejo de eventos de teclado
	virtual void morir();										// efectua la muerte del player (lo reinicia)

protected:
	Vector2D sigDir;										// siguiente direccion
};














// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
#endif