#pragma once
#include <iostream>

class Game;
using CallBackOnClick = void(Game*);

// MENU
using namespace std;

class callbacks {
public:
	static void pruebaGame(Game* app);
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