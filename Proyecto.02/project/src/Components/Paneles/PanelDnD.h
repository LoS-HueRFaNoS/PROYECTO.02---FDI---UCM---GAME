#pragma once
#include <string>
#include "../../ecs/Component.h"
#include "../../GameObjects/Character.h"
#include "../../Templates/CharacterSheet.h"
#include "../../Structures/Panel.h"
#include "../../Managers/game/InterfazManager.h"

const int NUM_WEAKNESSES = 8;

class PanelDnD : public Component {
private:
	Panel* pan_;
	InterfazManager* iManager_;
public:
	PanelDnD(SDLGame* game, Panel* p, Character* c, InterfazManager* iM) : 
		Component(ecs::PanelDnD), 
		pan_(p),
		character_(c),
		character_sheet(),
		iManager_(iM), 
		marco(), 
		firstElement() {};
	virtual ~PanelDnD() {};

	void init() override;
	void update() override;
	void draw() override;

private:
	SDL_Rect marco, firstElement;
	Character* character_;
	CharacterSheet* character_sheet;

	void drawPanelDnDActual();

	void addTitleName();
	void addWeaknesses();
	void addMainStats();
	void addArmorWeapon();
	void addCharacter();
	void addHabilities(Hero* hero);

	void addTemplate();
};
