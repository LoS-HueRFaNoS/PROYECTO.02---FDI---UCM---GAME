#pragma once
#include "Casilla.h"
#include <string>
#include <vector>
#include "Component.h"



class Laberinto : public Component
{
private:
	int h, w;
	vector<vector<Casilla*>> laberinto;
public:
	Laberinto(int h,int w);
	Laberinto();
	virtual ~Laberinto();
	void initFromFile();
	void createRandomMaze(int s);
};