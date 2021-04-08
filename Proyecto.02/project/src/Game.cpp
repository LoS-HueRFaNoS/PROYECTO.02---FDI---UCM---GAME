#include "SDL_macros.h"
#include "Game.h"
#include <assert.h>
#include "InputHandler.h"
#include "Rectangle.h"
#include "ecs.h"
#include "Transform.h"
#include "Image.h"
#include "SDLGame.h"
#include "SDL_macros.h"
#include "MazePos.h"

// Nuestro includes
#include "CombatManager.h"
#include "InterfazManager.h"
#include "PlayerMotion.h"
#include "PlayerViewer.h"
#include "../TheElementalMaze.h"
//

using namespace std;

Game::Game() :
	game_(nullptr), //
	entityManager_(nullptr), //
	characterManager_(nullptr), //
	exit_(false) {
	initGame();
}

Game::~Game() {
	closeGame();
}

void Game::initGame() {

	game_ = SDLGame::init("VAMOS A LLORAR CON SDL", _WINDOW_WIDTH_, _WINDOW_HEIGHT_);

	entityManager_ = new EntityManager(game_);

	TheElementalMaze* TEM = static_cast<TheElementalMaze*>(entityManager_->addEntity());
	TEM->init(game_, entityManager_);

	//Hero* wizard = new Hero(game_, entityManager_);
	//Hero* warrior = new Hero(game_, entityManager_);
	//warrior->getWeapon();
	//warrior->getArmor();
	//Hero* rogue = new Hero(game_, entityManager_);
	//rogue->getWeapon();
	//rogue->getArmor();
	//Hero* cleric = new Hero(game_, entityManager_);
	//cleric->getWeapon();
	//cleric->getArmor();
	//Enemy* e1 = new Enemy(game_, entityManager_);
	//Enemy* e2 = new Enemy(game_, entityManager_);
	//Enemy* e3 = new Enemy(game_, entityManager_);

	//wizard->loadFromTemplate(rpgLogic::WIZARD);
	//warrior->loadFromTemplate(rpgLogic::WARRIOR);
	//rogue->loadFromTemplate(rpgLogic::ROGUE);
	//cleric->loadFromTemplate(rpgLogic::CLERIC);
	//e1->loadFromTemplate(rpgLogic::ZOMBIE);
	//e2->loadFromTemplate(rpgLogic::ZOMBIE);
	//e3->loadFromTemplate(rpgLogic::ZOMBIE);

	//wizard->addHability<Fireball>();
	//wizard->addHability<SingleTargetAttackExample>();
	//wizard->addHability<SelfHealExample>();
	//wizard->addHability<AllyTeamAttackExample>();

	//warrior->addHability<SingleTargetAttackExample>();
	//warrior->addHability<AllyTeamAttackExample>();

	//rogue->addHability<SingleTargetAttackExample>();
	//rogue->addHability<AllyTeamAttackExample>();

	//cleric->addHability<SingleTargetHealxample>();
	//cleric->addHability<SelfHealExample>();
	//cleric->addHability<AllyTeamHealExample>();
	//cleric->addHability<AllyTeamAttackExample>();

	//cm->addCharacter(wizard);
	//cm->addCharacter(warrior);
	//cm->addCharacter(rogue);
	//cm->addCharacter(cleric);
	//cm->addCharacter(e1);
	//cm->addCharacter(e2);
	//cm->addCharacter(e3);

	//cm->startCombat();

	//cout << "Characters Loaded" << endl;
	//

}

void Game::closeGame() {
	delete entityManager_;
	//delete TEM;
	delete game_;
}

void Game::start() {
	exit_ = false;

	while (!exit_) {
		Uint32 startTime = game_->getTime();

		handleInput();
		update();
		render();

		Uint32 frameTime = game_->getTime() - startTime;
		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}
}

void Game::stop() {
	exit_ = true;
}

void Game::handleInput() {

	InputHandler* ih = InputHandler::instance();

	ih->update();

	if (ih->keyDownEvent()) {
		if (ih->isKeyDown(SDLK_ESCAPE)) {
			exit_ = true;
		}

		if (ih->isKeyDown(SDLK_f)) {
			int flags = SDL_GetWindowFlags(game_->getWindow());
			if (flags & SDL_WINDOW_FULLSCREEN) {
				SDL_SetWindowFullscreen(game_->getWindow(), 0);
			}
			else {
				SDL_SetWindowFullscreen(game_->getWindow(),
					SDL_WINDOW_FULLSCREEN);
			}
		}
	}

}

void Game::update() {
	entityManager_->update();
	characterManager_->update();
}

void Game::render() {
	SDL_SetRenderDrawColor(game_->getRenderer(), COLOR(0x00AAAAFF));
	SDL_RenderClear(game_->getRenderer());

	entityManager_->draw();
	characterManager_->draw();

	SDL_RenderPresent(game_->getRenderer());
}