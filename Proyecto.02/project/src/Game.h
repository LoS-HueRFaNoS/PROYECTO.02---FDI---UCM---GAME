#pragma once

#include <vector>

#include "SDLGame.h"
#include "checkML.h"

class InterfazManager;
class CharacterManager;
class TheElementalMaze;
class EntityManager;
class Cursor;

typedef unsigned int uint;

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
	//void createLaberinto();
	void closeGame();
	void handleInput();
	void update();
	void render();
	SDLGame* game_;
	EntityManager* entityManager_;
	CharacterManager* characterManager_;
	TheElementalMaze* gameManager_;
	InterfazManager* interfazManager_;

	Cursor* c_;
	Cursor* createCursor(Vector2D pos, uint width, uint height, Resources::TextureId image);

	bool exit_;

	const static int _WINDOW_WIDTH_ = 1200; // 1920px
	const static int _WINDOW_HEIGHT_ = 900; // 1050px
};