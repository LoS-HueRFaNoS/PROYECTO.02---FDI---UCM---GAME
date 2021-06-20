#pragma once
#include <string>
#include "../../ecs/Component.h"
#include "../../Managers/game/ChatManager.h"

class ChatInfo : public Component {
private:
	ChatManager* chat_;

public:
	ChatInfo() : Component(ecs::ChatInfo), chat_(nullptr) {};
	virtual ~ChatInfo() { /*delete chat_; chat_ = nullptr;*/ };

	void init() override;
	void update() override;
	void draw() override;
};
