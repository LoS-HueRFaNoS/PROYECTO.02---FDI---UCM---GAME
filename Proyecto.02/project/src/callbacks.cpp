#include "callbacks.h"
#include "MazePos.h"
#include "Entity.h"

void callbacks::pruebaGame0(Game* app) {
	std::cout << "pruebaGame0" << std::endl;
}
void callbacks::pruebaGame1(Game* app) {
	std::cout << "pruebaGame1" << std::endl;
}
void callbacks::pruebaGame2(Game* app) {
	std::cout << "pruebaGame2" << std::endl;
}
void callbacks::pruebaGame3(Game* app) {
	std::cout << "pruebaGame3" << std::endl;
}

void callbacks::interactuar(Game* app)
{
	std::cout << "has interactuado" << std::endl;
}

void callbacks::inventario(Game* app)
{
	std::cout << "has abierto el inventario" << std::endl;
}

void callbacks::pocionVida(Game* app)
{
	std::cout << "has usado la poción de vida" << std::endl;
}

void callbacks::pocionMana(Game* app)
{
	std::cout << "has usado la poción de maná" << std::endl;
}

void callbacks::chat(Game* app)
{
	std::cout << "has usado el botón de chat" << std::endl;
}

void callbacks::configuracion(Game* app)
{
	std::cout << "has usado el botón de configuración y ayuda" << std::endl;
}

void callbacks::ataqueNormal(Game* app)
{
	std::cout << "ataque cuerpo a cuerpo" << std::endl;
}

void callbacks::ataqueMagico(Game* app)
{
	std::cout << "ataque magico" << std::endl;
}

void callbacks::defensa(Game* app)
{
	std::cout << "te has defendido" << std::endl;
}

void callbacks::huida(Game* app)
{
	std::cout << "escapaste" << std::endl;
}
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