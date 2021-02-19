#pragma once
#ifndef FONT_H_
#define FONT_H_

#include "checkML.h"
#include <string>

#include "SDL.h"
#include "SDL_ttf.h" // fuentes ttf

#include "FileNotFoundError.h"
#include "SDLerror.h"

using namespace std;
typedef unsigned int uint;
//const string end = ";\n";
const uint SIZE = 72;		// tamaño por defecto
const string fontsData = "../assets/data/ttf_fonts.dat";
const string fontsPath = "../assets/ttf_fonts/";
enum fontName { CircleOfDust, FreeMono, FreeMonoBold, FreeMonoBoldOblique, FreeMonoOblique, FreeSans, FreeSansBold, FreeSansBoldOblique, FreeSansOblique, FreeSerif, FreeSerifBold, FreeSerifBoldItalic, FreeSerifItalic };

class Font
{
private:
	TTF_Font** fonts = nullptr;				// uso general, todas las fuentes a mano
	uint cont, capacity;
	TTF_Font* font = nullptr;		// uso individual y concreto
	string to_string(fontName fileName);
public:
	Font();
	Font(string fileName, uint size);		// acceso estricto
	Font(fontName fileName, uint size);		// acceso seguro
	~Font() { liberar(); };

	TTF_Font* load(string fileName, uint size);				// acceso estricto
	TTF_Font* loadFont(fontName fontFile, uint size);		// acceso seguro
	void liberar();

	SDL_Surface* generateSurface(string line, SDL_Color color) const;
	void render(const SDL_Rect& destRect) const;
};














// developed by: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL)
#endif