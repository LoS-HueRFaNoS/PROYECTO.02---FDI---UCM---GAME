#pragma once
#include "Casilla.h"
#include <string>
#include <vector>
#include "Component.h"



class Laberinto : public Component
{
private:
	int h, w;
	EntityManager* entityManager;
	vector<vector<Casilla*>> laberinto;
public:
	Laberinto(EntityManager* entityManager_,int h,int w);
	Laberinto(EntityManager* entityManager_);
	virtual ~Laberinto();
	void initFromFile();
	int mazeWidth() { return w; };
	int mazeHeigh() { return h; };
	Vector2D getEntrada();
	void createRandomMaze(int s);
	Casilla* getCasillaInfo(int x, int y);
	virtual void draw();
};