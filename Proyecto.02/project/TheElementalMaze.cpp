#include "TheElementalMaze.h"

void TheElementalMaze::init(jv enJs, jv heJs)
{
	// 1. Laberinto
	laberinto = mngr_->addEntity();
	lab = laberinto->addComponent<Laberinto>(mngr_); // esto es redundante ._.
	lab->initFromFile();

	// 2. Player
	player = mngr_->addEntity(); // lo primero en crearse debería ser el player ¿?
	player->addComponent<MazePos>(Vector2D(0, 0));
	plmot = player->addComponent<PlayerMotion>(SDLK_UP, SDLK_LEFT, SDLK_RIGHT, lab);
	player->addComponent<PlayerViewer>(lab);

	// 3. Interfaz
	F = addComponent<InterfazManager>();

	// 4. Personajes
	cm = addComponent<CombatManager>(); // al seguir por consola, bloquea el juego y faltan cosas que me he dejado

	Hero* wizard = new Hero(game_, mngr_);
	Hero* warrior = new Hero(game_, mngr_);
	Hero* rogue = new Hero(game_, mngr_);
	Hero* cleric = new Hero(game_, mngr_);
	Enemy* e1 = new Enemy(game_, mngr_);
	Enemy* e2 = new Enemy(game_, mngr_);
	Enemy* e3 = new Enemy(game_, mngr_);

	/* loadFromTemplate(jute::jValue v, heroTemplate t)
	* requiere de jValue y template, pero estaba puesto sólo con el template.
	* Para solucionar esto sin tocar mucho he añadido un getter pero no funciona bien.
	* Los jValue los guarda CharacterManager pero este se crea en Game.cpp
	* 
	*/

	/*wizard->loadFromTemplate(heroJson, rpgLogic::WIZARD);
	warrior->loadFromTemplate(heroJson, rpgLogic::WARRIOR);
	rogue->loadFromTemplate(heroJson, rpgLogic::ROGUE);
	cleric->loadFromTemplate(heroJson, rpgLogic::CLERIC);
	e1->loadFromTemplate(enemyJson, rpgLogic::ZOMBIE);
	e2->loadFromTemplate(enemyJson, rpgLogic::ZOMBIE);
	e3->loadFromTemplate(enemyJson, rpgLogic::ZOMBIE);*/

	/*wizard->addHability<Fireball>();
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
	cleric->addHability<AllyTeamAttackExample>();*/

	cm->addCharacter(wizard);
	cm->addCharacter(warrior);
	cm->addCharacter(rogue);
	cm->addCharacter(cleric);
	cm->addCharacter(e1);
	cm->addCharacter(e2);
	cm->addCharacter(e3);

	//cm->startCombat();

	cout << "Characters Loaded" << endl;
	
}
