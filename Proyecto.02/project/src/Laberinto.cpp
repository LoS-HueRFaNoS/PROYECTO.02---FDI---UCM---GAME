#include "Laberinto.h"
#include <string>
#include <iostream>
#include <fstream>


using namespace std;

Laberinto::Laberinto(EntityManager* entityManager_,int h_, int w_) :Component(ecs::Laberinto),entityManager(entityManager_),h(h_),w(w_)
{

}
Laberinto::Laberinto(EntityManager* entityManager_) : Component(ecs::Laberinto),entityManager(entityManager_), h(), w()
{

}


Laberinto::~Laberinto()
{

}



void Laberinto::initFromFile()
{
	ifstream input; // Flujo de entrada
	input.open("./Laberinto1.txt"); // Se abre el archivo
	if (!input.is_open()) // Da error si no se puede abrir el archivo
	{
		throw std::string("Fichero no encontrado");
	}
	else
	{
		input >> h >> w; // Primero se leen el número de filas y de columnas
		laberinto.resize(h);
		for (int i = 0; i < h; ++i)
			laberinto[i].resize(w);
		bool norte, este, sur, oeste; // Variable donde se guarda el siguiente dato
		for (int i = 0; i < h; ++i) // Por cada fila  = Y
		{
			for (int j = 0; j < w; ++j) // Por cada columna  = X
			{
				input >> norte >> este >> sur >> oeste; // Se recoge el siguiente dato

				auto a = new Casilla(i, j, norte, este, sur, oeste);
				laberinto[j][i] = a;
			}
		}
		input.close();
	}
}

Vector2D Laberinto::getEntrada()
{
	return Vector2D(0, 0);
}

void Laberinto::createRandomMaze(int s)
{
	laberinto = vector<vector<Casilla*>>(s, vector<Casilla*>(s, new Casilla()));
}
Casilla* Laberinto::getCasillaInfo(int x, int y)
{
	return laberinto[x][y];

}

void Laberinto::draw()
{
	//for (int i = 0; i < h; ++i) // Por cada fila  = Y
	//{
	//	for (int j = 0; j < w; ++j) // Por cada columna  = X
	//	{
	//		laberinto[j][i].
	//	}
	//}
}