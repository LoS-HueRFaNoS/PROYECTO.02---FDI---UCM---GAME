#pragma once

#include <string>
#include "../../ecs/Component.h"
#include "../../GameObjects/Character.h"
#include "../../Templates/CharacterSheet.h"
#include "../../Structures/Panel.h"
#include "../../Managers/game/InterfazManager.h"

const int NUM_LET = 20;

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
	SDL_Rect primElem;

	void drawPanel();

	std::string checkLineSize(std::string line);
};