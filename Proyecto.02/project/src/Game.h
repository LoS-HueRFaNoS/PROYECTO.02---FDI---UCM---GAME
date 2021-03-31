#pragma once

#include <vector>

#include "Manager.h"
#include "SDLGame.h"
#include "checkML.h"
class Game {

public:
	Game();
	virtual ~Game();

	// from SDLGame
	void start();
	void stop();
	SDLGame* getSDLGame() { return game_; };

private:
	void initGame();
	void createLaberinto();
	void closeGame();
	void handleInput();
	void update();
	void render();
	SDLGame* game_;
	EntityManager* entityManager_;
	bool exit_;

	const static int _WINDOW_WIDTH_ = 1200;
	const static int _WINDOW_HEIGHT_ = 900;
};