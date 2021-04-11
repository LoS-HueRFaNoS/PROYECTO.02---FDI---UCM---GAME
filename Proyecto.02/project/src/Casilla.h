#pragma once
#include <vector>
#include "Entity.h"
#include "Character.h"
using namespace std;


enum  Visibilidad { noVisitado, noEntrado,visitado };

class Casilla
{
private:
	//int look;
	vector<bool> direcciones;
	bool esSalida;
	Visibilidad visib;
	vector<Enemy*> enemigos;
	//vector<Chests*> cofres;

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
	void addEnemy(Enemy* e) {
		enemigos.push_back(e);
	}
	vector<Enemy*> getEnemy() { return enemigos; }
	void addChest()
	{

	}
	//vector<Chest*> getChest() { return cofres; }
};

