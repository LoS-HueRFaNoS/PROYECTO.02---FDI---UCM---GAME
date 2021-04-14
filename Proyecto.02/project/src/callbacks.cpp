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
#include "CombatManager.h"

void callbacks::infoHeroe01(Interfaz* app) {
	Entity* e = app->getEntity();
	CombatManager* c = GETCMP2(e, CombatManager);
	string name = c->getCharacter(0, HERO)->name();
	std::cout << "heroe 01: " << name << std::endl;
}

void callbacks::infoHeroe02(Interfaz* app) {
	Entity* e = app->getEntity();
	CombatManager* c = GETCMP2(e, CombatManager);
	string name = c->getCharacter(1, HERO)->name();
	std::cout << "heroe 02: " << name << std::endl;
}

void callbacks::infoHeroe03(Interfaz* app) {
	Entity* e = app->getEntity();
	CombatManager* c = GETCMP2(e, CombatManager);
	string name = c->getCharacter(2, HERO)->name();
	std::cout << "heroe 03: " << name << std::endl;
}

void callbacks::infoHeroe04(Interfaz* app) {
	Entity* e = app->getEntity();
	CombatManager* c = GETCMP2(e, CombatManager);
	string name = c->getCharacter(2, HERO)->name();
	std::cout << "heroe 04: " << name << std::endl;
}

#pragma endregion

// ----------------------------------------------------

#pragma region PanelMovimiento
#include "../TheElementalMaze.h"
#include "PlayerMotion.h"

void callbacks::movCommand(int movType)
{
	cout << movType << endl;
}

void callbacks::rotarDerecha(Interfaz* app)
{
	/*Entity* e = app->getEntity();
	GETCMP2(e, PlayerMotion)->rotarDerecha();*/
	TheElementalMaze* maze = static_cast<TheElementalMaze*>(app->getEntity());
	PlayerMotion* c = maze->getPlayerMotion();
	c->rotarDerecha();
}

void callbacks::rotarIzquierda(Interfaz* app)
{
	/*Entity* e = app->getEntity();
	GETCMP2(e, PlayerMotion)->rotarIzquierda();*/
	TheElementalMaze* maze = static_cast<TheElementalMaze*>(app->getEntity());
	PlayerMotion* c = maze->getPlayerMotion();
	c->rotarIzquierda();
}

void callbacks::avanzar(Interfaz* app)
{
	TheElementalMaze* maze = static_cast<TheElementalMaze*>(app->getEntity());
	//Entity* e = maze->getPlayer();
	//PlayerMotion* c = GETCMP2(e, PlayerMotion);
	PlayerMotion* c = maze->getPlayerMotion();
	c->avanzar();
}

void callbacks::interactuar(Interfaz* app)
{
	std::cout << "has interactuado" << std::endl;
}

#pragma endregion

// ----------------------------------------------------

#pragma region PanelInformation

void callbacks::inventario(Interfaz* app)
{
	std::cout << "has abierto el inventario" << std::endl;
}

void callbacks::pocionVida(Interfaz* app)
{
	std::cout << "has usado la poci�n de vida" << std::endl;
}

void callbacks::pocionMana(Interfaz* app)
{
	std::cout << "has usado la poci�n de man�" << std::endl;
}

void callbacks::configuracion(Interfaz* app)
{
	std::cout << "has usado el bot�n de configuraci�n y ayuda" << std::endl;
}

#pragma endregion

// ----------------------------------------------------

#pragma region PanelChatMapa

void callbacks::chat(Interfaz* app)
{
	std::cout << "has usado el bot�n de chat" << std::endl;
}

#pragma endregion

// ----------------------------------------------------

#pragma region PanelCombate

void callbacks::ataqueNormal(Interfaz* app)
{
	std::cout << "ataque cuerpo a cuerpo" << std::endl;
}

void callbacks::ataqueMagico(Interfaz* app)
{
	std::cout << "ataque magico" << std::endl;
}

void callbacks::defensa(Interfaz* app)
{
	std::cout << "te has defendido" << std::endl;
}

void callbacks::huida(Interfaz* app)
{
	std::cout << "escapaste" << std::endl;
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