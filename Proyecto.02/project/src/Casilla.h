#pragma once
#include <vector>
#include "Entity.h"
using namespace std;

enum MapCell { Norte, Este, Sur, Oeste };


class Casilla //: public Entity
{
private:
	int x, y;
	vector<bool> direcciones;
public:
	Casilla();
	Casilla(int x_,int y_, bool _N, bool _E, bool _S, bool _O);
	~Casilla();

	vector<bool>* checkCell();
};

