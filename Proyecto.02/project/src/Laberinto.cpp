#include "Laberinto.h"
#include <string>
#include <iostream>
#include <fstream>


using namespace std;



Laberinto::Laberinto(EntityManager* entityManager_,int h_, int w_) :Component(ecs::Laberinto),entityManager(entityManager_),h(h_),w(w_)
{
	salida = Vector2D(w, 0);

}
Laberinto::Laberinto(EntityManager* entityManager_) : Component(ecs::Laberinto),entityManager(entityManager_), h(5), w(5)
{
	salida = Vector2D(w,0);

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

				auto a = new Casilla( norte, este, sur, oeste);
				laberinto[j][i] = a;
			}
		}
		input.close();
	}
}

Vector2D Laberinto::getSalida()
{
	return salida;
}

void Laberinto::createRandomMaze(Vector2D entrada)
{
	int x, y;
	
	x = game_->getRandGen()->nextInt( (w/2), w );
	y = game_->getRandGen()->nextInt( (h/2), h);
	salida = Vector2D(x,y);
	laberinto.resize(h);
	for (int i = 0; i < h; ++i)
		laberinto[i].resize(w);
	maze1D.resize(w * h);
	x = entrada.getX();
	y = entrada.getY();

	maze1D[y * w + x] = true;
	m_stack.push_back(Vector2D(x, y));
	laberinto[x][y] = new Casilla();
	cellsCreated = 1;

	// Create a set of unvisted neighbours
	vector<Look> neighbours;
	while (cellsCreated < w*h)
	{
		x = m_stack.back().getX();
		y = m_stack.back().getY();
		// North neighbour
		if (y> 0 && !maze1D[(y-1)*w+x])
			neighbours.push_back(Norte);
		// East neighbour
		if (x < w -1 && !maze1D[y * w + (x+1)])
			neighbours.push_back(Este);
		// South neighbour
		if (y< h-1 && !maze1D[(y+1) * w + x])
			neighbours.push_back(Sur);
		// West neighbour
		if (x > 0 && !maze1D[y * w + (x-1)])
			neighbours.push_back(Oeste);

		// Are there any neighbours available?
		if (!neighbours.empty())
		{
			// Choose one available neighbour at random
			int next_cell_dir = neighbours[rand() % neighbours.size()];

			// Create a path between the neighbour and the current cell
			switch (next_cell_dir)
			{
			case 0: // North
				laberinto[x][y]->setDirs(Norte);
				y--;
				laberinto[x][y] = new Casilla();
				laberinto[x][y]->setDirs(Sur);

				
				break;

			case 1: // East
				laberinto[x][y]->setDirs(Este);
				x++;				
				laberinto[x][y] = new Casilla();
				laberinto[x][y]->setDirs(Oeste);

				break;

			case 2: // South
				laberinto[x][y]->setDirs(Sur);
				y++;
				laberinto[x][y] = new Casilla();
				laberinto[x][y]->setDirs(Norte);
				break;

			case 3: // West
				laberinto[x][y]->setDirs(Oeste);
				x--;
				laberinto[x][y] = new Casilla();
				laberinto[x][y]->setDirs(Este);
				break;

			}
			maze1D[y * w + x] = true;
			m_stack.push_back(Vector2D(x, y));
			cellsCreated++;

			if (x == salida.getX() && y == salida.getY())
			{
				shortestWay = new vector<Vector2D>( m_stack);
				laberinto[x][y]->setSalida();
			}
		}
		else
		{
			// No available neighbours so backtrack!
			m_stack.pop_back();
		}
		neighbours.clear();
	} 
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