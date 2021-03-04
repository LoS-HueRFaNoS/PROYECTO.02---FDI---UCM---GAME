// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
//

#include "Ghost.h"
#include "logic_game.h"
#include "logic_pacman.h"

#include <iostream>
#include <fstream>

#include <stdlib.h>
#include <time.h>

#pragma region METODOS_GHOST

// :::::::::::::::::: MOTOR DEL PERSONAJE ::::::::::::::::::::::

void Ghost::update()
{
	Point2D newPos = Point2D();
	SDL_Rect rect = getDestRect();

	if (checkMoves(rect)) {
		dir.dir(newRndDir());
	}
	if (acedLogic().tryMove(rect, dir, VEL, newPos)) {
		pos = newPos;
	}

	animation(direction(act(dir)));
	//showGhost();
}

bool Ghost::checkMoves(SDL_Rect rect)
{
	bool change = false;	// determina si hay nueva posible direcci�n
	vector<int> aux = dirs;
	dirs.clear();
	for (int i = 0; i < NUM_DIRS; i++)
	{
		Point2D p = Point2D();
		Vector2D d = DIRS[i];
		if (i != dirInv(dir) && acedLogic().tryMove(rect, d, VEL, p))
		{
			dirs.push_back(i);
		}
	}
	if (aux != dirs) { change = true; }
	return change;
}

direction Ghost::newRndDir()
{
	int newDir = -1;
	// coge una de ellas al azar
	int s = int(dirs.size());
	int rnd;
	if (s != 0)
	{
		rnd = 0 + rand() % (s - 0);
		newDir = dirs[rnd];
	}
	return direction(newDir);
}

void Ghost::morir()
{
	animation(direction(act(dir)));
	resetPos();
}

// :::::::::::::::::: MOTOR DE ANIMACI�N ::::::::::::::::::::::

void Ghost::animation(direction dir)
{
	Pacman* pacman = acedLogPacman().getPacman();
	int energy = pacman->getEnergy();

	// animacion del color
	if (energy > 0) {
		if (energy <= ENERGY / 6) { rowF = 1; colF = 12; }
		else { rowF = 0; colF = 12; }
	}
	else if (energy == 0) { setGhostColors(); }

	// animacion de los pies
	colF = contrario(colF);

	// animacion de los ojos
	if (!(energy > 0))
	{
		switch (dir)
		{
		case N: rowF = 3;
			break;
		case S: rowF = 1;
			break;
		case E: rowF = 0;
			break;
		case O: rowF = 2;
			break;
		default:
			break;
		}
	}
}

void Ghost::setGhostColors()
{
	switch (numGhost)
	{
	case -1: colF = 8;
		break;
	case 0: colF = 0;
		break;
	case 1: colF = 4;
		break;
	case 2: colF = 6;
		break;
	case 3: colF = 2;
		break;
	default:
		break;
	}
}

// :::::::::::::::::: Uso de Ficheros: GUARDAR & CARGAR ::::::::::::::::::::::

const void Ghost::saveToFile(ofstream& file)
{
	GameCharacter::saveToFile(file);
	file << numGhost << ' ' << die << ' ';
}

Ghost::Ghost(ifstream& file, Texture* t) : GameCharacter(file, t)
{
	uint x;
	file >> numGhost >> x;
	if (numGhost < -1 || numGhost > 3) throw FileFormatError("el valor 'numGhost' no esta bien definido");

	if (x == 1) die = true;
	else if (x == 0) die = false;
	else throw FileFormatError("el valor 'die' de Ghost no es tipo bool");
}

// :::::::::::::::::: Metodos de depuracion de codigo ::::::::::::::::::::::

void Ghost::showMoves()
{
	cout << "{ ";
	for (uint i = 0; i < dirs.size(); ++i)
	{
		char d = '?';
		switch (dirs[i])
		{
		case 0:
			d = 'N';
			break;
		case 1:
			d = 'S';
			break;
		case 2:
			d = 'E';
			break;
		case 3:
			d = 'O';
			break;
		default:
			break;
		}
		if (i == dirs.size() - 1)
			cout << d;
		else
			cout << d << ", ";
	}
	cout << " }" << endl;
}

void Ghost::showName()
{
	switch (numGhost)
	{
	case -1: 
		cout << "SmartGhost";
		break;
	case 0:
		cout << "Shadow";
		break;
	case 1:
		cout << "Speedy";
		break;
	case 2:
		cout << "Bashful";
		break;
	case 3:
		cout << "Pokey";
		break;
	default:
		break;
	}
}

void Ghost::showGhost()
{
	showName();
	showMoves();
}

















// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
#pragma endregion