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
#include "PlayerMotion.h"
#include "PlayerViewer.h"

// Nuestro includes
#include "CombatManager.h"
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

	/*Entity* laberinto = entityManager_->addEntity();
	Laberinto* lab = laberinto->addComponent<Laberinto>(entityManager_) ;
	lab -> initFromFile();

	Entity* player = entityManager_->addEntity();
	player->addComponent<MazePos>(Vector2D(0,0));
	player->addComponent<PlayerMotion>(SDLK_UP,SDLK_LEFT,SDLK_RIGHT,lab);
	player->addComponent<PlayerViewer>(lab);*/

	// Nuetro c�digo

	cout << "Loading Characters please wait..." << endl;

	characterManager_ = new CharacterManager(game_);

	Entity* manager = entityManager_->addEntity();

	CombatManager* cm = manager->addComponent<CombatManager>();

	Hero* wizard = characterManager_->addHeroFromTemplate(WIZARD);
	Hero* warrior = characterManager_->addHeroFromTemplate(WARRIOR);
	Hero* rogue = characterManager_->addHeroFromTemplate(ROGUE);
	Hero* cleric = characterManager_->addHeroFromTemplate(CLERIC);;
	Enemy* e1 = characterManager_->addRandomEnemy();
	Enemy* e2 = characterManager_->addRandomEnemy();
	Enemy* e3 = characterManager_->addRandomEnemy();


	wizard->addHability<Fireball>();
	wizard->addHability<SingleTargetAttackExample>();
	wizard->addHability<SelfHealExample>();
	wizard->addHability<AllyTeamAttackExample>();

	warrior->addHability<SingleTargetAttackExample>();
	warrior->addHability<AllyTeamAttackExample>();

	rogue->addHability<SingleTargetAttackExample>();
	rogue->addHability<AllyTeamAttackExample>();

	cleric->addHability<SingleTargetHealxample>();
	cleric->addHability<SelfHealExample>();
	cleric->addHability<AllyTeamHealExample>();
	cleric->addHability<AllyTeamAttackExample>();

	cm->addCharacter(wizard);
	cm->addCharacter(warrior);
	cm->addCharacter(rogue);
	cm->addCharacter(cleric);
	cm->addCharacter(e1);
	cm->addCharacter(e2);
	cm->addCharacter(e3);

	cm->startCombat();

	cout << "Characters Loaded" << endl;
	//
}

void Game::closeGame() {
	delete entityManager_;
	delete characterManager_;
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

