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

void callbacks::heroType(int numberHeroe) {
	CombatManager* c = GETCMP2(TheElementalMaze::instance(), CombatManager);
	string name = c->getCharacter(numberHeroe, HERO)->name();
	std::cout << "heroe " << numberHeroe << ": " << name << std::endl;
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
	std::cout << "has abierto el inventario" << std::endl;
}

void callbacks::configuracion(Interfaz* app)
{

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

void callbacks::attackType(int attackType_)
{
	CombatManager* c = GETCMP2(TheElementalMaze::instance(), CombatManager);
	switch (attackType_)
	{
	case 0:
		std::cout << "ataque cuerpo a cuerpo" << std::endl;
		break;
	case 1:
		std::cout << "ataque magico" << std::endl;
		break;
	default:
		break;
	}
}

void callbacks::defendType(int attackType_)
{
	CombatManager* c = GETCMP2(TheElementalMaze::instance(), CombatManager);
	switch (attackType_)
	{
	case 0:
		//c->defend();
		std::cout << "te has defendido" << std::endl;
		break;
	case 1:
		//c->escape();
		std::cout << "escapaste" << std::endl;
		break;
	default:
		break;
	}
}

void callbacks::addTarget(int attackType_)
{

}

void callbacks::s_cast_hability(int attackType_)
{

}

#pragma endregion

// ----------------------------------------------------

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