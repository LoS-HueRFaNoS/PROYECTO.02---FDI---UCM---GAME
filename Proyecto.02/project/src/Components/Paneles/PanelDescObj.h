#pragma once

#include <string>
#include "../../ecs/Component.h"
#include "../../GameObjects/Character.h"
#include "../../Templates/CharacterSheet.h"
#include "../../Structures/Panel.h"
#include "../../Managers/game/InterfazManager.h"

class PanelDescObj : public Component {
public:
	PanelDescObj(SDLGame* game, Panel* p, InterfazManager* iM, Item* ite)
		: Component(ecs::PanelDescObj), pan_(p), iManager_(iM), ite_(ite) {
		assert (ite_ != nullptr);
	};
	virtual ~PanelDescObj() {};

	void init() override;
	void update() override;
	void draw() override;

private:
	Panel* pan_;
	InterfazManager* iManager_;
	Item* ite_;

	string nombreItem_;
	vector<string> descripcionItem_;
	string tipoItem_;
	string afinidadItem_;
	string costeItem_;
	string valorItem_;
	//---
	SDL_Rect marco_;
	SDL_Rect titulo_;
	SDL_Rect descripcion_;
	SDL_Rect tipo_;
	SDL_Rect afinidad_;
	SDL_Rect coste_;
	SDL_Rect valor_;
	//---
	SDL_Color colorTextoTitulo_;
	SDL_Color colorTextoDescripcion_;
	SDL_Color colorTextoTipo_;
	SDL_Color colorTextoAfinidad_;
	SDL_Color colorTextoCoste_;
	SDL_Color colorTextoValor_;
	//-----
	int numLet_ = 38;
	int anchoTexto_ = 425; // 425 para NUM_LET = 38
	int altoTexto_ = 35;
	//---
	int offsetMarcoX_ = 15;
	int offsetMarcoX2_ = offsetMarcoX_ + 285;
	int	offsetMarcoY_ = 10;

	void drawPanel();

	std::string checkLineSize(std::string line);
	void generateDescriptionArray();
};