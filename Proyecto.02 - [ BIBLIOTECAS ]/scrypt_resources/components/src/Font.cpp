// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
//

#include "Font.h"
#include <iostream>
#include <fstream>

#pragma region METODOS_FONT

Font::Font()
{
	if (TTF_Init() < 0) throw SDLerror(string(TTF_GetError()).c_str(), "TTF");
	ifstream file;
	file.open(fontsData);
	if (!file.is_open()) throw FileNotFoundError(fontsData);
	else {
		// variables
		string line;
		// inicio
		capacity = cont = 0;
		file >> capacity; // num_fonts
		getline(file, line); // elimina la l�nea en blanco
		fonts = new TTF_Font*[capacity];
		// bucle
		while (!file.fail() && cont < capacity) {
			getline(file, line); // (stream + string)
			fonts[cont] = load(fontsPath + line, SIZE); // anade cada ttf
			++cont;
		}
		file.close();
	}
}

TTF_Font* Font::load(string fileName, uint size)
{
	TTF_Font* font = TTF_OpenFont(fileName.c_str(), size); // Fichero .ttf y tama�o en ptos
	if (!font) {
		throw FileNotFoundError(fileName + ";\n" + string(TTF_GetError()).c_str());
	}
	return font;
}

TTF_Font* Font::loadFont(fontName fontFile, uint size) {
	TTF_Font* font = load(to_string(fontFile).c_str(), size);
	//cout << to_string(fontFile) << " loaded!" << endl;
	return font;
}

void Font::liberar()
{
	if (!fonts)
		for (uint i = 0; i < capacity; ++i)
			TTF_CloseFont(fonts[i]);
		delete[] fonts;
}

SDL_Surface* Font::generateSurface(fontName fileName, string line, SDL_Color color) const
{
	return TTF_RenderText_Solid(fonts[fileName], line.c_str(), color);;
}

void Font::render(const SDL_Rect& destRect) const
{
	// textura + destRect : pero desde fuera
}

string Font::to_string(fontName fileName) {
	string end = ".ttf";
	switch (fileName)
	{
	case CircleOfDust: return (fontsPath + "CircleOfDust" + end);
		break;
	case FreeMono: return (fontsPath + "FreeMono" + end);
		break;
	case FreeMonoBold: return (fontsPath + "FreeMonoBold" + end);
		break;
	case FreeMonoBoldOblique: return (fontsPath + "FreeMonoBoldOblique" + end);
		break;
	case FreeMonoOblique: return (fontsPath + "FreeMonoOblique" + end);
		break;
	case FreeSans: return (fontsPath + "FreeSans" + end);
		break;
	case FreeSansBold: return (fontsPath + "FreeSansBold" + end);
		break;
	case FreeSansBoldOblique: return (fontsPath + "FreeSansBoldOblique" + end); 
		break;
	case FreeSansOblique: return (fontsPath + "FreeSansOblique" + end);
		break;
	case FreeSerif: return (fontsPath + "FreeSerif" + end);
		break;
	case FreeSerifBold: return (fontsPath + "FreeSerifBold" + end);
		break;
	case FreeSerifBoldItalic: return (fontsPath + "FreeSerifBoldItalic" + end);
		break;
	case FreeSerifItalic: return (fontsPath + "FreeSerifItalic" + end);
		break;
	default:
		return "ERROR: en el codigo para la fuente introducida";
		break;
	}
}














// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
#pragma endregion