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
#include "Manager.h"

// Nuestro includes
#include "CharacterManager.h"
#include "CombatManager.h"
#include "Interfaz.h"
#include "InterfazManager.h"
#include "PlayerMotion.h"
#include "PlayerViewer.h"
#include "Cursor.h"
#include "../TheElementalMaze.h"
//

using namespace std;

Game::Game() : game_(nullptr),			   //
			   entityManager_(nullptr),	   //
			   characterManager_(nullptr), //
			   exit_(false)
{
	initGame();
}

Game::~Game()
{
	closeGame();
}

void Game::initGame()
{
	int initTime = 0;
	game_ = SDLGame::init("VAMOS A LLORAR CON SDL", _WINDOW_WIDTH_, _WINDOW_HEIGHT_);

	Texture *tex_ = new Texture(game_->getRenderer(), "resources/images/cargando.png");
	SDL_Rect dest = {0, 0, int(game_->getWindowWidth()), int(game_->getWindowHeight())};
	SDL_SetRenderDrawColor(game_->getRenderer(), COLOR(0x00AAAAFF));
	SDL_RenderClear(game_->getRenderer());
	tex_->render(dest);
	SDL_RenderPresent(game_->getRenderer());

	game_->initResources();

	entityManager_ = new EntityManager(game_);

	characterManager_ = new CharacterManager(game_);

	interfazManager_ = new InterfazManager(game_);

	gameManager_ = TheElementalMaze::initInstace(game_, entityManager_, characterManager_, interfazManager_);

	entityManager_->addEntity(gameManager_);

	c_ = createCursor(Vector2D(200, 200), 50, 50, Resources::Mouse);

	int endTime = 0;
}

void Game::closeGame()
{
	delete entityManager_;
	delete characterManager_;
	delete interfazManager_;
	delete game_;
}

void Game::start()
{
	exit_ = false;

	while (!exit_)
	{
		Uint32 startTime = game_->getTime();

		handleInput();
		update();
		render();

		Uint32 frameTime = game_->getTime() - startTime;
		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}
}

void Game::stop()
{
	exit_ = true;
}

void Game::handleInput()
{

	InputHandler *ih = InputHandler::instance();

	ih->update();

	if (ih->keyDownEvent())
	{
		if (ih->isKeyDown(SDLK_ESCAPE))
		{
			exit_ = true;
		}

		if (ih->isKeyDown(SDLK_f))
		{
			int flags = SDL_GetWindowFlags(game_->getWindow());
			if (flags & SDL_WINDOW_FULLSCREEN)
			{
				SDL_SetWindowFullscreen(game_->getWindow(), 0);
			}
			else
			{
				SDL_SetWindowFullscreen(game_->getWindow(),
										SDL_WINDOW_FULLSCREEN);
			}
		}
	}
}

void Game::update()
{
	entityManager_->update();
	characterManager_->update();
	interfazManager_->update();
}

void Game::render()
{
	SDL_SetRenderDrawColor(game_->getRenderer(), COLOR(0x00AAAAFF));
	SDL_RenderClear(game_->getRenderer());

	entityManager_->draw();
	characterManager_->draw();
	interfazManager_->draw();
	c_->draw();

	SDL_RenderPresent(game_->getRenderer());
}

Cursor* Game::createCursor(Vector2D pos, uint width, uint height, Resources::TextureId image)
{
	Cursor* c = static_cast<Cursor*>(entityManager_->addEntity());
	c->init(game_, pos, width, height, image);
	return c;
}