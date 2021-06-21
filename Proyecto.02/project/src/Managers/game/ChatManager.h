#pragma once
#include "../../Utilities/interfaz/MousePanelMecanics.h"
#include "../../Structures/TextBlock.h"


class ChatManager : public TextBlock, public MousePanelMecanics 
{
private:
	ChatManager(SDLGame* game) : TextBlock(game) {};
	void init();

public:
	static void Init();

	static ChatManager* instance() {
		assert(instance_.get() != nullptr);
		return instance_.get();
	}

	void update() override;
	void draw() override;

	virtual ~ChatManager() {};

private:
	static std::unique_ptr<ChatManager> instance_;

};
