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
	switch (state_)
	{
	/*case gameST::MainMenu:
		cout << "MAIN MENU" << endl;
		break;*/
	case gameST::LOBBY:
		//cout << "LOBBY REACHED" << endl;
		//changeState(gameST::START_EXPLORING);
		break;
	case gameST::START_EXPLORING:
		tem_->startExploring();
		cout << "EXPLORATION STARTED" << endl;
		tem_->createLaberinto();
		tem_->checkOutNoInitialEnemy();
		changeState(gameST::EXPLORING);
		break;
	/*case gameST::EXPLORING:
		cout << "ON EXPLORING" << endl;
		break;*/
	case gameST::START_COMBAT:
		cout << "FIGHT STARTED" << endl;
		tem_->startCombat();
		changeState(gameST::COMBAT);
		break;
	/*case gameST::COMBAT:
		break;*/
	case gameST::END_EXPLORING:
		cout << "EXPLORING FINISHED" << endl;
		tem_->onExitLaberinto();
		changeState(gameST::LOBBY);
		break;
	default:
		break;
	}
}
