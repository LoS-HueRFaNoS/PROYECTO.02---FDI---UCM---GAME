// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
//

#include "InfoBar.h"
#include "logic_game.h"
#include "textureMachine.h"

#pragma region METODOS_INFOBAR

InfoBar::InfoBar(Point2D p, uint w, uint h, uint mc) : SDL_Object(p, w, h), mapCols(mc)
{
	startTime = 0;
	currentTime = MAX_TIME;
}

InfoBar::InfoBar(uint cT, Point2D p, uint w, uint h, uint mc) : SDL_Object(p, w, h), mapCols(mc)
{
	startTime = 0;
	currentTime = cT;
}

void InfoBar::update()
{
	if (startTime == 0) { startTime = SDL_GetTicks(); }
	else if (SDL_GetTicks() - startTime >= 1000) {
		--currentTime;
		startTime = SDL_GetTicks();
	}
}

void InfoBar::render()
{
	SDL_Rect rect;
	rect.h = height;
	rect.w = width;
	rect.y = int(pos.getY());
	rect.x = int(pos.getX());
	// draw lives
	drawLives(rect);
	// draw points
	string sc = to_string(acedLogic().points);
	word w = sc.c_str();
	drawPoints(rect, w);
	// draw time
	sc = to_string(currentTime);
	w = sc.c_str();
	drawTime(rect, w);
}

void const InfoBar::saveToFile(ofstream& file)
{
	file << currentTime << ' ';
	if (currentTime < 0) throw FileFormatError("el valor 'currentTime' no es un entero positivo");
}

// :::::::::::::::::: INFOBAR TOOLS ::::::::::::::::::::::

void InfoBar::drawLives(SDL_Rect rect)
{
	uint nlives = acedLogic().lives;
	for (uint i = 0; i < nlives; ++i)
	{
		acedTxtMot().getTexture(CharactersTxt)->renderFrame(rect, ROW, COL);
		rect.x = rect.x + rect.w;
	}
}

void InfoBar::drawPoints(SDL_Rect rect, word w)
{
	uint n = 0;
	uint tam = uint(strlen(w));
	if (tam >= 2) { n = tam / 2; tam = tam % 2; }
	rect.x = (mapCols - (tam + n) - 1) * rect.w;
	rect.w = rect.w + rect.w * ((tam + n) - 1);
	acedFontMot().writeFIL(w, rect);
}

void InfoBar::drawTime(SDL_Rect rect, word w)
{
	rect.x = (mapCols / 2 - int(strlen(w)) / 2) * rect.w;
	rect.w = rect.w + rect.w;
	acedFontMot().writeFIL(w, rect);
}

word InfoBar::uintToCharConst(uint num)
{
	string sc = to_string(num);
	word w = sc.c_str();
	return w;
}

















// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
#pragma endregion