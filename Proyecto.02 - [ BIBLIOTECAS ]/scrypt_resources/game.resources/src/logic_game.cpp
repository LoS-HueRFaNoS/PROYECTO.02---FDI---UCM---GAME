// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
//

#include "logic_game.h"
#include "windowAPP.h"
#include "objectsMotor.h"

#pragma region METODOS_LOGIC_GAME

void logic_game::abrirNivel(ifstream& file)
{
	string filePath = "";
	if (lvl == 0) { filePath = fileMap + "test1.dat";  file.open(filePath); }
	else { filePath = fileMap + "level0" + to_string(lvl) + ".dat";  file.open(filePath); }
	if (!file.is_open()) throw FileNotFoundError(filePath);
}

// :::::::::::::::::: Metodos de movimiento por PIXELES ::::::::::::::::::::::

bool logic_game::tryMove(const SDL_Rect& rect, Vector2D dir, Vector2D vel, Point2D& newPos) // si se puede mover devuelve true (se trabaja en pixeles)
{
	SDL_Rect mapRect = map->getDestRect();
	// pos + dir (movimiento)
	newPos = Point2D(rect.x, rect.y) + Point2D(dir.getX() * vel.getX(), dir.getY() * vel.getY());
	// posibles salidas del mapa: 
	if (dir.getX() > 0 && (newPos.getX() + rect.w) >= double(mapRect.x) + double(mapRect.w)) newPos.setX(double(mapRect.x)); // derecha
	if (dir.getX() < 0 && (newPos.getX()) <= mapRect.x) newPos.setX(double(mapRect.x) + double(mapRect.w) - rect.w); // izquierda
	if (dir.getY() > 0 && (newPos.getY() + rect.h) >= double(mapRect.y) + double(mapRect.h)) newPos.setY(double(mapRect.y)); // abajo
	if (dir.getY() < 0 && (newPos.getY()) <= mapRect.y) newPos.setY(double(mapRect.y) + double(mapRect.h) - rect.h); // arriba
	// newPos es la nueva posicion aplicando dir
	SDL_Rect newRect = { int(newPos.getX()), int(newPos.getY()), rect.w, rect.h };
	return !(map->intersectsWall(newRect));
}

Point2D logic_game::mapCoordsToSDLPoint(Point2D coords)
{
	Point2D point;
	point.setY(coords.getY() * hCell_ + map->pos.getY());
	point.setX(coords.getX() * wCell_ + map->pos.getX());
	return point;
}

Point2D logic_game::SDLPointToMapCoords(Point2D point)
{
	Point2D coords;
	coords.setY(int((point.getY() - map->pos.getY()) / hCell_));
	coords.setX(int((point.getX() - map->pos.getX()) / wCell_));
	return coords;
}

// :::::::::::::::::: Metodos de movimiento por CELDAS ::::::::::::::::::::::

MapCell logic_game::showCell(const Point2D pos) const
{
	int r = int(pos.getY());
	int c = int(pos.getX());
	return map->cells[r][c];
}

MapCell logic_game::showCell(const uint r, const uint c) const
{
	return map->cells[r][c];
}

void logic_game::clearCell(const Point2D pos)
{
	int r = int(pos.getY());
	int c = int(pos.getX());
	map->cells[r][c] = Empty;
}

void logic_game::setCell(const uint r, const uint c, MapCell mc) const
{
	map->cells[r][c] = mc;
}

// :::::::::::::::::: Metodos relacionados con PLAYER ::::::::::::::::::::::

void logic_game::addPoints(const int pts)
{
	points = points + pts;
	lvlPoints = lvlPoints + pts;
}

bool logic_game::isAlive()
{
	if (lives >= 0) return true;
	return false;
}

void logic_game::eraseObject(list<SDL_Object*>::iterator it)
{
	acedObjsMot().eraseObject(it);
}

double logic_game::calculateDistanceFrom(const Point2D posA, const Point2D posB)
{
	double x = posA.getX();
	double y = posA.getY();
	double a = posB.getX();
	double b = posB.getY();

	return sqrt(pow(x - a, 2) + pow(y - b, 2));
}

template<typename T>
bool logic_game::checkCollisions(const SDL_Rect& rect)
{
	list<SDL_Object*> stage = acedObjsMot().getStage();
	for (SDL_Object* o : stage) {
		T* g = dynamic_cast<T*>(o);
		if (g != nullptr) {
			SDL_Rect objRect = g->getDestRect();
			if (SDL_HasIntersection(&rect, &objRect)) {
				return true;
			}
		}
	}
	return false;
}

void logic_game::setCellTam(uint wC, uint hC)
{
	wCell_ = wC; hCell_ = hC;
}

void logic_game::setInfo(uint lv, int lvs, uint pts, uint lvlPts)
{
	lvl = lv;
	lives = lvs;
	points = pts;
	lvlPoints = lvlPts;
}

int logic_game::randomNumber(int num)
{
	int rnd = 0;
	if (num != 0)
	{
		rnd = 0 + rand() % (num - 0);
	}
	return rnd;
}

















// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
#pragma endregion
