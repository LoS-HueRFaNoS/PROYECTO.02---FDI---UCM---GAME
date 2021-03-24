#include "Interfaz.h"
#include "Button.h"
#include "callbacks.h"
#include "SDLGame.h"

void pruebaGame(Game* g) {
	std::cout << "has pulsado este boton" << std::endl;
}
Button* Interfaz::createButton(Panel* p, CallBackOnClick* cb)
{
	SDLGame* game_ = g_->getSDLGame();
	Button* b = static_cast<Button*>(mngr_->addEntity());
	b->init(game_, g_, mngr_, Vector2D(100, 100), 50, 50, Resources::Asteroid);
	b->setCB(cb);
	p->addButton(b);
	return b;
}
void Interfaz::createMovement()
{
	Panel* p = new Panel(Movement);
	allPanels.push_back(p);
	p->addButton(createButton(p, pruebaGame));
	/*p->addButton(mngr_, new Button(game_, g_, mngr_, Vector2D(150, 100), 50, 50, Resources::Asteroid));
	p->addButton(mngr_, new Button(game_, g_, mngr_, Vector2D(200, 100), 50, 50, Resources::Asteroid));
	Button* b = new Button(game_, g_, mngr_, Vector2D(250, 100), 50, 50, Resources::WhiteRect);
	p->addButton(mngr_, b);*/
	//b->setCB(&pruebaGame);
}

Interfaz::Interfaz(Game* juego, EntityManager* manager)
{
	g_ = juego;
	mngr_ = manager;
	createPanel(Movement);
	createPanel(Minimap);
	createPanel(Heroes);
	createPanel(Info);
}

Interfaz::~Interfaz()
{
}

void Interfaz::createPanel(idPanel panelID)
{
	switch (panelID) {
	case Fight:
		createFight();
		break;
	case Movement:
		createMovement();
		break;
	case Minimap:
		createMinimap();
		break;
	case Heroes:
		createHeroes();
		break;
	case Info:
		createInfo();
		break;
	case Inventory:
		createInventory();
		break;
	case HeroesStats:
		createHeroesStats();
		break;
	case BigMap:
		createBigMap();
		break;
	case Turns:
		createTurns();
		break;
	case Settings:
		createSettings();
		break;
	case Chat:
		createChat(); 
		break;
	}
}

void Interfaz::destroyPanel(idPanel panelID)
{
	bool encontrado = false;
	int i = 0;
	while (!encontrado && i < contador) {
		//encontrado = allPanels->GetID() == panelID;
		++i;
	}

	//if (encontrado) delete allPanels[i];
}

