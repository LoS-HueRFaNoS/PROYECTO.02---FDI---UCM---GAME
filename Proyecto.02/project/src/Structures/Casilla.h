#pragma once
#include <vector>
#include "../ecs/Entity.h"
#include "../Templates/RPGLogic.h"
#include "../GameObjects/Character.h"
#include "../GameObjects/ObjectChest.h"
using namespace std;


enum  Visibilidad { noVisitado, noEntrado,visitado };
class Casilla
{
private:
	Look direccionSalida;
	/*Look direccionCofre;*/
	vector<bool> direcciones;
	bool esSalida;
	bool esPosActual = false;
	int angulo = 0;
	Visibilidad visib;
	vector<enemyTemplate> enemyEnum;
	ObjectChest* chest;
	bool hayCofre = false;
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
	void setSalida();
	void setPosActual(bool value) { esPosActual = value; }
	void setLook(int ang) { angulo = ang; }
	void setDirs(Look dir) { direcciones[dir] = true; }
	bool isExit() { return esSalida; }
	void casillaRender(int x, int y, double w, double h);
	void addEnemy(enemyTemplate e) {
		enemyEnum.push_back(e);
	}
	void addChest(Chest* e);
	ObjectChest* getChest() { return chest; }
	bool hasChest()
	{
		return hayCofre;
	}
	vector<enemyTemplate>* getEnemy() { return &enemyEnum; }
	Look getDirSalida() { return direccionSalida; }
	/*Look getDirCofre() { return direccionCofre; }*/
};

