#pragma once
#include <vector>
#include "../ecs/Entity.h"
#include "../Templates/RPGLogic.h"
#include "../GameObjects/Character.h"
using namespace std;


enum  Visibilidad { noVisitado, noEntrado,visitado };
class Casilla
{
private:
	//int look;
	vector<bool> direcciones;
	bool esSalida;
	bool esPosActual = false;
	int angulo = 0;
	Visibilidad visib;
	vector<enemyTemplate> enemyEnum;
	vector< Chest> cofres;
	SDLGame* game_;
public:
	Casilla(SDLGame* game);
	Casilla(SDLGame* game, bool _N, bool _E, bool _S, bool _O);
	~Casilla();
	vector<bool> checkCell();
	//vector<Chests*>* checkChests();        //devuelve el puntero del vector de los cofres, que puede consultar si es nulo, o que renderiza.
	//vector<Enemys*>* checkenemigos();		//devuelve el puntero del vector de los enemigos.
	Visibilidad getVisibilidad() {return visib; }
	void setVisibilidad(Visibilidad vi) { visib = vi; }
	void setSalida() { esSalida = true; }
	void setPosActual(bool value) { esPosActual = value; }
	void setLook(int ang) { angulo = ang; }
	void setDirs(Look dir) { direcciones[dir] = true; }
	bool isExit() { return esSalida; }
	void casillaRender(int x, int y);
	void addEnemy(enemyTemplate e) {
		enemyEnum.push_back(e);
	}
	vector<enemyTemplate>* getEnemy() { return &enemyEnum; }
};
