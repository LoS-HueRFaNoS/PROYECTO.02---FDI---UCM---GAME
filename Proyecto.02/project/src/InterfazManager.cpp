#include "InterfazManager.h"
#include "Button.h"
#include "SDLGame.h"
#include "callbacks.h"
using cb = callbacks;
using src = Resources;

InterfazManager::~InterfazManager()
{
	for (auto it = allPanels.begin(); it != allPanels.end(); ++it)
	{
		delete (*it);
	}
	allPanels.clear();
}

Cursor* InterfazManager::createCursor(Vector2D pos, uint width, uint height, src::TextureId image)
{
	Cursor* c = static_cast<Cursor*>(entity_->getEntityMangr()->addEntity());
	c->init(this, pos, width, height, image);
	return c;
}

Button* InterfazManager::createButton(Panel* p, InterfazManager* im, CallBackOnClick* cb, Vector2D pos, uint width, uint height, src::TextureId image)
{
	Button* b = static_cast<Button*>(entity_->getEntityMangr()->addEntity());
	b->init(this, cb, pos, width, height, image);
	p->addButton(b);
	return b;
}

//void InterfazManager::createButtonFight(Panel* p, AtkType type, PlayerMotion* plmot, Vector2D pos, uint width, uint height, src::TextureId image) {
//	ButtonCombate* b = mngr_->addButtonCombateEntity();
//	b->setPlayerMotion(plmot);
//	b->setAtkType(type);
//	SDLGame* game_ = g_->getSDLGame();
//	b->init(game_, g_, pos, width, height, image);
//	p->addButton(b);
//}
//void InterfazManager::createButtonMovement(Panel* p, MovType type, PlayerMotion* plmot, Vector2D pos, uint width, uint height, src::TextureId image) {
//	ButtonMovimiento* b = mngr_->addButtonMovimientoEntity();
//	b->setPlayerMotion(plmot);
//	b->setMovType(type);
//	SDLGame* game_ = g_->getSDLGame();
//	b->init(game_, g_, pos, width, height, image);
//	p->addButton(b);
//}
//void InterfazManager::createButtonHeroes(Panel* p, HeroNum type, PlayerMotion* plmot, Vector2D pos, uint width, uint height, src::TextureId image) {
//	ButtonHeroes* b = mngr_->addButtonHeroesEntity();
//	b->setPlayerMotion(plmot);
//	b->setHero(type);
//	SDLGame* game_ = g_->getSDLGame();
//	b->init(game_, g_, pos, width, height, image);
//	p->addButton(b);
//}
//void InterfazManager::createButtonInfo(Panel* p, Inf type, PlayerMotion* plmot, Vector2D pos, uint width, uint height, src::TextureId image) {
//	ButtonInfo* b = mngr_->addButtonInfoEntity();
//	b->setPlayerMotion(plmot);
//	b->setInf(type);
//	SDLGame* game_ = g_->getSDLGame();
//	b->init(game_, g_, pos, width, height, image);
//	p->addButton(b);
//}

void InterfazManager::createFight()
{
	Panel* p = new Panel(Fight);
	allPanels.push_back(p);
	/*createButtonFight(p, AtkType::normal, plmot, Vector2D(150, 680), 85, 96, src::AtaqueNormal);
	createButtonFight(p, AtkType::magic, plmot, Vector2D(250, 700), 82, 72, src::AtaqueMagico);
	createButtonFight(p, AtkType::defend, plmot, Vector2D(50, 700), 82, 72, src::Defensa);
	createButtonFight(p, AtkType::escape, plmot, Vector2D(350, 710), 100, 55, src::Huida);*/
	createButton(p, this, cb::ataqueNormal, Vector2D(150, 680), 85, 96, src::AtaqueNormal);
	createButton(p, this, cb::ataqueMagico, Vector2D(250, 700), 82, 72, src::AtaqueMagico);
	createButton(p, this, cb::defensa, Vector2D(50, 700), 82, 72, src::Defensa);
	createButton(p, this, cb::huida, Vector2D(350, 710), 100, 55, src::Huida);
}
void InterfazManager::createMovement()
{
	// posicion del panel respecto a la ventana
	SDLGame* game_ = entity_->getSDLGame();
	double width = game_->getWindowWidth();
	width = width * 0.03;
	double height = game_->getWindowHeight();
	height = height * 0.875;
	Vector2D pPos = Vector2D(width, height);
	// construccion del panel
	Panel* p = new Panel(Movement);
	allPanels.push_back(p);
	/*createButtonMovement(this, rotarDerecha, Vector2D(pPos.getX() + 100, pPos.getY()), 85, 96, src::Avanzar);
	createButtonMovement(p, MovType::rotR, plmot, Vector2D(pPos.getX() + 200, pPos.getY()), 82, 72, src::RotarD);
	createButtonMovement(p, MovType::rotL, plmot, Vector2D(pPos.getX(), pPos.getY()), 82, 72, src::RotarI);
	createButtonMovement(p, MovType::touch, plmot, Vector2D(pPos.getX() + 300, pPos.getY()), 100, 55, src::Interactuar);*/
	createButton(p, this, cb::avanzar, Vector2D(pPos.getX(), pPos.getY()), 82, 72, src::Avanzar);
	createButton(p, this, cb::rotarDerecha, Vector2D(pPos.getX() + 100, pPos.getY()), 85, 96, src::RotarD);
	createButton(p, this, cb::rotarIzquierda, Vector2D(pPos.getX() + 200, pPos.getY()), 82, 72, src::RotarI);
	createButton(p, this, cb::interactuar, Vector2D(pPos.getX() + 300, pPos.getY()), 100, 55, src::Interactuar);
}


void InterfazManager::createHeroes()
{
	// posicion del panel respecto a la ventana
	SDLGame* game_ = entity_->getSDLGame();
	double width = game_->getWindowWidth();
	width = width * 3 / 4;
	double height = game_->getWindowHeight();
	height = height * 1 / 4;
	Vector2D pPos = Vector2D(width, height);
	// construccion del panel de heroes
	Panel* p = new Panel(Movement);
	allPanels.push_back(p);
	uint tamL = 100;
	/*createButtonHeroes(p, HeroNum::hero1, plmot, Vector2D(pPos.getX(), pPos.getY()), tamL, tamL, src::Bardo);
	createButtonHeroes(p, HeroNum::hero2, plmot, Vector2D(pPos.getX(), pPos.getY() + 100), tamL, tamL, src::Brujo);
	createButtonHeroes(p, HeroNum::hero3, plmot, Vector2D(pPos.getX(), pPos.getY() + 200), tamL, tamL, src::Clerigo);
	createButtonHeroes(p, HeroNum::hero4, plmot, Vector2D(pPos.getX(), pPos.getY() + 300), tamL, tamL, src::Guerrero);*/
	createButton(p, this, cb::infoHeroe01, Vector2D(pPos.getX(), pPos.getY()), tamL, tamL, src::Bardo);
	createButton(p, this, cb::infoHeroe02, Vector2D(pPos.getX(), pPos.getY() + 100), tamL, tamL, src::Brujo);
	createButton(p, this, cb::infoHeroe03, Vector2D(pPos.getX(), pPos.getY() + 200), tamL, tamL, src::Clerigo);
	createButton(p, this, cb::infoHeroe04, Vector2D(pPos.getX(), pPos.getY() + 300), tamL, tamL, src::Guerrero);
}

void InterfazManager::createInfo()
{
	SDLGame* game_ = entity_->getSDLGame();
	double width = game_->getWindowWidth();
	double height = game_->getWindowHeight();
	uint tamBoton = width / 16;

	Panel* p = new Panel(Info);
	allPanels.push_back(p);
	/*createButtonInfo(p, Inf::inventory, plmot, Vector2D(width * 4 / 7, height * 3 / 4), tamBoton*2, tamBoton*2, src::Inventario);
	createButtonInfo(p, Inf::potionHealth, plmot, Vector2D(width * 5 / 7, height * 3 / 4), tamBoton* 0.8, tamBoton * 0.8, src::PocionVida);
	createButtonInfo(p, Inf::potionMana, plmot, Vector2D(width * 5 / 7, height * 5 / 6), tamBoton * 0.8, tamBoton * 0.8, src::PocionMana);
	createButtonInfo(p, Inf::chat, plmot, Vector2D(width * 6 / 7, height * 3 / 4), tamBoton, tamBoton, src::Chat);
	createButtonInfo(p, Inf::config, plmot, Vector2D( width * 6 / 7, height * 5 / 6), tamBoton, tamBoton, src::Configuracion);*/
	createButton(p, this, cb::inventario, Vector2D(width * 4 / 7, height * 3 / 4), tamBoton*2, tamBoton*2, src::Inventario);
	createButton(p, this, cb::pocionVida, Vector2D(width * 5 / 7, height * 3 / 4), tamBoton* 0.8, tamBoton * 0.8, src::PocionVida);
	createButton(p, this, cb::pocionMana, Vector2D(width * 5 / 7, height * 5 / 6), tamBoton * 0.8, tamBoton * 0.8, src::PocionMana);
	createButton(p, this, cb::chat, Vector2D(width * 6 / 7, height * 3 / 4), tamBoton, tamBoton, src::Chat);
	createButton(p, this, cb::configuracion, Vector2D( width * 6 / 7, height * 5 / 6), tamBoton, tamBoton, src::Configuracion);
}

void InterfazManager::createInventory()
{
	SDLGame* game_ = entity_->getSDLGame();

	double slotTam = game_->getWindowWidth() / 16;
	double posX;
	double posY = slotTam * 1.5;

	Panel* p = new Panel(Inventory);
	allPanels.push_back(p);

	//Cuadro de inventario 5x5
	for (int i = 0; i < 5; ++i) {

		posX = slotTam * 1.2; //Se resetea la coordenada X

		for (int j = 0; j < 5; ++j) {

			createButton(p, this, {/*Solo quiero que se renderice no tiene cb xd*/}, Vector2D(posX, posY), slotTam, slotTam, src::Slot);

			posX += slotTam; // Se suma la coordenada X
		}
		
		posY += slotTam; // Se suma la coordenada Y
	}

	posX += slotTam; // Se suma la coordenada X dejando un espacio.
	posY = slotTam * 1.5;
	//Inventario personajes
	for (int i = 0; i < 4; ++i) {
		createButton(p, this, {/*Solo quiero que se renderice no tiene cb xd*/ }, Vector2D(posX, posY), slotTam, slotTam, src::Bardo);
		createButton(p, this, {/*Solo quiero que se renderice no tiene cb xd*/ }, Vector2D(posX + slotTam, posY), slotTam, slotTam, src::Slot);
		createButton(p, this, {/*Solo quiero que se renderice no tiene cb xd*/ }, Vector2D(posX + slotTam * 2, posY), slotTam, slotTam, src::Slot);

		posY += slotTam * 1.33;
	}
}


void InterfazManager::createPanel(idPanel panelID)
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

void InterfazManager::destroyPanel(idPanel panelID)
{
	bool encontrado = false;
	int i = 0;
	while (!encontrado && i < allPanels.size()) {
		encontrado = i == panelID;
		++i;
	}

	if (encontrado && allPanels[i] != nullptr) delete allPanels[i];
}

void InterfazManager::init()
{
	createPanel(Movement);
	createPanel(Fight);
	createPanel(Minimap);
	createPanel(Heroes);
	createPanel(Info);
	createPanel(Inventory);
	c_ = createCursor(Vector2D(200, 200), 50, 50, src::Mouse);
}

Entity* InterfazManager::getEntity()
{
	return entity_;
}

