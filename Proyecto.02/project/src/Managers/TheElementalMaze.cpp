#include "TheElementalMaze.h"
#include "../Managers/game/CombatManager.h"
#include "../Managers/game/CharacterManager.h"
#include "../Managers/game/PartyManager.h"
#include "../Managers/game/LobbyManager.h"
#include "../Managers/game/ItemManager.h"
#include "../Managers/game/HabilityManager.h"
#include "../Managers/game/ChatManager.h"
#include "../Components/GameStateManager.h"
#include "../Components/Tutorial.h"
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
	Hero* cleric = characterManager_->addHeroFromTemplate(heroTem::CLERIC);

	partyManager_->addHero(wizard);
	partyManager_->addHero(warrior);
	partyManager_->addHero(rogue);
	partyManager_->addHero(cleric);

	// 4. Interfaz
	uiManager_ = addComponent<Interfaz>(iManager_);

	// 5. GameStateManager
	stManager_ = addComponent<GameStateManager>();
	stManager_->changeState(GameState::MainMenu);
	TheElementalMaze::instance()->getSDLGame()->getAudioMngr()->playMusic(Resources::AudioId::MenuInicial, -1);

	// 6. Tutorial
	tutorial_ = addComponent<TutorialManager>(iManager_);
}

//--------------------------------------------------------

void TheElementalMaze::startExploring()
{
	lobbyManager_->startExploring();
}

void TheElementalMaze::createLaberinto()
{
	//lab_->removeComponent(ecs::Laberinto);
	/*laberinto_->createRandomMaze(Vector2D(0, 0));
	MazePos* mPos = GETCMP2(player_, MazePos);
	mPos->reset();
	mPos = nullptr;*/

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
void TheElementalMaze::firstLobby()
{
	lobbyManager_->firstLobby();
	firstLobbyCreated = true;
}
void TheElementalMaze::checkOutNoInitialEnemy()
{
	laberinto_->getCasillaInfo(int(player_->getComponent<MazePos>(ecs::MazePos)->getPos().getX()), int(player_->getComponent<MazePos>(ecs::MazePos)->getPos().getY()))->getEnemy()->clear();
}

void TheElementalMaze::startCombat()
{
	std::vector<Hero*> heroes_ = std::vector<Hero*>();
	for (Hero* h : partyManager_->getHeroes()) {
		if (h)
			heroes_.push_back(h);
	}
	combatManager_->addHeroesTeam(heroes_);
	combatManager_->startCombat();
}

void TheElementalMaze::onExitLaberinto()
{
	lab_->disable();
	player_->disable();
	player_ = nullptr;
	lab_ = nullptr;
}

//--------------------------------------------------------

GameState TheElementalMaze::gameState()
{
	return stManager_->gameState();
}

void TheElementalMaze::changeState(GameState state)
{
	stManager_->changeState(state);

	if (state == GameState::END_EXPLORING)
		nextLevel();
}

void TheElementalMaze::sendMsg(Message m)
{
	tutorial_->send(m);
}
