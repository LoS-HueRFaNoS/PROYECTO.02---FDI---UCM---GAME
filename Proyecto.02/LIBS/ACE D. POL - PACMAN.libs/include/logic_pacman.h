// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
//

#pragma once
#ifndef LOGIC_PACMAN_H_
#define LOGIC_PACMAN_H_

#include "checkML.h"

#include "Ghost.h"
#include "Pacman.h"
#include "map_pacman.h"
#include "SmartGhost.h"
// inherits
#include "Serializable.h"
#include "Singleton.h"

const Vector2D VEL = Vector2D(7, 5);					// Movimiento global para todos los personajes
const int ENERGY = 240;									// recarga de energia
const int NUM_LVLS = 5;
const int NUM_GHOSTS = 4;								// numero de fantasmas (a mano para el array)

class logic_pacman : public Serializable, public Singleton<logic_pacman>
{
	friend Singleton<logic_pacman>;
	logic_pacman() : loseLife(false), foodLeft() {};
private:
	bool loseLife;
	uint foodLeft;										// comida restante
public:
	void load(uint lvlSelect);
	virtual ~logic_pacman() {};

	virtual void const saveToFile(ofstream& file);
	logic_pacman(ifstream& file);
	// pacman
	void setLoseLife(bool opt) { loseLife = opt; };
	bool getLoseLife() { return loseLife; };
	void addFood() { ++foodLeft; };
	void subsFood() { --foodLeft; };
	void collisionsPacman(const SDL_Rect& rect);
	bool outOfFood() const { return foodLeft == 0; };	// determina si se ha acabado la comida
	Pacman* getPacman();

	// smartghosts
	void resetGhost();
	double calculateDistanceFromPacman(const Point2D pos);
	bool SmartGhostCollision(SmartGhost* smartG);
};

inline logic_pacman& acedLogPacman() {
	return *logic_pacman::instance();
}














// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
#endif