#include "Laberinto.h"
#include <string>
#include <iostream>
#include <fstream>
#include "RPGLogic.h"

using namespace std;



Laberinto::Laberinto(int h_, int w_) :Component(ecs::Laberinto), h(h_), w(w_)
{
	salida = Vector2D(w, 0);

}
Laberinto::Laberinto() : Component(ecs::Laberinto), h(5), w(5)
{
	salida = Vector2D(w, 0);

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

				auto a = new Casilla(norte, este, sur, oeste);
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

	x = game_->getRandGen()->nextInt((w / 2), w);
	y = game_->getRandGen()->nextInt((h / 2), h);
	salida = Vector2D(x, y);
	laberinto.resize(h);
	for (int i = 0; i < h; ++i)
		laberinto[i].resize(w);
	maze1D.resize(w * h);
	x = int(entrada.getX());
	y = int(entrada.getY());

	maze1D[y * w + x] = true;
	m_stack.push_back(Vector2D(x, y));
	laberinto[x][y] = new Casilla();
	cellsCreated = 1;

	// Create a set of unvisted neighbours
	vector<Look> neighbours;
	while (cellsCreated < w * h)
	{
		x = m_stack.back().getX();
		y = m_stack.back().getY();
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
				shortestWay = new vector<Vector2D>(m_stack);
				laberinto[x][y]->setSalida();

				cout << "shotwast copiado " << endl;
				for (int j = 3; j < shortestWay->size(); j++)
				{
					int posX, posY;
					int enemyType = game_->getRandGen()->nextInt(0, enemyTemplate::_LastEnemyTemplateId_ *3);
					if (enemyType < enemyTemplate::_LastEnemyTemplateId_)
					{
						posX = (*shortestWay)[j].getX();
						posY = (*shortestWay)[j].getY();
						cout << "En la casilla [" << x << " , " << y << " ]" << endl;
						generaObjeto(0, enemyType, laberinto[x][y], 3, 0);
					}
				}
			}

			int enemyType = game_->getRandGen()->nextInt(0, enemyTemplate::_LastEnemyTemplateId_*3 );
			if (enemyType < enemyTemplate::_LastEnemyTemplateId_)
			{
				cout << "En la casilla [" << x << " , " << y << " ]" << endl;
				generaObjeto(0, enemyType, laberinto[x][y], 4,0);
				
			}

			int totalItem = weaponId::_LastWeaponId_ + armorId::_LastArmorId_ + 4;
			int chestType = game_->getRandGen()->nextInt(0, totalItem*5);
			if (chestType <totalItem )
			{
				cout << "En la casilla [" << x << " , " << y << " ]" << " hay un cofre con :" << endl;
				generaObjeto(1, chestType, laberinto[x][y],2,0);
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

void Laberinto::generaObjeto(int object, int type, Casilla* casilla, int maxObject, int cant)
{
	casilla->addEnemy((static_cast<enemyTemplate>(type)));
	cout << "generado " << (cant + 1) << " enemigo" << endl;


	if (object == 0) {

		casilla->addEnemy((static_cast<enemyTemplate>(type)));
		cout << "generado " << (cant+1) << " enemigo"<<endl;
	}
	else if (object ==1)
	{

		
		//Generacion de tipo de cofre
		if (type < weaponId::_LastWeaponId_)
		{
			casilla->addChest(static_cast<ItemType>(0), type);
			cout << "weapon de " << static_cast<weaponId>(type) <<endl;
		}
		else if (type < weaponId::_LastWeaponId_ + armorId::_LastArmorId_)
		{
			type -= weaponId::_LastWeaponId_;
			cout << "armor de " << static_cast<armorId>(type) <<endl;
			casilla->addChest(static_cast<ItemType>(1),type);
		}
		else if ((type < weaponId::_LastWeaponId_ + armorId::_LastArmorId_ + 3))
		{
			type -= weaponId::_LastWeaponId_;
			type -= armorId::_LastArmorId_;
			cout << "potion de ";
			switch (type)
			{
			case 0:
				cout <<"Health" <<"Potion" << endl;
				break;
			case 1:
				cout << "Mana" << "Potion" << endl;
				break;
			case 2:
				cout << "Revive" << "Potion" << endl;
				break;
			default:
				break;
			}
			
			casilla->addChest(static_cast<ItemType>(2), type );

			
		}
		else
		{
			int dinero = game_->getRandGen()->nextInt(5, 21); // 5 a 21 runas
			cout << dinero << " Runas" <<endl;
			casilla->addChest(static_cast<ItemType>(3), dinero);
		}

		
		
	}
	cant++;
	if (object ==0)
		type = game_->getRandGen()->nextInt(0, enemyTemplate::_LastEnemyTemplateId_ * 2);
	else
	{
		
		
		int totalItem = weaponId::_LastWeaponId_ + armorId::_LastArmorId_ + 4;
		type = game_->getRandGen()->nextInt(0, totalItem * 5);
	}

	if (cant <= maxObject && type < enemyTemplate::_LastEnemyTemplateId_)
	{
		generaObjeto(object, type, casilla, maxObject, cant);
	}
}
