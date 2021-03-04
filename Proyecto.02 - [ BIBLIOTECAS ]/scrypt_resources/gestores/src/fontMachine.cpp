// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
//

#include "fontMachine.h"
#include "windowAPP.h"
#include <fstream>

#pragma region METODOS_FONT_MACHINE

fontMachine::fontMachine()
{
	render = acedWinApp().getRenderer();
	Win_h = acedWinApp().getWin_h();
	Win_w = acedWinApp().getWin_w();

	text = new Texture(render, "../resources/font/retro_font.png", 4, 10);
	ifstream file;
	file.open(dataClavesFile);
	if (!file.is_open()) throw FileNotFoundError(dataClavesFile);
	else {
		// variables
		string fraseClave;
		// inicio
		capacity = cont = 0;
		file >> capacity; // num_claves
		getline(file, fraseClave); // elimina la l�nea en blanco
		claves = new string[capacity];
		// bucle
		while (!file.fail() && cont < capacity) {
			getline(file, fraseClave); // (stream + string)
			claves[cont] = fraseClave; // anade cada frase clave
			++cont;
		}
		file.close();
	}
}

// :::::::::::::::::: AYUDA PARA EL CURSOR ::::::::::::::::::::::

SDL_Rect fontMachine::getSingleBox(word w, LINE k) // devuelve el contenedor de un s�lo char (en una l�nea)
{
	uint tam = uint(strlen(w));
	SDL_Rect rect = setLine(tam, k);
	return rect;
}

// :::::::::::::::::: MOTOR DE LA FUENTE ::::::::::::::::::::::

bool fontMachine::findLetter(const char ch) // si encuentra la letra, sit�a el frame a su posici�n
{
	bool success = false;
	int r;
	int c;
	if (int(ch) == int(' ')) { return success; }
	else if (int(ch) >= int('A')) 
	{
		r = 1;
		c = ch - 'A';			//  ( A - J )
		
		if (c >= 20) 
		{
			r = 3;
			c = c - 20;			// ( U - Z )
		}
		else if (c >= 10)
		{
			r = 2;
			c = c - 10;			// ( K - T )
		}
		success = true;
	}
	else if (int(ch) >= int('0') && int(ch) <= int('9'))
	{
		r = 0;
		c = ch - '0';
		success = true;
	}
	else
	{
		r = 3;
		if (int(ch) == int('-')) {	c = 6; success = true;	}
		else if (int(ch) == int('=')) {	c = 7; success = true;	}
		else if (int(ch) == int('*')) { c = 8; success = true;	}
		else if (int(ch) == int(':')) { c = 9; success = true;	}
	}
	if (success) { row = r; col = c; }
	return success;
}

void fontMachine::RETROwrite(word w, SDL_Rect rect) // escribe el texto recibido
{
	uint tam = uint(strlen(w));
	for (uint i = 0; i < tam; i++)
	{
		if (!findLetter(w[i])) // si no encuentra la letra, escribe un espacio
		{
			rect.x = rect.x + rect.w;
		}
		else					  // en caso contrario, escribe la letra
		{
			text->renderFrame(rect, row, col);
			rect.x = rect.x + rect.w;
		}
	}
}

void fontMachine::TTFwrite(word texto, const fontName f)
{
	SDL_Color color = SDL_Color{ 255, 255, 255, 255 }; // predeterminado
	Texture t = Texture(render, f, string(texto), color);
	uint tam = uint(strlen(texto));
	SDL_Rect rect = setLine(tam, TitleLine);
	rect.w = rect.w * tam;
	rect.h = rect.h * 2;
	t.renderText(rect);
}

void fontMachine::writeLIN(word w, LINE k) // escribe en una linea concreta
{
	uint tam = uint(strlen(w));
	SDL_Rect rect = setLine(tam, k);
	RETROwrite(w, rect);
}

void fontMachine::writeFIL(word w, SDL_Rect rect) // rellena el rectangulo
{
	uint tam = uint(strlen(w));
	rect.w = rect.w / tam;
	RETROwrite(w, rect);
}

void fontMachine::writeSuperTitle(word texto, fontName fontFile) // escoge uno ya definido
{
	TTFwrite(texto, fontFile);
}

SDL_Rect fontMachine::getContainer(word w, LINE k) // devuelve el contenedor final de la palabra (en una l�nea)
{
	uint tam = uint(strlen(w));
	SDL_Rect rect = getSingleBox(w, k);
	rect.w = rect.w * tam;
	return rect;
}

// :::::::::::::::::: AJUSTES DE TAMA�O DE LETRA ::::::::::::::::::::::

SDL_Rect fontMachine::setSize(const double line, const uint tam, Point2D e)
{
	SDL_Rect rect;
	int r = Win_h / uint(e.getY());		// alto de letra
	int c = Win_w / uint(e.getX());		// ancho de letra
	rect.h = r;
	rect.w = c;
	rect.y = int(Win_h * (2 + line) / 3);		// altura de linea en pantalla
	rect.x = int(Win_w / 2 - c * tam / 2);		// lo centra
	return rect;
}

SDL_Rect fontMachine::setLine(const uint tam, LINE k)
{
	Point2D escale;
	double line;
	switch (k) {
	// info principal:
	case TitleLine:
		line = -1.0;
		escale.set(20, 10);
		break;
	case SubtitleLine:
		line = -0.55;
		escale.set(25, 15);
		break;
	case InfoLine:
		line = -1.9;
		escale.set(40, 40);
		break;
	case InfoLine2:
		line = -1.8;
		escale.set(40, 40);
		break;
	default:
		escale.set(30, 20);
		// info opciones:
		switch (k) {
		case OptionsLine:
			line = -0.2;
			break;
		case ButtonLine:
			line = 0.1;
			break;
		case ButtonLine2:
			line = 0.4;
			break;
		case ButtonLine3:
			line = 0.7;
			break;
		}
		break;
	}
	return setSize(line, tam, escale);
}

















// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
#pragma endregion