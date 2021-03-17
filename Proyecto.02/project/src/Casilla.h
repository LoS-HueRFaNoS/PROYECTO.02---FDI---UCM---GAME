#pragma once
#include <vector>
#include "Entity.h"
using namespace std;




class Casilla
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

	vector<bool> checkCell();
};

