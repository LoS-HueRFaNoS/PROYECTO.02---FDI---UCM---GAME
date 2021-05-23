#pragma once
#include <string>
#include "../../ecs/Component.h"
#include "../../Templates/CharacterSheet.h"
#include "../../Templates/HabilityResources.h"
#include "../../Structures/Panel.h"
#include "../../Managers/game/InterfazManager.h"

const int NUM_WEAKNESSES = 8;
const int NUM_LETTERS = 20;

enum class infoType {
	HERO,
	ENEMY,
	HABILITY,
	ITEM,
	MESSAGE
};

class CartelInfo : public Component {
private:
	Panel* pan_;
	InterfazManager* iManager_;
public:
	CartelInfo(SDLGame* game, Panel* p, Character* c, infoType ty, InterfazManager* iM) :
		Component(ecs::Cartel_Info),
		pan_(p),
		character_sheet(),
		type(ty),
		iManager_(iM),
		marco(),
		firstElement() {};
	virtual ~CartelInfo() {};

	void init() override;
	void update() override;
	void draw() override;

private:
	SDL_Rect marco, firstElement;
	CharacterSheet* character_sheet;
	Hability* hability_sheet;
	infoType type;

	void drawCartelActual();

	void addTitleName();
	/*void addWeaknesses();
	void addMainStats();
	void addArmorWeapon();
	void addCharacter();
	void addHabilities(Hero* hero);*/

	void addTemplate();
	std::string checkLineSize(std::string line);
};
