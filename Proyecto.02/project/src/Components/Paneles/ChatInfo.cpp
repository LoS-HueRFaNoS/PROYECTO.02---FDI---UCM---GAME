#include "ChatInfo.h"
#include <SDL.h>
#include <cassert>
#include "../../Utilities/SDL_macros.h"

void ChatInfo::init()
{
	chat_ = ChatManager::instance();
}

void ChatInfo::update()
{
	chat_->update();
}

void ChatInfo::draw()
{
	chat_->draw();
}
