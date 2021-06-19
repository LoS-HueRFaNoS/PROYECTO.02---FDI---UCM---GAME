#pragma once

#include <string>
#include "../../ecs/Component.h"
#include "../../GameObjects/Character.h"
#include "../../Templates/CharacterSheet.h"
#include "../../Structures/Panel.h"
#include "../../Managers/game/InterfazManager.h"

class PanelDesc : public Component {
public:
	PanelDesc(SDLGame* game, Panel* p, InterfazManager* iM, Hability* hab, bool aff)
		: Component(ecs::PanelDesc),pan_(p), iManager_(iM), hab_(hab), affordable_(aff) {
		assert(hab_ != nullptr);
	};
	virtual ~PanelDesc() {};

	void init() override;
	void update() override;
	void draw() override;

private:
	Panel* pan_;
	InterfazManager* iManager_;
	Hability* hab_;
	bool affordable_;

	string nombreHab_;
	vector<string> descripcionHab_;
	string manaHab_;
	string tipoHab_;
	string modificadorHab_;
	//---
	SDL_Rect marco_;
	SDL_Rect titulo_;
	SDL_Rect descripcion_;
	SDL_Rect mana_;
	SDL_Rect tipo_;
	SDL_Rect modificador_;
	//---
	SDL_Color colorTextoTitulo_;
	SDL_Color colorTextoDescripcion_;
	SDL_Color colorTextoMana_;
	SDL_Color colorTextoTipo_;
	SDL_Color colorTextoModificador_;
	//-----
	int numLet_ = 38;
	int anchoTexto_ = 425; // 2001 para NUM_LET = 38
	int altoTexto_ = 35;
	//---
	int offsetMarcoX_ = 15;
	int offsetMarcoX2_ = offsetMarcoX_ + 285;
	int	offsetMarcoY_ = 10;

	void drawPanel();

	std::string checkLineSize(std::string line);
};