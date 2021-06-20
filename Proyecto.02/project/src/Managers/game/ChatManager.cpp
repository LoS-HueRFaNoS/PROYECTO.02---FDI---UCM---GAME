#include "ChatManager.h"
#include "../TheElementalMaze.h"
#include "../../ecs/Entity.h"

std::unique_ptr<ChatManager> ChatManager::instance_;

//--- INIT ----------------------------------------------------------------------

// Inicializa el Manager/Singleton
void ChatManager::Init()
{
	assert(instance_.get() == nullptr);
	instance_.reset(new ChatManager(TheElementalMaze::instance()->getSDLGame()));
	instance_->init();
}

// Inicializa los valores para el panel del chat
void ChatManager::init()
{
	// relative sizes
	SDL_Panel pan = game_->relativePanel(710, 790, 540, 190, 1, 9, 20, 10);
	MousePanelMecanics::Init(4, set_FE::DOWN);
	TextBlock::Init(pan);	
}

//--- UPDATE ---------------------------------------------------------------

// Hace el efecto de scroll si detecta MouseScrollEvent dentro del chat
void ChatManager::update()
{
	TextBlock::update();
	scroll(marco_, tuppleLimits_, entities, ObjectPanel::bottomElement_.h);
}

//--- DRAW ---------------------------------------------------------------

void ChatManager::draw()
{
	TextBlock::draw();	
}
