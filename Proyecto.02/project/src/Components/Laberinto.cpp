#include "Laberinto.h"
#include "../Managers/TheElementalMaze.h"
#include <string>
#include <iostream>
#include <fstream>
#include "../Templates/RPGLogic.h"
#include "../GameObjects/Character.h"

using namespace std;



Laberinto::Laberinto(int h_, int w_) :Component(ecs::Laberinto), h(h_), w(w_)
{
	salida = Vector2D(w, 0);
	drawMiniMap = true;
}
Laberinto::Laberinto() : Component(ecs::Laberinto), h(5), w(5)
{
	salida = Vector2D(w, 0);
	drawMiniMap = true;
}


Laberinto::~Laberinto()
{
	for (vector<Casilla*> v : laberinto) {
		for (Casilla* c : v) {
			delete c;
			c = nullptr;
		}
	}
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
		input >> h >> w; // Primero se leen el n�mero de filas y de columnas
		laberinto.resize(h);
		for (int i = 0; i < h; ++i)
			laberinto[i].resize(w);
		bool norte, este, sur, oeste; // Variable donde se guarda el siguiente dato
		for (int i = 0; i < h; ++i) // Por cada fila  = Y
		{
			for (int j = 0; j < w; ++j) // Por cada columna  = X
			{
				input >> norte >> este >> sur >> oeste; // Se recoge el siguiente dato

				auto a = new Casilla(game_, norte, este, sur, oeste);
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

	if (TheElementalMaze::instance()->getLevel() == -1)
	{
		w = 4;
		h = 4;
		x = 3;
		y = 3;
	}

	else
	{
		w = 10;
		h = 10;
		x = game_->getRandGen()->nextInt((w / 2), w);
		y = game_->getRandGen()->nextInt((h / 2), h);
	}


	salida = Vector2D(x, y);
	//salida = Vector2D(0, 1);
	laberinto.resize(h);
	for (int i = 0; i < h; ++i)
		laberinto[i].resize(w);
	maze1D.resize(w * h);
	x = int(entrada.getX());
	y = int(entrada.getY());

	maze1D[y * w + x] = true;
	m_stack.push_back(Vector2D(x, y));
	laberinto[x][y] = new Casilla(game_);
	cellsCreated = 1;

	// Create a set of unvisted neighbours
	vector<Look> neighbours;
	while (cellsCreated < w * h)
	{
		x = int(m_stack.back().getX());
		y = int(m_stack.back().getY());
		// North neighbour
		if (y > 0 && !maze1D[(int)((y - 1) * w + x)])
			neighbours.push_back(Norte);
		// East neighbour
		if (x < w - 1 && !maze1D[(int)(y * w + (x + 1))])
			neighbours.push_back(Este);
		// South neighbour
		if (y < h - 1 && !maze1D[(int)((y + 1) * w + x)])
			neighbours.push_back(Sur);
		// West neighbour
		if (x > 0 && !maze1D[(int)(y * w + (x - 1))])
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
				laberinto[x][y] = new Casilla(game_);
				laberinto[x][y]->setDirs(Sur);
				break;

			case 1: // East
				laberinto[x][y]->setDirs(Este);
				x++;
				laberinto[x][y] = new Casilla(game_);
				laberinto[x][y]->setDirs(Oeste);
				break;

			case 2: // South
				laberinto[x][y]->setDirs(Sur);
				y++;
				laberinto[x][y] = new Casilla(game_);
				laberinto[x][y]->setDirs(Norte);
				break;

			case 3: // West
				laberinto[x][y]->setDirs(Oeste);
				x--;
				laberinto[x][y] = new Casilla(game_);
				laberinto[x][y]->setDirs(Este);
				break;
			}
			maze1D[y * w + x] = true;
			m_stack.push_back(Vector2D(x, y));
			cellsCreated++;

			if (x == salida.getX() && y == salida.getY())
			{
				shortestWay = vector<Vector2D>(m_stack);

				if (TheElementalMaze::instance()->getLevel() != -1)
				{
					int enemyType = 0;

					switch (TheElementalMaze::instance()->getLevel())
					{
					case 0:
						enemyType = int(enemyTemplate::DEATHKNIGHT);
						break;
					case 1:
						enemyType = int(enemyTemplate::DRACOLICH);
						break;
					case 2:
						enemyType = int(enemyTemplate::LICH);
						break;
					default:
						break;
					}

					generaObjeto(0, enemyType, laberinto[x][y], 1, 0);

				}

			}
			int itemType = game_->getRandGen()->nextInt(1, 3);
			int chestChance = game_->getRandGen()->nextInt(0, 7);
			if (chestChance == 0)
			{
				if (itemType == 1)
				{
					auto armor = game_->getRandGen()->nextInt(int(armorId::ACOLCHADA), int(armorId::_lastArmorId_));
					generaObjeto(itemType, armor, laberinto[x][y], 1, 0);
				}
				if (itemType == 2)
				{
					auto weapon = game_->getRandGen()->nextInt(int(weaponId::ALABARDA), int(weaponId::_lastWeaponId_));
					generaObjeto(itemType, weapon, laberinto[x][y], 1, 0);
				}
			}
			if (TheElementalMaze::instance()->getLevel() != -1)
			{
				int hayEnemy = game_->getRandGen()->nextInt(0, 10);

				if (hayEnemy < 3)
				{
					int enemyType = 0;
					int random = 0;

					switch (TheElementalMaze::instance()->getLevel())
					{
					case 0:
						random = throwDice(1, 3);
						for (int i = 0; i < random; i++)
						{
							enemyType = game_->getRandGen()->nextInt(0, int(enemyTemplate::SKELETON));
							generaObjeto(0, enemyType, laberinto[x][y], 1, 0);
						}
						break;
					case 1:
						random = throwDice(1, 3);
						for (int i = 0; i < random; i++)
						{
							enemyType = game_->getRandGen()->nextInt(0, int(enemyTemplate::HELLHOUND));
							generaObjeto(0, enemyType, laberinto[x][y], 1, 0);
						}
						break;
					case 2:
						random = throwDice(1, 3);
						for (int i = 0; i < random; i++)
						{
							enemyType = game_->getRandGen()->nextInt(0, int(enemyTemplate::DEATHKNIGHT));
							generaObjeto(0, enemyType, laberinto[x][y], 1, 0);
						}
						break;
					default:
						break;
					}
				}
			}
		}

		else
		{
			// No available neighbours so backtrack!
			m_stack.pop_back();
		}
		neighbours.clear();
	}
	laberinto[salida.getX()][salida.getY()]->setSalida();
	if (TheElementalMaze::instance()->getLevel() == -1)
	{
		generaObjeto(0, int(enemyTemplate::GOBLIN), laberinto[3][2], 1, 0);
		generaObjeto(0, int(enemyTemplate::GOBLIN), laberinto[2][3], 1, 0);
	}
}


Casilla* Laberinto::getCasillaInfo(int x, int y)
{
	return laberinto[x][y];
}

void Laberinto::draw()
{
	if (!drawMiniMap) return;
	double _x = game_->setHorizontalScale(1510);
	double _y = game_->setVerticalScale(70);
	//double _w = game_->setHorizontalScale(34); // 28
	//double _h = game_->setVerticalScale(19); // 20
	double _w = game_->setHorizontalScale(340 / w); //  / 10
	double _h = game_->setVerticalScale(190 / h); //   / 10
	for (int i = 0; i < h; ++i) // Por cada fila  = Y
	{
		for (int j = 0; j < w; ++j) // Por cada columna  = X
		{
			laberinto[j][i]->casillaRender(int(_x) + j * int(_w), int(_y) + i * int(_h), _w, _h);
		}
	}
}

void Laberinto::generaObjeto(int object, int type, Casilla* casilla, int maxObject, int cant)
{
	if (object == 0) {

		casilla->addEnemy((static_cast<enemyTemplate>(type)));
		//cout << "generado " << (cant+1) << " enemigo"<<endl;
	}
	else if (object == 1 && !casilla->hasChest())
	{
		casilla->addChest(Chest(ARMOR,type, game_->getRandGen()->nextInt(100,300),game_));
	}
	else if (object == 2 && !casilla->hasChest())
	{
		casilla->addChest(Chest(WEAPON,type, game_->getRandGen()->nextInt(100,300),game_));
	}
	cant++;

	/*int generaOtro = game_->getRandGen()->nextInt(0, 10);
	if (cant < maxObject && generaOtro)
	{
		if (object == 0)
		{
			type = game_->getRandGen()->nextInt(0, int(enemyTemplate::_lastEnemyTemplateId_));
		}
		generaObjeto(object, type, casilla, maxObject, cant);
	}*/



}
