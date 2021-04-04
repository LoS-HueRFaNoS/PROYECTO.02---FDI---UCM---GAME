#include "Interfaz.h"
#include "Button.h"
#include "SDLGame.h"
#include "callbacks.h"

Interfaz::Interfaz(Game* juego, EntityManager* manager, PlayerMotion* plmot)
{
	g_ = juego;
	mngr_ = manager;
	createPanel(Movement, plmot);
	createPanel(Fight, plmot);
	createPanel(Minimap, plmot);
	createPanel(Heroes, plmot);
	createPanel(Info, plmot);
	c_ = createCursor(Vector2D(200, 200), 50, 50, Resources::Mouse);
}

Interfaz::~Interfaz()
{
}

Cursor* Interfaz::createCursor(Vector2D pos, uint width, uint height, Resources::TextureId image)
{
	SDLGame* game_ = g_->getSDLGame();
	Cursor* c = static_cast<Cursor*>(mngr_->addEntity());
	c->init(game_, g_, pos, width, height, image);
	return c;
}

void Interfaz::createButtonFight(Panel* p, AtkType type, PlayerMotion* plmot, Vector2D pos, uint width, uint height, Resources::TextureId image) {
	ButtonCombate* b = mngr_->addButtonCombateEntity();
	b->setPlayerMotion(plmot);
	b->setAtkType(type);
	SDLGame* game_ = g_->getSDLGame();
	b->init(game_, g_, pos, width, height, image);
	p->addButton(b);
}
void Interfaz::createButtonMovement(Panel* p, MovType type, PlayerMotion* plmot, Vector2D pos, uint width, uint height, Resources::TextureId image) {
	ButtonMovimiento* b = mngr_->addButtonMovimientoEntity();
	b->setPlayerMotion(plmot);
	b->setMovType(type);
	SDLGame* game_ = g_->getSDLGame();
	b->init(game_, g_, pos, width, height, image);
	p->addButton(b);
}
void Interfaz::createButtonHeroes(Panel* p, HeroNum type, PlayerMotion* plmot, Vector2D pos, uint width, uint height, Resources::TextureId image) {
	ButtonHeroes* b = mngr_->addButtonHeroesEntity();
	b->setPlayerMotion(plmot);
	b->setHero(type);
	SDLGame* game_ = g_->getSDLGame();
	b->init(game_, g_, pos, width, height, image);
	p->addButton(b);
}
void Interfaz::createButtonInfo(Panel* p, Inf type, PlayerMotion* plmot, Vector2D pos, uint width, uint height, Resources::TextureId image) {
	ButtonInfo* b = mngr_->addButtonInfoEntity();
	b->setPlayerMotion(plmot);
	b->setInf(type);
	SDLGame* game_ = g_->getSDLGame();
	b->init(game_, g_, pos, width, height, image);
	p->addButton(b);
}

void Interfaz::createFight(PlayerMotion* plmot)
{
	Panel* p = new Panel(Fight);
	allPanels.push_back(p);
	createButtonFight(p, AtkType::normal, plmot, Vector2D(150, 680), 85, 96, Resources::AtaqueNormal);
	createButtonFight(p, AtkType::magic, plmot, Vector2D(250, 700), 82, 72, Resources::AtaqueMagico);
	createButtonFight(p, AtkType::defend, plmot, Vector2D(50, 700), 82, 72, Resources::Defensa);
	createButtonFight(p, AtkType::escape, plmot, Vector2D(350, 710), 100, 55, Resources::Huida);
}
void Interfaz::createMovement(PlayerMotion* plmot)
{
	// posicion del panel respecto a la ventana
	SDLGame* game_ = g_->getSDLGame();
	double width = game_->getWindowWidth();
	width = width * 0.03;
	double height = game_->getWindowHeight();
	height = height * 0.875;
	Vector2D pPos = Vector2D(width, height);
	// construccion del panel
	Panel* p = new Panel(Movement);
	allPanels.push_back(p);
	createButtonMovement(p, MovType::forward, plmot, Vector2D(pPos.getX() + 100, pPos.getY()), 85, 96, Resources::Avanzar);
	createButtonMovement(p, MovType::rotR, plmot, Vector2D(pPos.getX() + 200, pPos.getY()), 82, 72, Resources::RotarD);
	createButtonMovement(p, MovType::rotL, plmot, Vector2D(pPos.getX(), pPos.getY()), 82, 72, Resources::RotarI);
	createButtonMovement(p, MovType::touch, plmot, Vector2D(pPos.getX() + 300, pPos.getY()), 100, 55, Resources::Interactuar);
}


void Interfaz::createHeroes(PlayerMotion* plmot)
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
	createButtonHeroes(p, HeroNum::hero1, plmot, Vector2D(pPos.getX(), pPos.getY()), tamL, tamL, Resources::Bardo);
	createButtonHeroes(p, HeroNum::hero2, plmot, Vector2D(pPos.getX(), pPos.getY() + 100), tamL, tamL, Resources::Brujo);
	createButtonHeroes(p, HeroNum::hero3, plmot, Vector2D(pPos.getX(), pPos.getY() + 200), tamL, tamL, Resources::Clerigo);
	createButtonHeroes(p, HeroNum::hero4, plmot, Vector2D(pPos.getX(), pPos.getY() + 300), tamL, tamL, Resources::Guerrero);
}

void Interfaz::createInfo(PlayerMotion* plmot)
{
	SDLGame* game_ = g_->getSDLGame();
	double width = game_->getWindowWidth();
	double height = game_->getWindowHeight();
	uint tamBoton = width / 16;

	Panel* p = new Panel(Info);
	allPanels.push_back(p);
	createButtonInfo(p, Inf::inventory, plmot, Vector2D(width * 4 / 7, height * 3 / 4), tamBoton*2, tamBoton*2, Resources::Inventario);
	createButtonInfo(p, Inf::potionHealth, plmot, Vector2D(width * 5 / 7, height * 3 / 4), tamBoton* 0.8, tamBoton * 0.8, Resources::PocionVida);
	createButtonInfo(p, Inf::potionMana, plmot, Vector2D(width * 5 / 7, height * 5 / 6), tamBoton * 0.8, tamBoton * 0.8, Resources::PocionMana);
	createButtonInfo(p, Inf::chat, plmot, Vector2D(width * 6 / 7, height * 3 / 4), tamBoton, tamBoton, Resources::Chat);
	createButtonInfo(p, Inf::config, plmot, Vector2D( width * 6 / 7, height * 5 / 6), tamBoton, tamBoton, Resources::Configuracion);
}


void Interfaz::createPanel(idPanel panelID, PlayerMotion* plmot)
{
	switch (panelID) {
	case Fight:
		createFight(plmot);
		break;
	case Movement:
		createMovement(plmot);
		break;
	case Minimap:
		createMinimap();
		break;
	case Heroes:
		createHeroes(plmot);
		break;
	case Info:
		createInfo(plmot);
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

