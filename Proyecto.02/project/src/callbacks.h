class Game;
// MENU
static void start(Game* app) // previo app->setLevel(lvl);
{
	/*app->getMachine()->setAction(goGame);
	app->setLevel(FIRST_LVL);
	app->setSalida(true);*/
}

static void exit(Game* app)
{
	/*app->getMachine()->setAction(goBack);
	app->setSalida(true);*/
}

static void exitApp(Game* app)
{
	/*app->getMachine()->setAction(shutDown);
	app->setSalida(true);*/
}

static void backToMenu(Game* app)
{
	/*app->getMachine()->setAction(pauseToMenu);
	app->setSalida(true);*/
}

static void saveOpt(Game* app)
{
	/*app->getMachine()->setAction(saveOption);
	MenuState* menu = static_cast<MenuState*>(app->getMachine()->currentState());
	MenuButton* mb = menu->engine->getActual();
	mb->setHidden(true);
	menuState ms = mb->getMenuState();
	menu->engine->setState(ms);
	static_cast<PauseState*>(menu)->clearUserOpt();*/
}

static void save(Game* app)
{
	/*app->getMachine()->setAction(saveCurrent);
	app->setSalida(true);*/
}

static void load(Game* app)
{
	/*app->getMachine()->setAction(loadOption);
	app->setSalida(true);*/
}

static void change(Game* app)
{
	/*MenuState* menu = static_cast<MenuState*>(app->getMachine()->currentState());
	MenuButton* mb = menu->engine->getActual();
	menuState ms = mb->getMenuState();
	menu->engine->setState(ms);
	menu->setRdy(false);*/
}

static void startLvl(Game* app)
{
	/*MenuState* menu = static_cast<MenuState*>(app->getMachine()->currentState());
	uint n = menu->engine->getActual()->getLvl();
	app->getMachine()->setAction(goGame);
	app->setLevel(n);
	app->setSalida(true);*/
}

// IN-GAME
static void game_over(Game* app)
{
	/*app->getMachine()->setAction(goGameOver);
	app->setSalida(true);*/
}

static void lose_life(Game* app)
{ 
	/*app->getMachine()->setAction(goLoseLife);
	app->setSalida(true);*/
}

static void stage_complete(Game* app)
{
	/*app->getMachine()->setAction(goStageClear);
	app->setSalida(true);*/
}

static void game_complete(Game* app)
{
	/*app->getMachine()->setAction(goGameClear);
	app->setSalida(true);*/
}

/*const enum action { gogame, gomenu, gopause, goback, pausetomenu, shutdown, saveoption, savecurrent, loadoption, gostageclear, goloselife, gogameover, gogameclear };

void game::chain()	// siempre empieza en el menu
{
	menustate* menu;
	playstate* play;
	action a = gamest->getaction();
	switch (a) {
	case gogame:
		if (lvl >= 1 && lvl <= 5)
			gamest->changestate(new playstate(this, lvl));
		else {
			exit = false;
			static_cast<mainmenustate*>(getmachine()->currentstate())->setwrong(true);
		}
		break;
	case gomenu:
		gamest->changestate(new mainmenustate(this));
		break;
	case gopause:
		gamest->pushstate(new pausestate(this));
		break;
	case goback:
		gamest->popstate();
		break;
	case pausetomenu:
		gamest->popstate();
		gamest->changestate(new mainmenustate(this));
		break;
	case savecurrent:
		if (savetofile()) {
			gamest->pushstate(new pausestate(this));
			static_cast<pausestate*>(gamest->currentstate())->setwrong(false);
		}
		break;
	case loadoption:
		play = loadgame();
		gamest->changestate(play);
		break;
	case gostageclear:
		gamest->pushstate(new pausestate(this));
		menu = static_cast<menustate*>(gamest->currentstate());
		menu->getmachine()->setstate(stageclear);
		menu->setrdy(false);
		break;
	case goloselife:
		gamest->pushstate(new pausestate(this));
		menu = static_cast<menustate*>(gamest->currentstate());
		menu->getmachine()->setstate(lifeless);
		menu->setrdy(false);
		break;
	case gogameover:
		gamest->pushstate(new pausestate(this));
		menu = static_cast<menustate*>(gamest->currentstate());
		menu->getmachine()->setstate(gameover);
		menu->setrdy(false);
		break;
	case gogameclear:
		gamest->pushstate(new pausestate(this));
		menu = static_cast<menustate*>(gamest->currentstate());
		menu->getmachine()->setstate(gameclear);
		menu->setrdy(false);
		break;
	case shutdown:
		gamest->popstate();
		break;
	}
	if (a != shutdown) setsalida(false);
	gamest->desactivate();
}*/