#pragma once

#include <string>
#include "../../ecs/Component.h"
#include "../../GameObjects/Character.h"
#include "../../Templates/CharacterSheet.h"
#include "../../Structures/Panel.h"
#include "../../Managers/game/InterfazManager.h"

const int NUM_LET = 200;

class PanelDesc : public Component {
public:
	PanelDesc(SDLGame* game, Panel* p, InterfazManager* iM, Hability* hab)
		: Component(ecs::PanelDesc),pan_(p), iManager_(iM), hab_(hab) {};
	virtual ~PanelDesc() {};

	void init() override;
	void update() override;
	void draw() override;

private:
	Panel* pan_;
	InterfazManager* iManager_;
	Hability* hab_;

	string nombreHab_;
	string descripcionHab_;
	string manaHab_;
	// string tipoHab_;
	// string modificadorHab_;
	//---
	SDL_Rect marco_;
	SDL_Rect titulo_;
	SDL_Rect descripcion_;
	SDL_Rect mana_;
	//---
	SDL_Color colorTextoTitulo_ = hex2sdlcolor("0xFFD700FF");
	SDL_Color colorTextoDescripcion_ = hex2sdlcolor("0xFFFFFFFF");
	SDL_Color colorTextoMana_ = hex2sdlcolor("0x0055FFFF");
	//---
	std::pair<int, int> tamTextoGrande_ = { NUM_LET * 10 + 1, 36 }; // { 2001, 36 } para NUM_LET = 200
	std::pair<int, int> tamTextoPequenyo_ = { tamTextoGrande_.first/1.5, tamTextoGrande_.second /1.5 }; // { 1334, 24 } para NUM_LET = 200
	//---
	int offsetMarcoX_ = 15;
	int	offsetMarcoY_ = 10;

	void drawPanel();

	std::string checkLineSize(std::string line);
};