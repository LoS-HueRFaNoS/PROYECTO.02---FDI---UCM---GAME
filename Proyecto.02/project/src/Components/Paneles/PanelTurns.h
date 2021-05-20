#pragma once
#include <string>
#include "../../ecs/Component.h"
#include "../../GameObjects/Character.h"
#include "../../Structures/Panel.h"
#include "../../Managers/game/InterfazManager.h"

class PanelTurns : public Component {
private:
	Panel* pan_;
	InterfazManager* iManager_;
public:
	PanelTurns(SDLGame* game, Panel* p, InterfazManager* iM) : Component(ecs::PanelTurns), pan_(p), iManager_(iM), marco(), firstElement() {};
	virtual ~PanelTurns() {};

	void init() override;
	void update() override;
	void draw() override;

private:
	SDL_Rect marco, firstElement;
	Character* character_;
	std::vector<Character*> turnsList_;

	void drawCharacterActual();
};