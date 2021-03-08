#include "SDL_macros.h"
#include "Game.h"
#include <assert.h>
#include "InputHandler.h"
#include "Rectangle.h"
#include "ecs.h"
#include "Transform.h"
#include "SDLGame.h"
#include "SDL_macros.h"
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
	//laberinto = new Laberinto();
	/*Entity* Fighter = entityManager_->addEntity();
	Transform* FighterTR = Fighter->addComponent<Transform>();
	Fighter->addComponent<FighterCtrl>();
	Fighter->addComponent<FighterViewer>();
	Fighter->addComponent<FighterMotion>();
	Fighter->addComponent<Gun>(GETCMP2(Bullets, BulletsPool));
	Fighter->addComponent<Health>();
	FighterTR->setPos(game_->getWindowWidth() / 2 - 6, game_->getWindowHeight() / 2 - 6);

	Entity* gameManager = entityManager_->addEntity();
	gameManager->addComponent<ScoreManager>();
	gameManager->addComponent<GameLogic>(FighterTR, GETCMP2(Game, AsteroidPool), GETCMP2(Bullets, BulletsPool), GETCMP2(Fighter, Health));
	gameManager->addComponent<ScoreViewer>();
	gameManager->addComponent<GameCtrl>(GETCMP2(Fighter, Health), GETCMP2(Game, AsteroidPool));*/
}

void Game::closeGame() {
	delete entityManager_;
	delete laberinto;
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

