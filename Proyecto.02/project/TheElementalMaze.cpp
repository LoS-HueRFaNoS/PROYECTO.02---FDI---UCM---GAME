#include "TheElementalMaze.h"

void TheElementalMaze::init(SDLGame* game, EntityManager* mngr)
{
	// 1. Laberinto
	laberinto = mngr->addEntity();
	lab = laberinto->addComponent<Laberinto>(mngr); // esto es redundante ._.
	lab->initFromFile();

	// 2. Player
	player = mngr->addEntity(); // lo primero en crearse debería ser el player ¿?
	player->addComponent<MazePos>(Vector2D(0, 0));
	plmot = player->addComponent<PlayerMotion>(SDLK_UP, SDLK_LEFT, SDLK_RIGHT, lab);
	player->addComponent<PlayerViewer>(lab);

	// 3. Interfaz
	F = addComponent<InterfazManager>();

	// 4. Personajes
	//cm = addComponent<CombatManager>(); // al seguir por consola, bloquea el juego y faltan cosas que me he dejado

	/*Hero* wizard = new Hero(game_, mngr);
	Hero* warrior = new Hero(game_, mngr);
	Hero* rogue = new Hero(game_, mngr);
	Hero* cleric = new Hero(game_, mngr);
	Enemy* e1 = new Enemy(game_, mngr);
	Enemy* e2 = new Enemy(game_, mngr);
	Enemy* e3 = new Enemy(game_, mngr);

	wizard->loadFromTemplate(rpgLogic::WIZARD);
	warrior->loadFromTemplate(rpgLogic::WARRIOR);
	rogue->loadFromTemplate(rpgLogic::ROGUE);
	cleric->loadFromTemplate(rpgLogic::CLERIC);
	e1->loadFromTemplate(rpgLogic::ZOMBIE);
	e2->loadFromTemplate(rpgLogic::ZOMBIE);
	e3->loadFromTemplate(rpgLogic::ZOMBIE);

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

	cm->addCharacter(wizard);
	cm->addCharacter(warrior);
	cm->addCharacter(rogue);
	cm->addCharacter(cleric);
	cm->addCharacter(e1);
	cm->addCharacter(e2);
	cm->addCharacter(e3);

	cm->startCombat();

	cout << "Characters Loaded" << endl;*/
	
}
