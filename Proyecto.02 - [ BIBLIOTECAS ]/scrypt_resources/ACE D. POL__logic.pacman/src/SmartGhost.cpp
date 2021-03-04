// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
//

#include "SmartGhost.h"
#include "logic_game.h"
#include "logic_pacman.h"

#pragma region METODOS_SMART_GHOST

// :::::::::::::::::: MOTOR DEL PERSONAJE ::::::::::::::::::::::

void SmartGhost::update() {
	Point2D newPos = Point2D();
	SDL_Rect rect = getDestRect();

	// ciclo de reloj
	++currentTime;

	// movimiento
	if (!deadBody) {
		distance = acedLogPacman().calculateDistanceFromPacman(pos);
		// update de seguimiento:
		if (adulto && distance <= MIN_DIST) {
			checkDirs(rect);
			if (acedLogic().tryMove(rect, dir, VEL, newPos)) {
				pos = newPos;
			}
			Ghost::animation(direction(act(dir)));
		}
		else { Ghost::update(); }

		// reproducción
		if (adulto && currentTime >= cuarentenaTime) {
			if (acedLogPacman().SmartGhostCollision(this))
				cuarentenaTime = currentTime + CUARENTENATIME;
		}
	}

	// etapa de la vida
	if (currentTime >= TIMETOGROW		&& !adulto)		becomeAdult();
	if (currentTime >= TIMETODIE		&& !deadBody)	dieAndStay();
	if (currentTime >= TIMETOPERMADIE	&&  deadBody)	acedLogic().eraseObject(itList);
}

void SmartGhost::render()
{
	if (!adulto) {
		//nuevo render pequeno 
		SDL_Rect rect = getDestRect();
		rect.x = rect.x + (width / 4);
		rect.y = rect.y + (height / 4);
		rect.h = rect.h / 2;
		rect.w = rect.w / 2;
		text->renderFrame(rect, rowF, colF);
	}
	else {
		//casting usar el render de gameCharacter
		GameCharacter::render();
	}
}

void SmartGhost::checkDirs(SDL_Rect rect) { // mejorable
	dirs.clear();
	double minDistance, distance;
	int id;
	minDistance = 1000;
	id = -1;
	for (int i = 0; i < NUM_DIRS; i++)	{
		Point2D p = Point2D();
		Vector2D d = DIRS[i];
		if (acedLogic().tryMove(rect, d, VEL, p)) {
			distance = acedLogPacman().calculateDistanceFromPacman(p);
			if (distance <= minDistance) {
				//dirs.push_back(i);
				minDistance = distance;
				id = i;
			}
		}
	}
	dir.dir(direction(id)); 
}

void SmartGhost::morir()
{
	Ghost::morir();
}

void SmartGhost::becomeAdult()
{
	adulto = true;
}

void SmartGhost::dieAndStay()
{
	die = true;
	deadBody = true;
	colF = 12;
	rowF = 2;	//transparentes
}

// :::::::::::::::::: Uso de Ficheros: GUARDAR & CARGAR ::::::::::::::::::::::

const void SmartGhost::saveToFile(ofstream& file)
{
	Ghost::saveToFile(file);
	file << currentTime << ' ' << adulto << ' ' << deadBody << ' ';
}

SmartGhost::SmartGhost(ifstream& file, Texture* t) : Ghost(file, t), cuarentenaTime(0)
{
	uint timelife, ad, db;
	file >> timelife >> ad >> db;

	if (timelife < 0) throw FileFormatError("el valor 'timelife' no es un entero positivo");
	else currentTime = timelife;

	if (ad == 1) adulto = true;
	else if (ad == 0) adulto = false;
	else throw FileFormatError("el valor 'adulto' de SmartGhost no es tipo bool");
	if (db == 1) deadBody = true;
	else if (db == 0) deadBody = false;
	else throw FileFormatError("el valor 'deadBody' de SmartGhost no es tipo bool");

	distance = double(MIN_DIST) + double(50);
}

















// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
#pragma endregion