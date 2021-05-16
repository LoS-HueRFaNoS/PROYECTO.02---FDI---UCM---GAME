#pragma once
#include <string>
#include <vector>
#include "../ecs/Component.h"
#include "../Structures/Casilla.h"
#include "../Structures/Vector2D.h"

class Laberinto : public Component
{
private:
	int h, w; //Tamaño del laberinto 
	//EntityManager* entityManager;
	vector<vector<Casilla*>> laberinto;
	Vector2D salida;

	vector<Vector2D> shortestWay;
	vector<bool> maze1D;
	vector<Vector2D> m_stack;	// (x, y) coordinate pairs
	int cellsCreated = 0;
	
public:
	Laberinto(int h,int w);
	Laberinto();
	virtual ~Laberinto();
	void initFromFile();
	int mazeWidth() { return w; };
	int mazeHeigh() { return h; };
	Vector2D getSalida();
	void createRandomMaze(Vector2D entrada);
	Casilla* getCasillaInfo(int x, int y);
	
	virtual void draw();

	void generaObjeto(int object, int type, Casilla* casilla, int maxObject, int cant);
};