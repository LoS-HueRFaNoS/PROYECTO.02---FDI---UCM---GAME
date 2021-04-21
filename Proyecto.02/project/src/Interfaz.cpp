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
	//allPanels.emplace(allPanels.begin() + Fight, p);
	allPanels[Fight] = p;
	// BOTONES:
	p->addButton(iManager->addButton<ButtonSlott>(Vector2D(pPos.getX() - 10, pPos.getY() - 10), 85 * 5 + 20, 96 + 10, src::Marco));
	p->addButton(iManager->addButton<ButtonPanel>(Vector2D(pPos.getX(), pPos.getY()), 85, 96, src::AtaqueNormal, Targets, false));
	p->addButton(iManager->addButton<ButtonPanel>(Vector2D(pPos.getX() + 100, pPos.getY()), 82, 72, src::AtaqueMagico, Habilities, false));
	p->addButton(iManager->addButton<ButtonDefend>(Vector2D(pPos.getX() + 200, pPos.getY()), 82, 72, src::Defensa, DfndType::defend));
	p->addButton(iManager->addButton<ButtonDefend>(Vector2D(pPos.getX() + 300, pPos.getY()), 100, 55, src::Huida, DfndType::escape));
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
	//allPanels.emplace(allPanels.begin() + Movement, p);
	allPanels[Movement] = p;
	// BOTONES:
	p->addButton(iManager->addButton<ButtonMovimiento>(Vector2D(pPos.getX() + 200, pPos.getY()), 64, 64, src::RotarD, MovType::rotR));
	p->addButton(iManager->addButton<ButtonMovimiento>(Vector2D(pPos.getX() + 000, pPos.getY()), 64, 64, src::RotarI, MovType::rotL));
	p->addButton(iManager->addButton<ButtonMovimiento>(Vector2D(pPos.getX() + 100, pPos.getY()), 64, 64, src::Avanzar, MovType::forward));
	p->addButton(iManager->addButton<ButtonMovimiento>(Vector2D(pPos.getX() + 300, pPos.getY()), 128, 64, src::Interactuar, MovType::touch));
} // rotR, rotL, forward, touch

#include "ecs.h"
#include "../TheElementalMaze.h"
#include "CombatManager.h"
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
	Panel* p = new Panel(Heroes);
	//allPanels.emplace(allPanels.begin() + Heroes, p);
	allPanels[Heroes] = p;
	uint tamL = 100;
	// BOTONES:
	CombatManager* c = GETCMP2(TheElementalMaze::instance(), CombatManager);
	uint n = c->getHerosTam();
	for (int i = 0; i < n; i++) {
		p->addButton(iManager->addButton<ButtonHero>(Vector2D(pPos.getX(), pPos.getY() + i * 100.0), tamL, tamL, getHeroTxt(i), (HeroNum)i));
	}
} // hero1, hero2, hero3, hero4

void Interfaz::createInfo()
{
	SDLGame* game_ = entity_->getSDLGame();
	double width = game_->getWindowWidth();
	double height = game_->getWindowHeight();
	uint tamBoton = uint(width / 16);

	Panel* p = new Panel(Info);
	//allPanels.emplace(allPanels.begin() + Info, p);
	allPanels[Info] = p;

	double space = tamBoton * 0.8;
	// BOTONES:
	p->addButton(iManager->addButton<ButtonPotion>(Vector2D(width * 5 / 7, height * 3 / 4), tamBoton * 0.8, tamBoton * 0.8, src::PocionVida, PtnType::health));
	p->addButton(iManager->addButton<ButtonPotion>(Vector2D(width * 5 / 7, height * 5 / 6), tamBoton * 0.8, tamBoton * 0.8, src::PocionMana, PtnType::mana));
	//p->addButton(iManager->addButton<ButtonPotion>(Vector2D(width * 5 / 7, height * 5 / 6 + space), tamBoton * 0.8, tamBoton * 0.8, src::PocionRess, PtnType::resurrection));

	p->addButton(iManager->addButton<ButtonPanel>(Vector2D(width * 4 / 7, height * 3 / 4), tamBoton * 2, tamBoton * 2, src::Inventario, Inventory, false));
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
	//allPanels.emplace(allPanels.begin() + Inventory, p);
	allPanels[Inventory] = p;

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

void Interfaz::createTargets()
{
	// posicion del panel respecto a la ventana
	SDLGame* game_ = entity_->getSDLGame();
	double width = game_->getWindowWidth();
	width = width * 0.03;
	double height = game_->getWindowHeight();
	height = height * 0.875;
	Vector2D pPos = Vector2D(width, height);
	// construccion del panel
	Panel* p = new Panel(Targets);
	//allPanels.emplace(allPanels.begin() + Targets, p);
	allPanels[Targets] = p;
	// BOTONES:
	/*p->addButton(iManager->addButton<ButtonSlott>(Vector2D(pPos.getX() - 10, pPos.getY() - 10), 85 * 5 + 20, 96 + 10, src::Marco));
	p->addButton(iManager->addButton<ButtonPanelCte>(Vector2D(pPos.getX(), pPos.getY()), 85, 96, src::AtaqueNormal, AtkType::normal, allPanels[Targets]));
	p->addButton(iManager->addButton<ButtonPanelCte>(Vector2D(pPos.getX() + 100, pPos.getY()), 82, 72, src::AtaqueMagico, AtkType::magic, allPanels[Habilities]));
	p->addButton(iManager->addButton<ButtonDefend>(Vector2D(pPos.getX() + 200, pPos.getY()), 82, 72, src::Defensa, DfndType::defend));
	p->addButton(iManager->addButton<ButtonDefend>(Vector2D(pPos.getX() + 300, pPos.getY()), 100, 55, src::Huida, DfndType::escape));*/
}

void Interfaz::createHabilities()
{
	// posicion del panel respecto a la ventana
	SDLGame* game_ = entity_->getSDLGame();
	double width = game_->getWindowWidth();
	width = width * 0.03;
	double height = game_->getWindowHeight();
	height = height * 0.875;
	Vector2D pPos = Vector2D(width, height);
	// construccion del panel
	Panel* p = new Panel(Habilities);
	//allPanels.emplace(allPanels.begin() + Habilities, p);
	allPanels[Habilities] = p;
	// BOTONES:
	/*p->addButton(iManager->addButton<ButtonSlott>(Vector2D(pPos.getX() - 10, pPos.getY() - 10), 85 * 5 + 20, 96 + 10, src::Marco));
	p->addButton(iManager->addButton<ButtonPanelCte>(Vector2D(pPos.getX(), pPos.getY()), 85, 96, src::AtaqueNormal, AtkType::normal, allPanels[Targets]));
	p->addButton(iManager->addButton<ButtonPanelCte>(Vector2D(pPos.getX() + 100, pPos.getY()), 82, 72, src::AtaqueMagico, AtkType::magic, allPanels[Habilities]));
	p->addButton(iManager->addButton<ButtonDefend>(Vector2D(pPos.getX() + 200, pPos.getY()), 82, 72, src::Defensa, DfndType::defend));
	p->addButton(iManager->addButton<ButtonDefend>(Vector2D(pPos.getX() + 300, pPos.getY()), 100, 55, src::Huida, DfndType::escape));*/
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
	/*delete allPanels[panelID];
	allPanels[panelID] = nullptr;*/
}

void Interfaz::toggleCombat_Movement()
{
	togglePanel(Fight);
	togglePanel(Movement);
}

void Interfaz::init()
{
	//allPanels.reserve(maxPanels);
	initialize();
	createPanel(Movement);
	createPanel(Heroes);
	createPanel(Info);
	createPanel(Minimap);
	createPanel(Fight);
	togglePanel(Fight);
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

#include "CombatManager.h"
Resources::TextureId Interfaz::getHeroTxt(uint number)
{
	CombatManager* c = GETCMP2(entity_, CombatManager);
	string name = c->getCharacter((int)number, HERO)->name();

	if (name == "Warrior") return src::Guerrero;
	if (name == "Wizard") return src::Brujo;
	if (name == "Ranger") return src::Explorador;
	if (name == "Bard") return src::Bardo;
	if (name == "Cleric") return src::Clerigo;
	if (name == "Paladin") return src::Paladin;
	if (name == "Barbarian") return src::Barbaro;
	if (name == "Rogue") return src::Picaro;
	if (name == "Druid") return src::Druida;
	return Resources::TextureId();
}

void Interfaz::initialize()
{
	for (uint i = 0; i < maxPanels; ++i)
	{
		allPanels.push_back(nullptr);
	}
}

