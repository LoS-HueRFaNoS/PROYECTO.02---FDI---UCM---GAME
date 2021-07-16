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
#include "Components/Rectangle.h"
#include "GameObjects/Cursor.h"
#include "GameObjects/SDL_Objects.h"
#include "ecs/ecs.h"
#include "ecs/Manager.h"

// Nuestro includes
#include "Managers/game/CharacterManager.h"
#include "Managers/game/CombatManager.h"
#include "Managers/game/InterfazManager.h"
#include "Managers/game/AnimationManager.h"
#include "Managers/TheElementalMaze.h"
#include "Managers/SDLGame.h"
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

    // MODO VENTANA // _/!\ NO ALTERAR, POR FAVOR /!\_
    game_ = SDLGame::init("THE ELEMENTAL MAZE", client_width * 0.75, client_height * 0.75);

    // PANTALLA COMPLETA
    game_->setFullScreen(true);

    Texture* tex_ = new Texture(game_->getRenderer(), "project/resources/images/cargando.png");
    SDL_Rect dest = { 0, 0, int(game_->getWindowWidth()), int(game_->getWindowHeight()) };
    SDL_SetRenderDrawColor(game_->getRenderer(), COLOR(0x00000000));
    SDL_RenderClear(game_->getRenderer());
    tex_->render(dest);
    SDL_RenderPresent(game_->getRenderer());

    game_->initResources();
    entityManager_ = new EntityManager(game_);
    game_->getAudioMngr()->setMusicVolume(game_->getAudioMngr()->INITIAL_GAME_VOLUME);
    game_->getAudioMngr()->setChannelVolume(game_->getAudioMngr()->INITIAL_GAME_SOUND);

    fondo = new Fondo(game_, entityManager_);
    fondo->init(Vector2D(), game_->getWindowWidth(), game_->getWindowHeight());

    characterManager_ = new CharacterManager(game_);

    interfazManager_ = new InterfazManager(game_);

    animManager_ = new AnimationManager(game_);

#ifdef DEBUG
    system("cls");
#endif // DEBUG


    gameManager_ = TheElementalMaze::initInstace(game_, entityManager_, characterManager_, interfazManager_, animManager_);

    entityManager_->addEntity(gameManager_);

    c_ = createCursor(Vector2D(game_->getWindowWidth() / 2, game_->getWindowHeight() / 2), 75, 75, Resources::Mouse);

    int endTime = 0;
    delete tex_;
}

void Game::closeGame()
{
    delete entityManager_; entityManager_ = nullptr;
    delete characterManager_; characterManager_ = nullptr;
    delete interfazManager_; interfazManager_ = nullptr;
    delete animManager_; animManager_ = nullptr;
    delete fondo; fondo = nullptr;
    delete c_; c_ = nullptr;
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

void Game::handleInput()
{
    InputHandler* ih = InputHandler::instance();

    if (!ih->update()) exit_ = true;
}

void Game::update()
{
    interfazManager_->update(); // interfaz
    entityManager_->update(); // laberinto
    characterManager_->update(); // characters
    animManager_->update(); //animacion
    c_->update();
}

void Game::render()
{
    SDL_SetRenderDrawColor(game_->getRenderer(), COLOR(0x00000000));
    SDL_RenderClear(game_->getRenderer());

    fondo->draw();
    //interfazManager_->draw();
    gameManager_->draw();
    //entityManager_->draw();
    //characterManager_->draw(); //

    c_->draw();

    SDL_RenderPresent(game_->getRenderer());
}

Cursor* Game::createCursor(Vector2D pos, uint width, uint height, Resources::TextureId image)
{
    Cursor* c = new Cursor(game_, entityManager_);
    c->init(game_, pos, width, height, image);
    return c;
}