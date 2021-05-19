#include "TheElementalMaze.h"
#include "../Managers/game/CombatManager.h"
#include "../Managers/game/CharacterManager.h"
#include "../Managers/game/PartyManager.h"
#include "../Managers/game/LobbyManager.h"
#include "../Managers/game/ItemManager.h"
#include "../Managers/game/HabilityManager.h"
#include "../Components/GameStateManager.h"
#include "../Components/Interfaz.h"
#include "../Components/Laberinto.h"
#include "../Components/PlayerMotion.h"
#include "../Components/PlayerViewer.h"
#include "../Components/Image.h"

TheElementalMaze* TheElementalMaze::instance_ = nullptr;

TheElementalMaze::~TheElementalMaze()
{
	delete itemManager_;
	itemManager_ = nullptr;
	delete partyManager_;
	partyManager_ = nullptr;
	delete lobbyManager_;
	lobbyManager_ = nullptr;
}

void TheElementalMaze::init()
{
	// 3. Personajes
	
	itemManager_ = new ItemManager();

	HabilityManager::Init();
	
	partyManager_ = new PartyManager();

	lobbyManager_ = new LobbyManager(partyManager_);
	
	combatManager_ = addComponent<CombatManager>();

	Hero* wizard = characterManager_->addHeroFromTemplate(heroTem::WIZARD);
	Hero* warrior = characterManager_->addHeroFromTemplate(heroTem::WARRIOR);
	Hero* rogue = characterManager_->addHeroFromTemplate(heroTem::ROGUE);
	Hero* cleric = characterManager_->addHeroFromTemplate(heroTem::CLERIC);;

	partyManager_->addHero(wizard);
	partyManager_->addHero(warrior);
	partyManager_->addHero(rogue);
	partyManager_->addHero(cleric);

	partyManager_->addItem(itemManager_->getRandomWeapon(), 0);

	// 4. Interfaz
	uiManager_ = addComponent<Interfaz>(iManager_);

	// 5. GameStateManager
	stManager_ = addComponent<GameStateManager>();
	stManager_->changeState(GameState::MainMenu);
}

//--------------------------------------------------------

void TheElementalMaze::startExploring()
{
	lobbyManager_->startExploring();
}

void TheElementalMaze::createLaberinto()
{
	// 1. Laberinto
	lab_ = mngr_->addEntity();
	laberinto_ = lab_->addComponent<Laberinto>(10, 10);
	laberinto_->createRandomMaze(Vector2D(0, 0));

	// 2. Player
	player_ = mngr_->addEntity();
	player_->addComponent<MazePos>(Vector2D(0, 0));
	player_->addComponent<PlayerViewer>(laberinto_);
	player_->addComponent<PlayerMotion>(SDLK_UP, SDLK_LEFT, SDLK_RIGHT, laberinto_);
}

void TheElementalMaze::backFromDungeon()
{
	lobbyManager_->backFromDungeon();
}

void TheElementalMaze::checkOutNoInitialEnemy()
{
	laberinto_->getCasillaInfo(int(player_->getComponent<MazePos>(ecs::MazePos)->getPos().getX()), int(player_->getComponent<MazePos>(ecs::MazePos)->getPos().getY()))->getEnemy()->clear();
}

void TheElementalMaze::startCombat()
{
	combatManager_->addHeroesTeam(partyManager_->getHeroes());
	combatManager_->startCombat();
}

void TheElementalMaze::onExitLaberinto()
{
	lab_->disable();
	player_->disable();
	player_ = nullptr;
}

//--------------------------------------------------------

GameState TheElementalMaze::gameState()
{
	return stManager_->gameState();
}

void TheElementalMaze::changeState(GameState state)
{
	stManager_->changeState(state);
}
