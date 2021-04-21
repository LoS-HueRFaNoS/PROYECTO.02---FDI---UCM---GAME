#include "TheElementalMaze.h"
#include "src/CombatManager.h"
#include "src/CharacterManager.h"
#include "src/Interfaz.h"
#include "src/Laberinto.h"
#include "src/PlayerMotion.h"
#include "src/PlayerViewer.h"
#include "src/ItemManager.h"


TheElementalMaze* TheElementalMaze::instance_ = nullptr;

TheElementalMaze::~TheElementalMaze()
{
	delete itemManager_;
	itemManager_ = nullptr;
}

void TheElementalMaze::init()
{
	// 1. Laberinto
	laberinto_ = mngr_->addEntity();
	Laberinto* lab = laberinto_->addComponent<Laberinto>(10, 10);
	lab->createRandomMaze(Vector2D(0, 0));

	// 2. Player
	player_ = mngr_->addEntity(); // lo primero en crearse deber�a ser el player �?
	player_->addComponent<MazePos>(Vector2D(0, 0));
	player_->addComponent<PlayerMotion>(SDLK_UP, SDLK_LEFT, SDLK_RIGHT, lab);
	player_->addComponent<PlayerViewer>(lab);

	// 3. Personajes
	itemManager_ = new ItemManager();

	combatManager_ = addComponent<CombatManager>(); // al seguir por consola, bloquea el juego y faltan cosas que me he dejado

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

	combatManager_->addCharacter(wizard);
	combatManager_->addCharacter(warrior);
	combatManager_->addCharacter(rogue);
	combatManager_->addCharacter(cleric);

	int enemies = rpgLogic::throwDice(1, 3);

	for (int i = 0 ;i < enemies; i++)
		combatManager_->addCharacter(characterManager_->addRandomEnemy());


	combatManager_->startCombat();


	cout << "Characters Loaded" << endl;

	// 4. Interfaz
	uiManager_ = addComponent<Interfaz>(iManager_);

}
