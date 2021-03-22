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

// Nuestro includes
#include "CombatManager.h"
//

using namespace std;

Game::Game() :
	game_(nullptr), //
	entityManager_(nullptr), //
	exit_(false) {
	initGame();
}

Game::~Game() {
	closeGame();
}

void Game::initGame() {

	game_ = SDLGame::init("VAMOS A LLORAR CON SDL", _WINDOW_WIDTH_, _WINDOW_HEIGHT_);

	entityManager_ = new EntityManager(game_);

	// Nuetro código
	Hero* h1 = new Hero(game_, entityManager_);
	Enemy* e1 = new Enemy(game_, entityManager_);

	h1->loadFromTemplate(rpgLogic::WIZARD);
	e1->loadFromTemplate(rpgLogic::ZOMBIE);

	h1->addHability<Fireball>();

	h1->castHability(0, e1);

	//
}

void Game::closeGame() {
	delete entityManager_;

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
}

void Game::render() {
	SDL_SetRenderDrawColor(game_->getRenderer(), COLOR(0x00AAAAFF));
	SDL_RenderClear(game_->getRenderer());

	entityManager_->draw();

	SDL_RenderPresent(game_->getRenderer());
}

