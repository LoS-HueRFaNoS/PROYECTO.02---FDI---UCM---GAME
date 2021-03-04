// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
//

#pragma once
#ifndef LOGIC_GAME_H_
#define LOGIC_GAME_H_

#include "checkML.h"

#include "InfoBar.h"
#include "GamePlayer.h"
#include "GameMap.h"

#include "FileNotFoundError.h"
#include "FileFormatError.h"

// inherits
#include "Singleton.h"

const int INFOBAR = 1;											// alto para la barra de informacion (vidas + puntuacion)
const string fileMap = "../resources/maps/";					// cadena para abreviar el acceso a los mapas

class logic_game : public Singleton<logic_game>
{
	friend Singleton<logic_game>;
	logic_game() : wCell_(), hCell_(), lvl(), lvlPoints(), lives(), points() {};
protected:
	friend InfoBar;
	friend GameMap;
	uint wCell_, hCell_;									// tamano de las celdas -> lo utilizan otras clases para pintarse
	
	GameMap* map = nullptr;									// GameMap
	GamePlayer* player = nullptr;							// player (player)
	InfoBar* bar = nullptr;									// InfoBar
	
	uint lvlPoints;											// puntuacion en el nivel
	int lives;												// vidas restantes
	uint points;											// puntuacion
	uint lvl;
public:
	virtual ~logic_game() {};

	// info getters
	uint getLevel() { return lvl; };
	int getRows() const { return map->getRows(); };
	int getCols() const { return map->getCols(); };
	int getCell_h() const { return hCell_; };
	int getCell_w() const { return wCell_; };
	uint getLvl() { return lvl; };
	int getLives() { return lives; }
	uint getPoints() { return points; };
	uint getLvlPoints() { return lvlPoints; };
	// info setters
	void setLvl(uint lvlSelect) { lvl = lvlSelect; };
	void setInfoBar(InfoBar* b) { bar = b; };
	void setCellTam(uint wC, uint hC);
	void setInfo(uint lv, int lvs, uint pts, uint lvlPts);
	// info calculos
	int randomNumber(int num);
	double calculateDistanceFrom(const Point2D posA, const Point2D posB);		// calcula la distancia de 'B' hasta 'A'

	// movimiento por pixeles
	bool tryMove(const SDL_Rect& rect, Vector2D dir, Vector2D vel, Point2D& newPos);	// comprueba si choca con algo al moverse en cierta direccion
	Point2D SDLPointToMapCoords(Point2D point);
	Point2D mapCoordsToSDLPoint(Point2D coords);

	// player (player)
	GamePlayer* getPlayer() { return player; };
	void setPlayer(GamePlayer* gp) { player = gp; };
	void addPoints(const int pts);
	void addLives() { ++lives; };
	void subsLives() { --lives; };
	bool isAlive();
	template<typename T> bool checkCollisions(const SDL_Rect& rect);	// comprueba colisiones con los objetos del tipo indicado
	
	// npc's
	void eraseObject(list<SDL_Object*>::iterator it);

	// map
	GameMap* getMap() { return map; };
	void setMap(GameMap* gm) { map = gm; };
	MapCell showCell(const Point2D pos) const;
	MapCell showCell(const uint r, const uint c) const;
	void clearCell(const Point2D pos);
	void setCell(const uint r, const uint c, MapCell mc) const;

	// ficheros
	void abrirNivel(ifstream& file);
};

inline logic_game& acedLogic() {
	return *logic_game::instance();
}














// @autor: Pedro Pablo Cubells Talavera (player, ACE D. POL) [https://github.com/player]
#endif