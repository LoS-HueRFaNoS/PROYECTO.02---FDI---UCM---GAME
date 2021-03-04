// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
//

#pragma once
#ifndef INFOBAR_H_
#define INFOBAR_H_

#include "checkML.h"

#include "SDL_Object.h"
#include "fontMachine.h"

const int ROW = 0;
const int COL = 11;
const int MAX_TIME = 120;

class Game;
class InfoBar : public SDL_Object
{
private:
	uint startTime, currentTime;
	uint mapCols;

public:
	InfoBar(Point2D p, uint w, uint h, uint mc);
	InfoBar(uint cT, Point2D p, uint w, uint h, uint mc);
	virtual ~InfoBar() {};

	virtual void update();
	virtual void render();

	virtual const void saveToFile(ofstream& file);

private:
	void drawLives(SDL_Rect rect);
	void drawPoints(SDL_Rect rect, word w);
	void drawTime(SDL_Rect rect, word w);
	word uintToCharConst(uint num);
};














// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
#endif