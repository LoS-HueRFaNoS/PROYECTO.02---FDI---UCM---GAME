#pragma once
#include "Casilla.h"
#include <string>
#include <vector>



class Laberinto
{
private:
	int h, w;
	vector<vector<Casilla*>> laberinto;
public:
	Laberinto();
	~Laberinto();
	void initFromFile();
	void createRandomMaze(int s);
};