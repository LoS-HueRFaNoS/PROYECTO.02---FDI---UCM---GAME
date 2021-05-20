#include <assert.h>
#include "Game.h"
#include "Utilities/SDL_macros.h"
#include "Utilities/InputHandler.h"
#include "Utilities/SDL_macros.h"
#include "Components/Transform.h"
#include "Components/Image.h"
#include "Components/MazePos.h"
#include "Components/Interfaz.h"
#include "Components/PlayerMotion.h"
#include "Components/PlayerViewer.h"
#include "GameObjects/Rectangle.h"
#include "GameObjects/Cursor.h"
#include "GameObjects/SDL_Objects.h"
#include "ecs/ecs.h"
#include "ecs/Manager.h"

// Nuestro includes
#include "Managers/game/CharacterManager.h"
#include "Managers/game/CombatManager.h"
#include "Managers/game/InterfazManager.h"
#include "Managers/TheElementalMaze.h"
#include "Managers/SDLGame.h"
#include <Windows.h>
//

using namespace std;

unique_ptr<Game> Game::instance_;

Game* Game::Init()
{
	assert(instance_.get() == nullptr);
	instance_.reset(new Game());
	return instance_.get();
}

Game* Game::Instance()
{
	assert(instance_.get() != nullptr);
	return instance_.get();
}

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
	RECT rect;
	HWND hd = GetDesktopWindow();
	GetClientRect(hd, &rect);
	int client_width = (rect.right - rect.left);
	int client_height = (rect.bottom - rect.top);

	//MODO VENTANA
	game_ = SDLGame::init("THE ELEMENTAL MAZE", client_width * 0.75, client_height * 0.75);
	//game_ = SDLGame::init("THE ELEMENTAL MAZE", 1920, 1080);

	// PANTALLA COMPLETA
	/*game_ = SDLGame::init("THE ELEMENTAL MAZE", client_width, client_height);
	SDL_SetWindowFullscreen(game_->getWindow(), SDL_WINDOW_FULLSCREEN);*/

	Texture *tex_ = new Texture(game_->getRenderer(), "project/resources/images/cargando.png");
	SDL_Rect dest = { 0, 0, int(game_->getWindowWidth()), int(game_->getWindowHeight()) };
	SDL_SetRenderDrawColor(game_->getRenderer(), COLOR(0x00000000));
	SDL_RenderClear(game_->getRenderer());
	tex_->render(dest);
	SDL_RenderPresent(game_->getRenderer());

	game_->initResources();

	entityManager_ = new EntityManager(game_);

	fondo = new Fondo(game_, entityManager_);
	fondo->init(Vector2D(), game_->getWindowWidth(), game_->getWindowHeight());
	entityManager_->addEntity(fondo);

	characterManager_ = new CharacterManager(game_);

	interfazManager_ = new InterfazManager(game_);

	system("cls");

	gameManager_ = TheElementalMaze::initInstace(game_, entityManager_, characterManager_, interfazManager_);

	entityManager_->addEntity(gameManager_);

	c_ = createCursor(Vector2D(200, 200), 50, 50, Resources::Mouse);


	int endTime = 0;
	delete tex_;
}

void Game::closeGame()
{
	delete entityManager_;
	delete characterManager_;
	delete interfazManager_;
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

	InputHandler* ih = InputHandler::instance();

	if (ih->update()) {
		if (ih->keyDownEvent()) {
			if (ih->isKeyDown(SDLK_ESCAPE)) {
				exit_ = true;
			}
		}
	}
	else
		exit_ = true;

}

void Game::update()
{
	interfazManager_->update(); // interfaz
	entityManager_->update(); // laberinto
	characterManager_->update(); // characters
}

void Game::render()
{
	SDL_SetRenderDrawColor(game_->getRenderer(), COLOR(0x00000000));
	SDL_RenderClear(game_->getRenderer());

	fondo->draw();
	entityManager_->draw();
	interfazManager_->draw();
	characterManager_->draw(); //
	c_->draw();

	SDL_RenderPresent(game_->getRenderer());
}

Cursor* Game::createCursor(Vector2D pos, uint width, uint height, Resources::TextureId image)
{
	Cursor* c = static_cast<Cursor*>(entityManager_->addEntity());
	c->init(game_, pos, width, height, image);
	return c;
}
