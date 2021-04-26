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


TheElementalMaze* TheElementalMaze::instance_ = nullptr;

TheElementalMaze::~TheElementalMaze()
{
	delete itemManager_;
	itemManager_ = nullptr;
	delete partyManager_;
	partyManager_ = nullptr;
}

void TheElementalMaze::init()
{
	// 1. Laberinto
	laberinto_ = this->addComponent<Laberinto>(10, 10);
	laberinto_->createRandomMaze(Vector2D(0, 0));

	// 2. Player
	player_ = mngr_->addEntity(); // lo primero en crearse deber�a ser el player �?
	player_->addComponent<MazePos>(Vector2D(0, 0));
	player_->addComponent<PlayerMotion>(SDLK_UP, SDLK_LEFT, SDLK_RIGHT, laberinto_);
	player_->addComponent<PlayerViewer>(laberinto_);

	// 3. Personajes
	itemManager_ = new ItemManager();

	combatManager_ = addComponent<CombatManager>();

	partyManager_ = new PartyManager();

	Hero* wizard = characterManager_->addHeroFromTemplate(WIZARD);
	Hero* warrior = characterManager_->addHeroFromTemplate(WARRIOR);
	Hero* rogue = characterManager_->addHeroFromTemplate(ROGUE);
	Hero* cleric = characterManager_->addHeroFromTemplate(CLERIC);;

	wizard->addHability<Fireball>();
	wizard->addHability<SingleTargetAttackExample>();
	wizard->addHability<SelfHealExample>();
	wizard->addHability<AllyTeamAttackExample>();

	warrior->addHability<SingleTargetAttackExample>();
	warrior->addHability<AllyTeamAttackExample>();

	rogue->addHability<SingleTargetAttackExample>();
	rogue->addHability<AllyTeamAttackExample>();

	cleric->addHability<SingleTargetHealxample>();
	cleric->addHability<SelfHealExample>();
	cleric->addHability<AllyTeamHealExample>();
	cleric->addHability<AllyTeamAttackExample>();

	partyManager_->addHero(wizard);
	partyManager_->addHero(warrior);
	partyManager_->addHero(rogue);
	partyManager_->addHero(cleric);

	cout << "Characters Loaded" << endl;

	// 4. Interfaz
	uiManager_ = addComponent<Interfaz>(iManager_);

	changeState(EXPLORING);
}

void TheElementalMaze::onStateChanged()
{
	switch (state_)
	{
	case COMBAT:
		combatManager_->addHeroesTeam(partyManager_->getHeroes());
		combatManager_->startCombat();
		break;
	case EXPLORING:
		cout << "EXPLORING STARTED" << endl;
		laberinto_->getCasillaInfo(player_->getComponent<MazePos>(ecs::MazePos)->getPos().getX(), player_->getComponent<MazePos>(ecs::MazePos)->getPos().getY())->getEnemy()->clear();
		break;
	case LOBBY:
		cout << "LOBBY REACHED" << endl;
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
