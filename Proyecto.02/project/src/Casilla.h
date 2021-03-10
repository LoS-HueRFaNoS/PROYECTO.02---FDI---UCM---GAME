#pragma once
#include <vector>
#include "Entity.h"
using namespace std;

const static enum MapCell { Norte, Este, Sur, Oeste };


class Casilla //: public Entity
{
private:
	int x, y; //           <-   |   ->
	int look;
	int camino;
	bool vista;
	vector<bool> direcciones;
public:
	Casilla();
	Casilla(int x_,int y_, bool _N, bool _E, bool _S, bool _O);
	~Casilla();

	vector<bool>* checkCell();
};

