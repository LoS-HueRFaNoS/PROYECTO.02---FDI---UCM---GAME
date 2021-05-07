#include "TheElementalMaze.h"
#include "src/CombatManager.h"
#include "src/CharacterManager.h"
#include "src/Interfaz.h"
#include "src/Laberinto.h"
#include "src/PlayerMotion.h"
#include "src/PlayerViewer.h"
#include "src/ItemManager.h"
#include "src/Image.h"
#include "src/PartyManager.h"
#include "src/LobbyManager.h"

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

	Hero* wizard = characterManager_->addHeroFromTemplate(WIZARD);
	Hero* warrior = characterManager_->addHeroFromTemplate(WARRIOR);
	Hero* rogue = characterManager_->addHeroFromTemplate(ROGUE);
	Hero* cleric = characterManager_->addHeroFromTemplate(CLERIC);;

	wizard->addHability(FIREBALL);
	wizard->addHability<SingleTargetAttackExample>();
	wizard->addHability(SELFHEALEXAMPLE);
	wizard->addHability<AllyTeamAttackExample>();

	warrior->addHability(SINGLETARGETATTACKEXAMPLE);
	warrior->addHability<AllyTeamAttackExample>();

	rogue->addHability(SINGLETARGETATTACKEXAMPLE);
	rogue->addHability<AllyTeamAttackExample>();

	cleric->addHability(SINGLETARGETHEALXAMPLE);
	cleric->addHability<SelfHealExample>();
	cleric->addHability<AllyTeamHealExample>();
	cleric->addHability(ALLYTEAMATTACKEXAMPLE);

	partyManager_->addHero(wizard);
	partyManager_->addHero(warrior);
	partyManager_->addHero(rogue);
	partyManager_->addHero(cleric);

	cout << "Characters Loaded" << endl;

	// 4. Interfaz
	uiManager_ = addComponent<Interfaz>(iManager_);

	changeState(LOBBY);
}

void TheElementalMaze::onStateChanged()
{

	switch (state_)
	{
	case LOBBY:
		cout << "LOBBY REACHED" << endl;
		lobbyManager_->backFromDungeon();
		break;
	case START_EXPLORING:
		cout << "EXPLORATION STARTED" << endl;
		// 1. Laberinto
		laberinto_ = addComponent<Laberinto>(10, 10);
		laberinto_->createRandomMaze(Vector2D(0, 0));

		// 2. Player
		player_ = mngr_->addEntity(); // lo primero en crearse deber�a ser el player �?
		player_->addComponent<MazePos>(Vector2D(0, 0));
		player_->addComponent<PlayerMotion>(SDLK_UP, SDLK_LEFT, SDLK_RIGHT, laberinto_);
		player_->addComponent<PlayerViewer>(laberinto_);
		changeState(EXPLORING);
		break;
	case EXPLORING:
		cout << "EXPLORING STARTED" << endl;
		laberinto_->getCasillaInfo(player_->getComponent<MazePos>(ecs::MazePos)->getPos().getX(), player_->getComponent<MazePos>(ecs::MazePos)->getPos().getY())->getEnemy()->clear();
		break;
	case COMBAT:
		combatManager_->addHeroesTeam(partyManager_->getHeroes());
		combatManager_->startCombat();
		break;
	case END_EXPLORING:
		removeComponent(ecs::Laberinto);
		delete player_;
		break;
	default:
		break;
	}
}


void TheElementalMaze::changeState(GameState state)
{
	if (state_ != state) {
		state_ = state;
		onStateChanged();
	}
}
