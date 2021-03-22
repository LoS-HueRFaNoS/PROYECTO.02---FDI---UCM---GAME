#pragma once
#include "Casilla.h"
#include <string>
#include <vector>
#include "Component.h"
#include "Vector2D.h"



class Laberinto : public Component
{
private:
	int h, w; //Tamaño del laberinto 
	EntityManager* entityManager;
	vector<vector<Casilla*>> laberinto;
	Vector2D salida;

	vector<Vector2D>* shortestWay =nullptr;
	vector<bool> maze1D;
	vector<Vector2D> m_stack;	// (x, y) coordinate pairs
	int cellsCreated = 0;
	
public:
	Laberinto(EntityManager* entityManager_,int h,int w);
	Laberinto(EntityManager* entityManager_);
	virtual ~Laberinto();
	void initFromFile();
	int mazeWidth() { return w; };
	int mazeHeigh() { return h; };
	Vector2D getSalida();
	void createRandomMaze(Vector2D entrada);
	Casilla* getCasillaInfo(int x, int y);
	vector<Vector2D>* getShortWay() { return shortestWay; }
	virtual void draw();
};