#pragma once
#include <vector>
#include "Entity.h"
#include "Character.h"
#include "RPGLogic.h"
#include "Item.h"
using namespace std;


enum  Visibilidad { noVisitado, noEntrado,visitado };

class Casilla
{
private:
	//int look;
	vector<bool> direcciones;
	bool esSalida;
	Visibilidad visib;
	vector<enemyTemplate> enemyEnum;
	vector< Chest> cofres;

public:
	Casilla();
	Casilla( bool _N, bool _E, bool _S, bool _O);
	~Casilla();
	vector<bool> checkCell();
	//vector<Chests*>* checkChests();        //devuelve el puntero del vector de los cofres, que puede consultar si es nulo, o que renderiza.
	//vector<Enemys*>* checkenemigos();		//devuelve el puntero del vector de los enemigos.
	Visibilidad getVisibilidad() {return visib; }
	void setVisibilidad(Visibilidad vi) { visib = vi; }
	void setSalida() { esSalida = true; }
	void setDirs(Look dir) { direcciones[dir] = true; }
	bool isExit() { return esSalida; }
	void addEnemy(enemyTemplate e) {
		enemyEnum.push_back(e);
	}
	vector<enemyTemplate>* getEnemy() { return &enemyEnum; }
	void addChest(ItemType it, int itId)
	{
		cofres.push_back({ it,itId });
	}
	vector<Chest>* getChest() { return &cofres; }
};

