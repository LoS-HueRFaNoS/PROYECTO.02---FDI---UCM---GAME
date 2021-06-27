#pragma once

#include <vector>

#include "Managers/SDLGame.h"
#include "Utilities/checkML.h"

class InterfazManager;
class CharacterManager;
class AnimationManager;
class TheElementalMaze;
class EntityManager;
class Cursor;
class Fondo;

typedef unsigned int uint;

class Game {

public:
	static Game* Init();
	static Game* Instance();
	Game();
	virtual ~Game();

	// from SDLGame
	void start();
	SDLGame* getSDLGame() { return game_; }
	void exitGame() { exit_ = true; }

	Fondo* getFondo() { return fondo; }

private:
	static std::unique_ptr<Game> instance_;
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
	AnimationManager* animManager_;

	Fondo* fondo;
	Cursor* c_;
	Cursor* createCursor(Vector2D pos, uint width, uint height, Resources::TextureId image);

	bool exit_;
};