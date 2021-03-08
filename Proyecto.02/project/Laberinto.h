#pragma once
#include "Casilla.h"
#include <string>
#include <vector>
class Laberinto
{
private:
	int h, w;
	string numLaberinto;
	vector<vector<Casilla*>> laberinto;
public:
	Laberinto();
	~Laberinto();
};

