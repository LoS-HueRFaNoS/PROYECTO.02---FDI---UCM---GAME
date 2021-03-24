#include "Interfaz.h"
#include "Button.h"
#include "SDLGame.h"
#include "callbacks.h"

Button* Interfaz::createButton(Panel* p, CallBackOnClick* cb, Vector2D pos, uint width, uint height, Resources::TextureId image)
{
	SDLGame* game_ = g_->getSDLGame();
	Button* b = static_cast<Button*>(mngr_->addEntity());
	b->init(game_, g_, mngr_, pos, width, height, image);
	b->setCB(cb);
	p->addButton(b);
	return b;
}

void Interfaz::createMovement()
{
	Panel* p = new Panel(Movement);
	allPanels.push_back(p);
	p->addButton(createButton(p, callbacks::pruebaGame, Vector2D(100, 100), 50, 50, Resources::Asteroid));
	p->addButton(createButton(p, callbacks::pruebaGame, Vector2D(150, 100), 50, 50, Resources::Asteroid));
	p->addButton(createButton(p, callbacks::pruebaGame, Vector2D(200, 100), 50, 50, Resources::Asteroid));
	p->addButton(createButton(p, callbacks::pruebaGame, Vector2D(250, 100), 50, 50, Resources::Asteroid));
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

