#include "GameStateManager.h"
#include "../Managers/TheElementalMaze.h"
#include "../Templates/callbacks.h"
GameStateManager::GameStateManager() :
	Component(ecs::GameStateManager),
	state_(gameST::MainMenu),
	tem_(nullptr)
{};

void GameStateManager::init()
{
	tem_ = TheElementalMaze::instance();
}

void GameStateManager::update()
{
	if (!stateChanged)
		return;
	stateChanged = false;
	switch (state_)
	{
	case gameST::MainMenu:
		TheElementalMaze::instance()->getSDLGame()->getAudioMngr()->playMusic(Resources::AudioId::MenuInicial, -1);
		break;
	case gameST::LOBBY: case gameST::DURING_LOBBY:
		TheElementalMaze::instance()->getSDLGame()->getAudioMngr()->playMusic(Resources::AudioId::Lobby, -1);
		break;
	case gameST::START_EXPLORING:
		tem_->startExploring();
		tem_->createLaberinto();
		tem_->checkOutNoInitialEnemy();
		changeState(gameST::EXPLORING);
		break;
	case gameST::EXPLORING:
		game_->getAudioMngr()->playMusic(Resources::Exploracion, -1);
		break;
	case gameST::START_COMBAT:
		tem_->startCombat();
		changeState(gameST::COMBAT);
		break;
	case gameST::COMBAT:
		break;
	case gameST::END_EXPLORING:
		//tem_->nextLevel();
		changeState(gameST::START_EXPLORING);
		break;
	case gameST::GAME_OVER:
		tem_->onExitLaberinto();
		changeState(gameST::LOBBY);
		break;
	default:
		break;
	}
}
