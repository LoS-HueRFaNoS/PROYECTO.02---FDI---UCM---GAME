#include "Interfaz.h"
#include "Button.h"
#include "SDLGame.h"
#include "callbacks.h"

Cursor* Interfaz::createCursor(Vector2D pos, uint width, uint height, Resources::TextureId image)
{
	SDLGame* game_ = g_->getSDLGame();
	Cursor* c = static_cast<Cursor*>(mngr_->addEntity());
	c->init(game_, g_, pos, width, height, image);
	return c;
}

Button* Interfaz::createButton(Panel* p, CallBackOnClick* cb, Vector2D pos, uint width, uint height, Resources::TextureId image)
{
	SDLGame* game_ = g_->getSDLGame();
	Button* b = static_cast<Button*>(mngr_->addEntity());
	b->init(game_, g_, pos, width, height, image);
	b->setCB(cb);
	p->addButton(b);
	return b;
}

void Interfaz::createFight()
{
	Panel* p = new Panel(Fight);
	allPanels.push_back(p);
	p->addButton(createButton(p, callbacks::ataqueNormal, Vector2D(150, 680), 85, 96, Resources::AtaqueNormal));
	p->addButton(createButton(p, callbacks::ataqueMagico, Vector2D(250, 700), 82, 72, Resources::AtaqueMagico));
	p->addButton(createButton(p, callbacks::defensa, Vector2D(50, 700), 82, 72, Resources::Defensa));
	p->addButton(createButton(p, callbacks::huida, Vector2D(350, 710), 100, 55, Resources::Huida));
}
void Interfaz::createMovement()
{
	Panel* p = new Panel(Movement);
	allPanels.push_back(p);
	p->addButton(createButton(p, callbacks::avanzar, Vector2D(150, 780), 85, 96, Resources::Avanzar));
	p->addButton(createButton(p, callbacks::rotarDer, Vector2D(250, 800), 82, 72, Resources::RotarD));
	p->addButton(createButton(p, callbacks::rotarIzq, Vector2D(50, 800), 82, 72, Resources::RotarI));
	p->addButton(createButton(p, callbacks::interactuar, Vector2D(350, 810), 100, 55, Resources::Interactuar));
}


void Interfaz::createHeroes()
{
	// posicion del panel respecto a la ventana
	SDLGame* game_ = g_->getSDLGame();
	double width = game_->getWindowWidth();
	width = width * 3 / 4;
	double height = game_->getWindowHeight();
	height = height * 1 / 4;
	Vector2D pPos = Vector2D(width, height);
	// construccion del panel de heroes
	Panel* p = new Panel(Movement);
	allPanels.push_back(p);
	uint tamL = 100;
	p->addButton(createButton(p, callbacks::pruebaGame0, Vector2D(pPos.getX(), pPos.getY()), tamL, tamL, Resources::Bardo));
	p->addButton(createButton(p, callbacks::pruebaGame1, Vector2D(pPos.getX(), pPos.getY() + 100), tamL, tamL, Resources::Brujo));
	p->addButton(createButton(p, callbacks::pruebaGame2, Vector2D(pPos.getX(), pPos.getY() + 200), tamL, tamL, Resources::Clerigo));
	p->addButton(createButton(p, callbacks::pruebaGame3, Vector2D(pPos.getX(), pPos.getY() + 300), tamL, tamL, Resources::Guerrero));
}

void Interfaz::createInfo()
{
	SDLGame* game_ = g_->getSDLGame();
	double width = game_->getWindowWidth();
	double height = game_->getWindowHeight();
	uint tamBoton = width / 16;

	Panel* p = new Panel(Info);
	allPanels.push_back(p);
	p->addButton(createButton(p, callbacks::inventario, Vector2D(width * 4 / 7, height * 3 / 4), tamBoton*2, tamBoton*2, Resources::Inventario));
	p->addButton(createButton(p, callbacks::pocionVida, Vector2D(width * 5 / 7, height * 3 / 4), tamBoton* 0.8, tamBoton * 0.8, Resources::PocionVida));
	p->addButton(createButton(p, callbacks::pocionMana, Vector2D(width * 5 / 7, height * 5 / 6), tamBoton * 0.8, tamBoton * 0.8, Resources::PocionMana));
	p->addButton(createButton(p, callbacks::chat, Vector2D(width * 6 / 7, height * 3 / 4), tamBoton, tamBoton, Resources::Chat));
	p->addButton(createButton(p, callbacks::configuracion, Vector2D( width * 6 / 7, height * 5 / 6), tamBoton, tamBoton, Resources::Configuracion));
}

Interfaz::Interfaz(Game* juego, EntityManager* manager)
{
	g_ = juego;
	mngr_ = manager;
	createPanel(Movement);
	createPanel(Fight);
	createPanel(Minimap);
	createPanel(Heroes);
	createPanel(Info);
	c_ = createCursor(Vector2D(200, 200), 50, 50, Resources::Mouse);
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

