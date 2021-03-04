// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
//

#pragma once
#ifndef GHOST_H_
#define GHOST_H_

#include "checkML.h"

#include "GameCharacter.h"
#include <vector>

class Ghost : public GameCharacter		// hereda de GameCharacter
{
protected:												// atributos privados:
	int numGhost;										// numero de fantasma creado (-1 == SmartGhost)	
	vector<int> dirs;									// registrar las direcciones que puede tomar
	direction newRndDir();								// devuelve una direccion aleatoria de entre las posibles
	bool die;											// condición de vida (para comer o ser comido, podría servir para la animacion de vuelta)

public:
	Ghost() : GameCharacter(), numGhost(0), die(false) {};			// contructor por defecto
	Ghost(	Point2D pIni,
			uint r,
			uint c,
			Texture* t, 
			uint w,
			uint h,
			uint numGho) : GameCharacter(pIni, r, c, t, w, h), numGhost(numGho), dirs(), die(false)
	{
		 setGhostColors();
	};
	virtual ~Ghost() { dirs.clear(); };					// destructor

	virtual const void saveToFile(ofstream& file);
	Ghost(ifstream& file, Texture* t);

	virtual void update();							// actualiza el siguiente paso del fantasma
	virtual void morir();							// efectua la muerte del ghost (lo reinicia)
	
	void animation(direction dir);					// ejecuta la animacion por frames
	void resetPos() { pos.set(posIni); };			// vuelve a la posicion inicial
	int getNumGhost() { return numGhost; };
	bool getIsDie() { return die; };

private:
	bool checkMoves(SDL_Rect rect);				// actualiza la direcciones posibles, indica si hay alguna nueva
	void setGhostColors();						// segun el num. del ghost le pone un color (teniamos los nombres tambien)
	void showMoves();							// debugger: muestra los posibles movimientos por consola								
	void showName();							// debugger: muestra el nombre del fantasma por consola						
	void showGhost();							// debugger: muestra info del fantasma para debuggear
};














// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
#endif