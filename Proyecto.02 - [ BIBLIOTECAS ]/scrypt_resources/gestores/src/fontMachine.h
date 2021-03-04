// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
//

#pragma once
#ifndef FONT_MACHINE_H_
#define FONT_MACHINE_H_

#include "checkML.h"

#include "Font.h"
#include "Texture.h"
#include "Vector2D.h"
// inherits
#include "Singleton.h"

// palabras claves:
const enum LINE { TitleLine, SubtitleLine, OptionsLine, ButtonLine, ButtonLine2, ButtonLine3, InfoLine, InfoLine2};
const enum palabraClave { aux, newGame, lvlFinish, loseLife, leftLives, saveLvl, chooseLvl, chooseGame, gameClear, gameOver, options, options1, options2, options3, options4, pause, ToGame, ToMenu, Return, setOptions, salir, lvlSelect, gameSelect, loadGame, saveGame, gameSaved, errorSaving, nameRepeat, noGameSaves };
const string dataClavesFile = "../resources/data/frases_clave.dat";

class fontMachine : public Singleton<fontMachine>
{
	friend Singleton<fontMachine>;
	fontMachine();
private:
	Font* ttf = nullptr;
	SDL_Renderer* render = nullptr;
	Texture* text = nullptr;
	uint row, col;
	uint Win_h, Win_w;
public:
	virtual ~fontMachine() { delete[] claves; delete text; };

	void writeLIN(word w, LINE k);
	void writeFIL(word w, SDL_Rect rect);
	
	void writeSuperTitle(word texto, fontName fontFile);

	SDL_Rect getContainer(word w, LINE k);
	SDL_Rect getSingleBox(word w, LINE k);

	word getClave(palabraClave pC) { return claves[pC].c_str(); };

private:
	string* claves;
	uint cont, capacity;

	void RETROwrite(word w, SDL_Rect rect);
	void TTFwrite(word texto, const fontName f);
	bool findLetter(const char c);
	SDL_Rect setLine(const uint tam, LINE k);
	SDL_Rect setSize(const double line, const uint tam, Point2D e);
};

inline fontMachine& acedFontMot() {
	return *fontMachine::instance();
}














// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
#endif