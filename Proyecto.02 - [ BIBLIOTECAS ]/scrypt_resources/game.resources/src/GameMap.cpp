// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
//

#include "GameMap.h"
#include "logic_game.h"
#include "windowAPP.h"
#include <iostream>

#pragma region METODOS_GAMEMAP

// :::::::::::::::::: CONSTRUCTOR ::::::::::::::::::::::

GameMap::GameMap(Point2D pIni, uint rs, uint cs, uint w, uint h) : SDL_Object(pIni, w, h), rows(rs), cols(cs)
{
	cells = new MapCell* [rows];
	for (int i = 0; i < rows; ++i) {
		cells[i] = new MapCell[cols];
	}
}

// :::::::::::::::::: MOTOR DEL MAPA ::::::::::::::::::::::

bool GameMap::intersectsWall(SDL_Rect rect) // si da con la pared devuelve true (se trabaja en mapCoords)
{
	Point2D topLeft = acedLogic().SDLPointToMapCoords(Point2D(double(rect.x) + 1.0, double(rect.y) + 1.0));
	Point2D botRight = acedLogic().SDLPointToMapCoords(Point2D(double(rect.x) + double(rect.w) - 1.0, double(rect.y) + double(rect.h) - 1.0));
	for (int r = int(topLeft.getY()); r <= int(botRight.getY()); ++r)
		for (int c = int(topLeft.getX()); c <= int(botRight.getX()); ++c)
			if (cells[r][c] == Wall || cells[r][c] == Door)
				return true;
	return false;
}

// :::::::::::::::::: Uso de Ficheros: GUARDAR & CARGAR ::::::::::::::::::::::

void GameMap::render()
{
	SDL_Rect rect;
	rect.h = acedLogic().hCell_;
	rect.w = acedLogic().wCell_;
	for (int r = 0; r < rows; ++r) {
		for (int c = 0; c < cols; ++c) {
			rect.y = (r + INFOBAR) * rect.h;
			rect.x = c * rect.w;

			switch (cells[r][c]) {
			case Wall:
				acedTxtMot().getTexture(WallTxt)->render(rect);
				break;
			case Food:
				acedTxtMot().getTexture(FoodTxt)->render(rect);
				break;
			case Vitamins:
				acedTxtMot().getTexture(BurguerTxt)->render(rect);
				break;
			case Door:
				acedTxtMot().getTexture(DoorTxt)->render(rect);
				break;
			default:
				break;
			}
		}
	}
}

const void GameMap::saveToFile(ofstream& file)
{
	file << rows << ' ' << cols << endl;
	file << pos << ' ' << width << ' ' << height << endl;
	for (int r = 0; r < rows; ++r) {
		for (int c = 0; c < cols; ++c) {
			file << cells[r][c] << ' ';
		}
		file << endl;
	}
}

GameMap::GameMap(ifstream& file)
{
	file >> rows >> cols;
	file >> pos >> width >> height;

	cells = new MapCell * [rows];
	for (int i = 0; i < rows; ++i) {
		cells[i] = new MapCell[cols];
	}
}

// :::::::::::::::::: DESTRUCTOR ::::::::::::::::::::::

GameMap::~GameMap() 
{
	for (int i = 0; i < rows; ++i) {
		delete[] cells[i];
	}
	delete[] cells;
}

















// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
#pragma endregion