#include "Interfaz.h"
#include "Button.h"
#include "SDLGame.h"
#include "InterfazManager.h"
#include "callbacks.h"
#include "Image.h"
#include "Transform.h"

using cb = callbacks;
using src = Resources;

Interfaz::~Interfaz()
{
	for (auto it = allPanels.begin(); it != allPanels.end(); ++it)
	{
		delete (*it);
	}
	allPanels.clear();
}

void Interfaz::createFight()
{
	// posicion del panel respecto a la ventana
	SDLGame* game_ = entity_->getSDLGame();
	double width = game_->getWindowWidth();
	width = width * 0.03;
	double height = game_->getWindowHeight();
	height = height * 0.875;
	Vector2D pPos = Vector2D(width, height);
	// construccion del panel
	Panel* p = new Panel(Fight);
	allPanels.push_back(p);
	// BOTONES:
	p->addButton(iManager->addButton<ButtonAttack>(Vector2D(pPos.getX() + 100, pPos.getY()), 85, 96, src::AtaqueNormal, AtkType::normal));
	p->addButton(iManager->addButton<ButtonAttack>(Vector2D(pPos.getX() + 200, pPos.getY()), 82, 72, src::AtaqueMagico, AtkType::magic));
	p->addButton(iManager->addButton<ButtonAttack>(Vector2D(pPos.getX(), pPos.getY()), 82, 72, src::Defensa, AtkType::defend));
	p->addButton(iManager->addButton<ButtonAttack>(Vector2D(pPos.getX() + 300, pPos.getY()), 100, 55, src::Huida, AtkType::escape));
} // normal, magic, defend, escape

void Interfaz::createMovement()
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
	// BOTONES:
	p->addButton(iManager->addButton<ButtonMovimiento>(Vector2D(pPos.getX() + 100, pPos.getY()), 85, 96, src::RotarD, MovType::rotR));
	p->addButton(iManager->addButton<ButtonMovimiento>(Vector2D(pPos.getX() + 200, pPos.getY()), 82, 72, src::RotarI, MovType::rotL));
	p->addButton(iManager->addButton<ButtonMovimiento>(Vector2D(pPos.getX(), pPos.getY()), 82, 72, src::Avanzar, MovType::forward));
	p->addButton(iManager->addButton<ButtonMovimiento>(Vector2D(pPos.getX() + 300, pPos.getY()), 100, 55, src::Interactuar, MovType::touch));
} // rotR, rotL, forward, touch

void Interfaz::createHeroes()
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
	// BOTONES:
	p->addButton(iManager->addButton<ButtonHero>(Vector2D(pPos.getX(), pPos.getY()), tamL, tamL, src::Bardo, HeroNum::hero1));
	p->addButton(iManager->addButton<ButtonHero>(Vector2D(pPos.getX(), pPos.getY() + 100), tamL, tamL, src::Brujo, HeroNum::hero2));
	p->addButton(iManager->addButton<ButtonHero>(Vector2D(pPos.getX(), pPos.getY() + 200), tamL, tamL, src::Clerigo, HeroNum::hero3));
	p->addButton(iManager->addButton<ButtonHero>(Vector2D(pPos.getX(), pPos.getY() + 300), tamL, tamL, src::Guerrero, HeroNum::hero4));
} // hero1, hero2, hero3, hero4

void Interfaz::createInfo()
{
	SDLGame* game_ = entity_->getSDLGame();
	double width = game_->getWindowWidth();
	double height = game_->getWindowHeight();
	uint tamBoton = uint(width / 16);

	Panel* p = new Panel(Info);
	allPanels.push_back(p);

	double space = tamBoton * 0.8;
	// BOTONES:
	p->addButton(iManager->addButton<ButtonPotion>(Vector2D(width * 5 / 7, height * 3 / 4), tamBoton * 0.8, tamBoton * 0.8, src::PocionVida, PtnType::health));
	p->addButton(iManager->addButton<ButtonPotion>(Vector2D(width * 5 / 7, height * 5 / 6), tamBoton * 0.8, tamBoton * 0.8, src::PocionMana, PtnType::mana));
	//p->addButton(iManager->addButton<ButtonPotion>(Vector2D(width * 5 / 7, height * 5 / 6 + space), tamBoton * 0.8, tamBoton * 0.8, src::PocionRess, PtnType::resurrection));

	//p->addButton(iManager->addButton<ButtonPanelCte>(Vector2D(width * 4 / 7, height * 3 / 4), tamBoton * 2, tamBoton * 2, src::Inventario, p));
	/*createButton(p, this, cb::chat, Vector2D(width * 6 / 7, height * 3 / 4), tamBoton, tamBoton, src::Chat);
	createButton(p, this, cb::configuracion, Vector2D(width * 6 / 7, height * 5 / 6), tamBoton, tamBoton, src::Configuracion);*/
} // health, mana, resurrection

void Interfaz::createInventory()
{
	SDLGame* game_ = entity_->getSDLGame();

	double slotTam = game_->getWindowWidth() / 16;
	double posX;
	double posY = slotTam * 1.5;

	Panel* p = new Panel(Inventory);
	allPanels.push_back(p);

	// Cuadro de inventario 5x5
	for (int i = 0; i < 5; ++i) {

		posX = slotTam * 0.84; //Se resetea la coordenada X

		for (int j = 0; j < 5; ++j) {
			p->addButton(iManager->addButton<ButtonSlott>(Vector2D(posX, posY), slotTam, slotTam, src::Slot));
			posX += slotTam;
		}

		posY += slotTam; // Se suma la coordenada Y
	}

	posX += slotTam; // Se suma la coordenada X dejando un espacio.
	posY = slotTam * 1.5;
	int margen = 6;

	// Inventario personajes: clase + arma + armadura
	for (int i = 0; i < 4; ++i) {
		p->addButton(iManager->addButton<ButtonSlott>(Vector2D(posX, posY), slotTam, slotTam, src::Bardo));
		p->addButton(iManager->addButton<ButtonSlott>(Vector2D(posX + slotTam, posY), slotTam, slotTam, src::WeaponSlot));
		p->addButton(iManager->addButton<ButtonSlott>(Vector2D(posX + slotTam * 2, posY), slotTam, slotTam, src::ArmorSlot));

		posY += slotTam * 1.33;
	}
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
	while (!encontrado && i < allPanels.size()) {
		encontrado = i == panelID;
		++i;
	}

	if (encontrado && allPanels[i] != nullptr) delete allPanels[i];

	if (panelID == idPanel::Inventory) {
		for (int j = 0; j < entitiesV.size(); ++j) {
			delete entitiesV[j];
		}

		entitiesV.clear();
	}

}

void Interfaz::toggleCombat_Movement()
{
	togglePanel(Fight);
	togglePanel(Movement);
}

void Interfaz::init()
{
	createPanel(Fight);
	togglePanel(Fight);
	createPanel(Movement);
	createPanel(Heroes);
	createPanel(Info);
	createPanel(Inventory);
	destroyPanel(Inventory);
	createPanel(Minimap);
}

void Interfaz::update()
{
	InputHandler* ih_ = InputHandler::instance();
	if (ih_->isKeyDown(SDLK_t)) {
		// mouse event
		toggleCombat_Movement();
	}
}

Entity* Interfaz::getEntity()
{
	return entity_;
}

