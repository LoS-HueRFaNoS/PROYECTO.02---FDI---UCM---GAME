#include "TheElementalMaze.h"

void TheElementalMaze::init()
{
	// 1. Laberinto
	laberintoE_ = mngr_->addEntity();
	laberintoC_ = laberintoE_->addComponent<Laberinto>(10,10); // esto es redundante ._.
	laberintoC_->createRandomMaze(Vector2D(0, 0));

	// 2. Player
	player_ = mngr_->addEntity(); // lo primero en crearse deber�a ser el player �?
	player_->addComponent<MazePos>(Vector2D(0, 0));
	playerMotion_ = player_->addComponent<PlayerMotion>(SDLK_UP, SDLK_LEFT, SDLK_RIGHT, laberintoC_);
	player_->addComponent<PlayerViewer>(laberintoC_);

	// 3. Interfaz
	uiManager_ = addComponent<Interfaz>(iManager_);

	// 4. Personajes

	characterManager_->setElementalMaze(this);

	itemManager_ = new ItemManager();

	combatManager_ = addComponent<CombatManager>(); // al seguir por consola, bloquea el juego y faltan cosas que me he dejado

	Hero* wizard = characterManager_->addHeroFromTemplate(WIZARD);
	Hero* warrior = characterManager_->addHeroFromTemplate(WARRIOR);
	Hero* rogue = characterManager_->addHeroFromTemplate(ROGUE);
	Hero* cleric = characterManager_->addHeroFromTemplate(CLERIC);;

	Enemy* e1 = characterManager_->addRandomEnemy();
	Enemy* e2 = characterManager_->addRandomEnemy();
	Enemy* e3 = characterManager_->addRandomEnemy();

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
	combatManager_->addCharacter(e1);
	combatManager_->addCharacter(e2);
	combatManager_->addCharacter(e3);

	//combatManager_->startCombat();


	cout << "Characters Loaded" << endl;

}
