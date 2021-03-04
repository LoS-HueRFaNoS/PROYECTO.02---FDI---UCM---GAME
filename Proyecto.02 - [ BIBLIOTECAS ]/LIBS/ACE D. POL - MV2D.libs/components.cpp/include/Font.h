// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
//

#pragma once
#ifndef FONT_H_
#define FONT_H_

#include "checkML.h"

#include "SDL_ttf.h" // fuentes ttf
// inherits
#include "Singleton.h"

#include "FileNotFoundError.h"
#include "SDLerror.h"

const uint SIZE = 72;		// tamano por defecto
const string fontsData = "../resources/data/ttf_fonts.dat";
const string fontsPath = "../resources/ttf_fonts/";
enum fontName { CircleOfDust, FreeMono, FreeMonoBold, FreeMonoBoldOblique, FreeMonoOblique, FreeSans, FreeSansBold, FreeSansBoldOblique, FreeSansOblique, FreeSerif, FreeSerifBold, FreeSerifBoldItalic, FreeSerifItalic };

class Font : public Singleton<Font>
{
	friend Singleton<Font>;
	Font();
	
private:
	TTF_Font** fonts = nullptr;				// uso general, todas las fuentes a mano
	uint cont, capacity;
	string to_string(fontName fileName);
	TTF_Font* load(string fileName, uint size);
	TTF_Font* loadFont(fontName fontFile, uint size);		// acceso seguro
public:
	~Font() { liberar(); };
	void liberar();

	SDL_Surface* generateSurface(fontName fileName, string line, SDL_Color color) const;
	void render(const SDL_Rect& destRect) const;
};

inline Font& acedFontTTF() {
	return *Font::instance();
}














// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
#endif