#pragma once

class Interfaz;

// MENU
using namespace std;

class callbacks {
public:
	// pruebas (solo escriben por consola)
	static void pruebaGame0(Interfaz* app);
	static void pruebaGame1(Interfaz* app);
	static void pruebaGame2(Interfaz* app);
	static void pruebaGame3(Interfaz* app);
	// acceso a heroes
	static void infoHeroe01(Interfaz* app);
	static void infoHeroe02(Interfaz* app);
	static void infoHeroe03(Interfaz* app);
	static void infoHeroe04(Interfaz* app);
	// acceso a movimiento
	static void movCommand(int movType);
	static void rotarDerecha(Interfaz* app);
	static void rotarIzquierda(Interfaz* app);
	static void avanzar(Interfaz* app);
	static void interactuar(Interfaz* app);
	// acceso a informacion
	static void inventario(Interfaz* app);
	static void pocionVida(Interfaz* app);
	static void pocionMana(Interfaz* app);
	static void chat(Interfaz* app);
	static void configuracion(Interfaz* app);
	// acceso a combate
	static void ataqueNormal(Interfaz* app);
	static void ataqueMagico(Interfaz* app);
	static void defensa(Interfaz* app);
	static void huida(Interfaz* app);
};

//const enum action { gogame, gomenu, gopause, goback, pausetomenu, shutdown, saveoption, savecurrent, loadoption, gostageclear, goloselife, gogameover, gogameclear };
//
//void game::chain()	// siempre empieza en el menu
//{
//	menustate* menu;
//	playstate* play;
//	action a = gamest->getaction();
//	switch (a) {
//	case gogame:
//		if (lvl >= 1 && lvl <= 5)
//			gamest->changestate(new playstate(this, lvl));
//		else {
//			exit = false;
//			static_cast<mainmenustate*>(getmachine()->currentstate())->setwrong(true);
//		}
//		break;
//	case gomenu:
//		gamest->changestate(new mainmenustate(this));
//		break;
//	case gopause:
//		gamest->pushstate(new pausestate(this));
//		break;
//	case goback:
//		gamest->popstate();
//		break;
//	case pausetomenu:
//		gamest->popstate();
//		gamest->changestate(new mainmenustate(this));
//		break;
//	case savecurrent:
//		if (savetofile()) {
//			gamest->pushstate(new pausestate(this));
//			static_cast<pausestate*>(gamest->currentstate())->setwrong(false);
//		}
//		break;
//	case loadoption:
//		play = loadgame();
//		gamest->changestate(play);
//		break;
//	case gostageclear:
//		gamest->pushstate(new pausestate(this));
//		menu = static_cast<menustate*>(gamest->currentstate());
//		menu->getmachine()->setstate(stageclear);
//		menu->setrdy(false);
//		break;
//	case goloselife:
//		gamest->pushstate(new pausestate(this));
//		menu = static_cast<menustate*>(gamest->currentstate());
//		menu->getmachine()->setstate(lifeless);
//		menu->setrdy(false);
//		break;
//	case gogameover:
//		gamest->pushstate(new pausestate(this));
//		menu = static_cast<menustate*>(gamest->currentstate());
//		menu->getmachine()->setstate(gameover);
//		menu->setrdy(false);
//		break;
//	case gogameclear:
//		gamest->pushstate(new pausestate(this));
//		menu = static_cast<menustate*>(gamest->currentstate());
//		menu->getmachine()->setstate(gameclear);
//		menu->setrdy(false);
//		break;
//	case shutdown:
//		gamest->popstate();
//		break;
//	}
//	if (a != shutdown) setsalida(false);
//	gamest->desactivate();
//}