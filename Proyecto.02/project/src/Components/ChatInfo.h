#pragma once
#include <string>
#include "../ecs/Component.h"
#include "../Managers/game/ChatManager.h"

class ChatInfo : public Component {
private:
	ChatManager* chat_;
public:
	ChatInfo(SDLGame* game) : Component(ecs::ChatInfo), chat_(nullptr) {};
	virtual ~ChatInfo() {};

	void init() override;
	void update() override;
	void draw() override;
};
