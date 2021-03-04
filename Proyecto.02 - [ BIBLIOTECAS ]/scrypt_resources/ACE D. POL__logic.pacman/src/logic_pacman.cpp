// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
//

#include "logic_game.h"
#include "logic_pacman.h"
#include "objectsMotor.h"
#include "windowAPP.h"

#pragma region METODOS_LOGIC_PACMAN

// :::::::::::::::::: Metodos relacionados con PACMAN ::::::::::::::::::::::

Pacman* logic_pacman::getPacman()
{
	return static_cast<Pacman*>(acedLogic().getPlayer());
}

void logic_pacman::collisionsPacman(const SDL_Rect& rect)
{
	list<SDL_Object*> stage = acedObjsMot().getStage();
	for (SDL_Object* o : stage) {
		Ghost* g = dynamic_cast<Ghost*>(o);
		if (g != nullptr) {
			SDL_Rect objRect = g->getDestRect();
			if (SDL_HasIntersection(&rect, &objRect) && (!g->getIsDie())) {
				
				if (static_cast<Pacman*>(acedLogic().getPlayer())->getEnergy() > 0) {
					acedLogic().addPoints(100); g->morir();
				}
				else {
					acedLogic().getPlayer()->morir(); resetGhost(); // motor->resetGhost
					if (acedLogic().isAlive()) {
						//setLoseLife(true); // letrero
					}
				}
			}
		}
	}
}

// :::::::::::::::::: Uso de Ficheros: GUARDAR & CARGAR ::::::::::::::::::::::

void logic_pacman::load(uint lvlSelect)
{
	acedLogic().setLvl(lvlSelect);
	// Prepara el fileMap del juego:
	uint rows = 0, cols = 0;

	// Abre el fichero del nivel:
	ifstream file;
	acedLogic().abrirNivel(file);

	// Construye el juego:
	file >> rows >> cols;
	// prepara el tamano celda de salida
	uint wCell_ = acedWinApp().getWin_w() / cols;
	uint hCell_ = acedWinApp().getWin_h() / (rows + INFOBAR);
	acedLogic().setCellTam(wCell_, hCell_);

	// Prepara el mapa:
	map_pacman* map = new map_pacman(Point2D(0 * wCell_, double(INFOBAR) * double(hCell_)), rows, cols, wCell_ * cols, hCell_ * rows);
	acedLogic().setMap(map);
	acedObjsMot().storeObject(map);
	
	// Prepara InfoBar:
	InfoBar* bar = new InfoBar(Point2D(wCell_, 0 * hCell_), wCell_, hCell_, cols);
	acedLogic().setInfoBar(bar);
	acedObjsMot().storeObject(bar);

	// Prepara el mapa del juego:
	int i = 0;
	for (uint r = 0; r < rows; ++r) {
		for (uint c = 0; c < cols; ++c) {
			int d;
			file >> d;
			if (d > -1 && d < 4) {
				if (d == 2) { ++foodLeft; };
				acedLogic().setCell(r, c, MapCell(d));
			}
			else if (d >= 4 && d < 10) {
				acedLogic().setCell(r, c, MapCell(0)); // vacio
				if (d == 9) // Prepara al jugador -> Pacman
				{	// PONER BIEN LOS PARAMETROS
					Pacman* player = new Pacman(Point2D(double(c) * double(wCell_) + map->getPosAct().getX(), double(r) * double(hCell_) + map->getPosAct().getY()), 0, 10, acedWinApp().getTexture(CharactersTxt), wCell_, hCell_);
					acedLogic().setPlayer(player);
					acedObjsMot().storeObject(player);
					acedObjsMot().storeHandler(player);
				}
				else if (d == 4) {
					SmartGhost* smartG = new SmartGhost(Point2D(double(c) * double(wCell_) + map->getPosAct().getX(), double(r) * double(hCell_) + map->getPosAct().getY()), 0, 0, acedWinApp().getTexture(CharactersTxt), wCell_, hCell_, -1, false);
					acedObjsMot().storeObject(smartG);
				}
				else { // Prepara los ghosts
					Ghost* g = new Ghost(Point2D(double(c) * double(wCell_) + map->getPosAct().getX(), double(r) * double(hCell_) + map->getPosAct().getY()), 0, 0, acedWinApp().getTexture(CharactersTxt), wCell_, hCell_, i);
					acedObjsMot().storeObject(g);
					++i;
				}
			}
		}
	}
	file.close(); // cierra el flujo
}

void const logic_pacman::saveToFile(ofstream& file)
{
	file << 'F' << ' ' << acedLogic().getLvl() << ' ' << acedLogic().getLives() << ' ' << acedLogic().getPoints() << ' ' << acedLogic().getLvlPoints() << ' ' << foodLeft << endl;

	list<SDL_Object*> stage = acedObjsMot().getStage();
	for (SDL_Object* o : stage) {
		SmartGhost* s = dynamic_cast<SmartGhost*>(o);
		if (s != nullptr) {
			file << 'S' << ' ';
			s->saveToFile(file);
		}
		else {
			Ghost* g = dynamic_cast<Ghost*>(o);
			if (g != nullptr) {
				file << 'G' << ' ';
				g->saveToFile(file);
			}
			else {
				Pacman* p = dynamic_cast<Pacman*>(o);
				if (p != nullptr) {
					file << 'P' << ' ';
					p->saveToFile(file);
				}
				else {
					GameMap* m = dynamic_cast<GameMap*>(o);
					if (m != nullptr) {
						file << 'M' << ' ';
						m->saveToFile(file);
					}
					else {
						InfoBar* b = dynamic_cast<InfoBar*>(o);
						if (b != nullptr) {
							file << 'I' << ' ';
							b->saveToFile(file);
						}
					}
				}
			}
		}
		file << endl;
	}
}

logic_pacman::logic_pacman(ifstream& file)
{
	Pacman* player = nullptr;
	map_pacman* map = nullptr;
	uint currentTime = 0;
	setLoseLife(false);
	while (!file.fail()) {
		char c = ' ';
		file >> c;
		switch (c) {
		case 'F':
			uint lvl, points, lvlPoints;
			int lives;
			file >> lvl >> lives >> points >> lvlPoints >> foodLeft;
			acedLogic().setInfo(lvl, lives, points, lvlPoints);
			break;
		case 'M':
			map = new map_pacman(file);
			acedLogic().setMap(map);
			acedObjsMot().storeObject(map);
			break;
		case 'P':
			player = new Pacman(file, acedTxtMot().getTexture(CharactersTxt));
			acedLogic().setPlayer(player);
			acedObjsMot().storeObject(player);
			acedObjsMot().storeHandler(player);
			break;
		case 'I':
			file >> currentTime;
			break;
		case 'S':
		case 'G':
			if (c == 'S') {
				SmartGhost* s = new SmartGhost(file, acedTxtMot().getTexture(CharactersTxt));
				acedObjsMot().storeObject(s);
			}
			if (c == 'G') {
				Ghost* g = new Ghost(file, acedTxtMot().getTexture(CharactersTxt));
				acedObjsMot().storeObject(g);
			}
			break;
		}
	}
	uint wCell_ = WIN_WIDTH / acedLogic().getCols();
	uint hCell_ = WIN_HEIGHT / (acedLogic().getRows() + INFOBAR);
	acedLogic().setCellTam(wCell_, hCell_);

	// Prepara InfoBar:
	InfoBar* bar = new InfoBar(currentTime, Point2D(wCell_, 0 * hCell_), wCell_, hCell_, acedLogic().getCols());
	acedLogic().setInfoBar(bar);
	acedObjsMot().storeObject(bar);
	// pause
}

// :::::::::::::::::: Metodos relacionados con GHOSTS ::::::::::::::::::::::

void logic_pacman::resetGhost()
{
	list<SDL_Object*> stage = acedObjsMot().getStage();
	for (SDL_Object* o : stage) {
		Ghost* g = dynamic_cast<Ghost*>(o);
		if (g != nullptr)
			if (!g->getIsDie())
				g->morir();
	};
}

double logic_pacman::calculateDistanceFromPacman(const Point2D pos)
{
	Point2D posPacman = static_cast<Pacman*>(acedLogic().getPlayer())->getPosAct();
	return acedLogic().calculateDistanceFrom(posPacman, pos);
}

bool logic_pacman::SmartGhostCollision(SmartGhost* smartG)
{
	list<SDL_Object*> stage = acedObjsMot().getStage();
	SDL_Rect smartGRect = smartG->getDestRect();
	for (SDL_Object* o : stage) {
		Ghost* g = dynamic_cast<Ghost*>(o);
		if (g != nullptr) {
			SDL_Rect ghostRect = g->getDestRect();
			// si no es un 'deadBody' (SmartGhost)
			bool deadBodyGhost = false;
			if (g->getNumGhost() == -1) { // es un smartGhost
				deadBodyGhost = static_cast<SmartGhost*>(g)->getDeadBody();
			}
			// Y ademas hay colision -> se reproduce
			if (!deadBodyGhost && !SDL_RectEquals(&smartGRect, &ghostRect) && SDL_HasIntersection(&smartGRect, &ghostRect)) {
				// posicion inicial heredada de forma aleatoria
				int rnd = acedLogic().randomNumber(2);
				Point2D pIni;
				if (rnd == 0)
					pIni = smartG->getPosAct();
				else
					pIni = g->getPosAct();
				// determina el hijo que van a tener ^^
				if (g->getNumGhost() == -1) { // es un smartGhost
					SmartGhost* newSmartG = new SmartGhost(pIni, 0, 0, acedTxtMot().getTexture(CharactersTxt), acedLogic().getCell_w(), acedLogic().getCell_h(), -1, false);
					acedObjsMot().storeObject(newSmartG);
				}
				else { // es 'normal'
					int numGhost = g->getNumGhost();
					Ghost* newGhost = new Ghost(pIni, 0, 0, acedTxtMot().getTexture(CharactersTxt), acedLogic().getCell_w(), acedLogic().getCell_h(), numGhost);
					acedObjsMot().storeObject(newGhost);
				}
				return true;
			}
		}
	}
	return false;
}














// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
#pragma endregion