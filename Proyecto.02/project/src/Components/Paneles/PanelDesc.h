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
	PanelDesc(SDLGame* game, Panel* p, InterfazManager* iM) : Component(ecs::PanelDesc), pan_(p), iManager_(iM) {};
	virtual ~PanelDesc() {};

	void init() override;
	void update() override;
	void draw() override;

private:
	Panel* pan_;
	InterfazManager* iManager_;

	SDL_Rect marco;
	SDL_Rect titulo;
	SDL_Rect descripcion;
	SDL_Rect mana;

	SDL_Color colorTextoTitulo_ = hex2sdlcolor("0xFFD700FF");
	SDL_Color colorTextoDescripcion_ = hex2sdlcolor("0xFFFFFFFF");
	SDL_Color colorTextoMana_ = hex2sdlcolor("0x0055FFFF");
	//---
	std::pair<int, int> tamTextoGrande_ = { NUM_LET * 10 + 1, 36 }; // { 2001, 36 } para NUM_LET = 200
	std::pair<int, int> tamTextoPequenyo_ = { tamTextoGrande_.first/1.5, tamTextoGrande_.second /1.5 }; // { 1334, 24 } para NUM_LET = 200
	//---
	int offsetMarcoX = 15;
	int	offsetMarcoY = 10;

	void drawPanel();

	std::string checkLineSize(std::string line);
};