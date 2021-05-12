#include "callbacks.h"
#include "Entity.h"
#include "Component.h"
#include <iostream>
#include "Interfaz.h"
#include "ecs.h"

// ----------------------------------------------------

#pragma region PruebasBotones


void callbacks::pruebaGame0(Interfaz* app) {
	std::cout << "pruebaGame0" << std::endl;
}
void callbacks::pruebaGame1(Interfaz* app) {
	std::cout << "pruebaGame1" << std::endl;
}
void callbacks::pruebaGame2(Interfaz* app) {
	std::cout << "pruebaGame2" << std::endl;
}
void callbacks::pruebaGame3(Interfaz* app) {
	std::cout << "pruebaGame3" << std::endl;
}

#pragma endregion

// ----------------------------------------------------

#pragma region PanelHeroes
#include "../TheElementalMaze.h"
#include "CombatManager.h"
#include "Interfaz.h"

void callbacks::heroType(uint numberHeroe) {
	CombatManager* c = GETCMP2(TheElementalMaze::instance(), CombatManager);
	string name = c->getCharacter(numberHeroe, HERO)->name();
	std::cout << "heroe " << numberHeroe << ": " << name << std::endl;
}

void callbacks::createDDPan(bool active, uint numberHeroe) {
	Interfaz* i = GETCMP2(TheElementalMaze::instance(), Interfaz);
	
	if (!active) i->createFichaDD(numberHeroe);
	else if (active) i->removePanel(DDPan);
}

#pragma endregion

// ----------------------------------------------------

#pragma region PanelMovimiento
#include "../TheElementalMaze.h"
#include "PlayerMotion.h"

void callbacks::movCommand(int movType)
{
	PlayerMotion* p = GETCMP2(TheElementalMaze::instance()->getPlayer(), PlayerMotion);

	switch (movType)
	{
	case 0:
		std::cout << "has girado a la derecha" << std::endl;
		p->rotarDerecha();
		break;
	case 1:
		std::cout << "has girado a la izquierda" << std::endl;
		p->rotarIzquierda();
		break;
	case 2:
		std::cout << "has avanzado" << std::endl;
		p->avanzar();
		break;
	case 3:
		std::cout << "has interactuado" << std::endl;
		break;
	default:
		break;
	}
}

#pragma endregion

// ----------------------------------------------------

#pragma region PanelInformation

void callbacks::inventario(Interfaz* app)
{
	//app->createPanel(Inventory);
	std::cout << "has abierto el inventario" << std::endl;
}

void callbacks::configuracion(Interfaz* app)
{
	//app->createPanel(Settings);
	std::cout << "has abierto la configuración" << std::endl;
}

void callbacks::potionType(int potionType_)
{
	switch (potionType_)
	{
	case 0:
		std::cout << "has usado la pocion de vida" << std::endl;
		break;
	case 1:
		std::cout << "has usado la pocion de mana" << std::endl;
		break;
	case 2:
		std::cout << "has usado la pocion de resurreccion" << std::endl;
		break;
	default:
		break;
	}
}

#pragma endregion

// ----------------------------------------------------

#pragma region PanelResources
#include "../TheElementalMaze.h"
#include "Interfaz.h"

void callbacks::createPanel(bool active, int panelType)
{
	Interfaz* i_ = GETCMP2(TheElementalMaze::instance(), Interfaz);

	if (!active) i_->createPanel((idPanel)panelType);
	else if (active) i_->removePanel((idPanel)panelType);
}

#pragma endregion

// ----------------------------------------------------

#pragma region PanelChatMapa

void callbacks::chat(Interfaz* app)
{
	std::cout << "has usado el boton de chat" << std::endl;
}

#pragma endregion

// ----------------------------------------------------

#pragma region PanelCombate
#include "../TheElementalMaze.h"
#include "CombatManager.h"

void callbacks::combatType(int combatType_)
{
	Interfaz* i = GETCMP2(TheElementalMaze::instance(), Interfaz);
	CombatManager* c = GETCMP2(TheElementalMaze::instance(), CombatManager);
	switch (combatType_)
	{
	case 0:
		if (c->getState() == ACTION_PHASE_SPELL) {
			std::cout << "ataque cuerpo a cuerpo" << std::endl;
			callbacks::set_hability(-1);
		}
		else
			std::cout << "ERROR: aun no has comenzado tu turno" << std::endl;
		break;
	case 1:
		if (c->getState() == ACTION_PHASE_SPELL) {
			std::cout << "has seleccionado una habilidad" << std::endl;
			if (!i->getActivePan(Habilities)) callbacks::createPanel(false, Habilities);
			if (i->getEnablePan(Fight)) i->togglePanel(Fight);
		}
		else
			std::cout << "ERROR: aun no has comenzado tu turno" << std::endl;
		break;
	case 2:
		std::cout << "actitud defensiva" << std::endl;
		break;
	case 3:
		std::cout << "huir del combate" << std::endl;
		break;
	default:
		break;
	}
}

void callbacks::addTarget(int objetive_) // -1 para volver atrás
{
	CombatManager* c = GETCMP2(TheElementalMaze::instance(), CombatManager);
	c->sendKeyEvent(objetive_); // sólo uno
	Interfaz* i = GETCMP2(TheElementalMaze::instance(), Interfaz);
	// cambia a combate
	if (i->getActivePan(Targets)) i->removePanel(Targets);
	if (!i->getEnablePan(Fight)) i->togglePanel(Fight);
	std::cout << "has fijado tu objetivo" << std::endl;
}

void callbacks::set_hability(int hability_)
{
	CombatManager* c = GETCMP2(TheElementalMaze::instance(), CombatManager); // falta paso intermedio para guardar la habilidad y seleccionar enemigos
	c->sendKeyEvent(hability_); //indice de la habilidad
	
	Interfaz* i = GETCMP2(TheElementalMaze::instance(), Interfaz);
	if (i->getActivePan(Habilities)) i->removePanel(Habilities);

	// team or single target
	if (c->getState() != END_TURN) {
		// abre panel selecionar objetivo
		callbacks::createPanel(false, Targets);
	}
	else { 
		if (!i->getEnablePan(Fight)) i->togglePanel(Fight); 
	}
}

#pragma endregion

// ----------------------------------------------------
#pragma region MenuPrincipal
void callbacks::startLobby(Interfaz* app)
{
	TheElementalMaze::instance()->changeState(LOBBY);
	app->togglePanel(MenuPrincipal);
	//app->createPanel(Lobby);
	//app->togglePanel(Movement);
	//app->togglePanel(Heroes);
	//app->togglePanel(Info);
	std::cout << "startLobby se ha activado\n";
}
void callbacks::options(Interfaz* app)
{
	app->togglePanel(Options);
	app->togglePanel(MenuPrincipal);
	std::cout << "options se ha activado\n";
}
void callbacks::howToPlay(Interfaz* app)
{
	app->togglePanel(HowToPlay);
	app->togglePanel(MenuPrincipal);
}
void callbacks::quit(Interfaz* app)
{
	
	std::cout << "quit se ha activado\n";
}
#pragma endregion
//void callbacks::start(Game* app) // previo app->setLevel(lvl);
//{
//	/*app->getMachine()->setAction(goGame);
//	app->setLevel(FIRST_LVL);
//	app->setSalida(true);*/
//}
//
//void callbacks::exitGame(Game* app)
//{
//	/*app->getMachine()->setAction(goBack);
//	app->setSalida(true);*/
//}
//
//void callbacks::exitApp(Game* app)
//{
//	/*app->getMachine()->setAction(shutDown);
//	app->setSalida(true);*/
//}
//
//void callbacks::backToMenu(Game* app)
//{
//	/*app->getMachine()->setAction(pauseToMenu);
//	app->setSalida(true);*/
//}
//
//void callbacks::saveOpt(Game* app)
//{
//	/*app->getMachine()->setAction(saveOption);
//	MenuState* menu = static_cast<MenuState*>(app->getMachine()->currentState());
//	MenuButton* mb = menu->engine->getActual();
//	mb->setHidden(true);
//	menuState ms = mb->getMenuState();
//	menu->engine->setState(ms);
//	static_cast<PauseState*>(menu)->clearUserOpt();*/
//}
//
//void callbacks::save(Game* app)
//{
//	/*app->getMachine()->setAction(saveCurrent);
//	app->setSalida(true);*/
//}
//
//void callbacks::load(Game* app)
//{
//	/*app->getMachine()->setAction(loadOption);
//	app->setSalida(true);*/
//}
//
//void callbacks::change(Game* app)
//{
//	/*MenuState* menu = static_cast<MenuState*>(app->getMachine()->currentState());
//	MenuButton* mb = menu->engine->getActual();
//	menuState ms = mb->getMenuState();
//	menu->engine->setState(ms);
//	menu->setRdy(false);*/
//}
//
//void callbacks::startLvl(Game* app)
//{
//	/*MenuState* menu = static_cast<MenuState*>(app->getMachine()->currentState());
//	uint n = menu->engine->getActual()->getLvl();
//	app->getMachine()->setAction(goGame);
//	app->setLevel(n);
//	app->setSalida(true);*/
//}
//
//// IN-GAME
//void callbacks::game_over(Game* app)
//{
//	/*app->getMachine()->setAction(goGameOver);
//	app->setSalida(true);*/
//}
//
//void callbacks::lose_life(Game* app)
//{
//	/*app->getMachine()->setAction(goLoseLife);
//	app->setSalida(true);*/
//}
//
//void callbacks::stage_complete(Game* app)
//{
//	/*app->getMachine()->setAction(goStageClear);
//	app->setSalida(true);*/
//}
//
//void callbacks::game_complete(Game* app)
//{
//	/*app->getMachine()->setAction(goGameClear);
//	app->setSalida(true);*/
//}