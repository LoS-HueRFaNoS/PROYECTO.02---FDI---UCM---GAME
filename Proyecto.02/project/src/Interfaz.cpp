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
	// posici�n en pixeles del 'fondo'
	double x_ = 70;
	double y_ = 790;
	// tama�o en pixeles del 'fondo'
	double w_ = 710;
	double h_ = 190;
	// tama�o de los margenes
	double n = 20;

	// posicion del panel respecto a la ventana
	x_ = setHorizontalScale(x_ + n);
	y_ = setVerticalScale(y_ + n);

	double espace = setHorizontalScale((w_ - n) / 4);

	w_ = espace - setHorizontalScale(n);
	h_ = setVerticalScale(h_ - n * 2);

	// construccion y asignacion del panel:
	Panel* p = new Panel(Fight);
	allPanels[Fight] = p;

	// BOTONES: normal, magic, defend, escape
	p->addButton(iManager->addButton<ButtonPanel>(Vector2D(x_ + 0, y_), w_, h_, src::AtaqueNormal, Targets, false));
	p->addButton(iManager->addButton<ButtonPanel>(Vector2D(x_ + espace, y_), w_, h_, src::AtaqueMagico, Habilities, false));
	p->addButton(iManager->addButton<ButtonDefend>(Vector2D(x_ + espace * 2, y_), w_, h_, src::Defensa, DfndType::defend));
	p->addButton(iManager->addButton<ButtonDefend>(Vector2D(x_ + espace * 3, y_), w_, h_, src::Huida, DfndType::escape));
}

void Interfaz::createMovement()
{
	// posici�n en pixeles del 'fondo'
	double x_ = 70;
	double y_ = 790;
	// tama�o en pixeles del 'fondo'
	double w_ = 710;
	double h_ = 190;
	// tama�o de los margenes
	double n = 20;

	// posicion del panel respecto a la ventana
	x_ = setHorizontalScale(x_ + n);
	y_ = setVerticalScale(y_ + n);

	/* || 20px - button - 20px - button - 20px - button - 20px - button - 20px - button - 20px || */
	double espace = setHorizontalScale((w_ - n) / 4);

	w_ = espace - setHorizontalScale(n);
	h_ = setVerticalScale(h_ - n * 2);

	// construccion y asignacion del panel:
	Panel* p = new Panel(Movement);
	allPanels[Movement] = p;

	// BOTONES: rotR, rotL, forward, touch
	p->addButton(iManager->addButton<ButtonMovimiento>(Vector2D(x_ + 0, y_), w_, h_, src::RotarI, MovType::rotL));
	p->addButton(iManager->addButton<ButtonMovimiento>(Vector2D(x_ + espace, y_), w_, h_, src::Avanzar, MovType::forward));
	p->addButton(iManager->addButton<ButtonMovimiento>(Vector2D(x_ + espace * 2, y_), w_, h_, src::RotarD, MovType::rotR));
	p->addButton(iManager->addButton<ButtonMovimiento>(Vector2D(x_ + espace * 3, y_), w_, h_, src::Interactuar, MovType::touch));
}

#include "ecs.h"
#include "../TheElementalMaze.h"
#include "CombatManager.h"
void Interfaz::createHeroes()
{
	CombatManager* c = GETCMP2(TheElementalMaze::instance(), CombatManager);
	uint nHeros = c->getHerosTam();

	// posici�n en pixeles del 'fondo'
	double x_ = 1510;
	double y_ = 360;
	// tama�o en pixeles del 'fondo'
	double w_ = 340;
	double h_ = 330;
	// tama�o de los margenes
	double n = 5;

	// posicion del panel respecto a la ventana
	x_ = setHorizontalScale(x_ + n);
	y_ = setVerticalScale(y_ + n);

	double espace = setVerticalScale((h_ - n) / nHeros);

	h_ = espace - setHorizontalScale(n);
	w_ = h_;

	// construccion del panel de heroes
	Panel* p = new Panel(Heroes);
	allPanels[Heroes] = p;

	// BOTONES: hero1, hero2, hero3, hero4
	for (int i = 0; i < nHeros; i++) {
		p->addButton(iManager->addButton<ButtonHero>(Vector2D(x_, y_ + i * espace), w_, h_, getHeroTxt(i), (HeroNum)i));
	}
}

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
		p->addButton(iManager->addButton<ButtonSlott>(Vector2D(posX, posY), slotTam, slotTam, getHeroTxt(i)));
		p->addButton(iManager->addButton<ButtonSlott>(Vector2D(posX + slotTam, posY), slotTam, slotTam, src::WeaponSlot));
		p->addButton(iManager->addButton<ButtonSlott>(Vector2D(posX + slotTam * 2, posY), slotTam, slotTam, src::ArmorSlot));

		posY += slotTam * 1.33;
	}
}

void Interfaz::createTargets()
{
	CombatManager* c = GETCMP2(TheElementalMaze::instance(), CombatManager);
	uint nEnemys = c->getEnemysTam();

	// posici�n en pixeles del 'fondo'
	double x_ = 70;
	double y_ = 790;
	// tama�o en pixeles del 'fondo'
	double w_ = 710;
	double h_ = 190;
	// tama�o de los margenes
	double n = 20;

	// posicion del panel respecto a la ventana
	x_ = setHorizontalScale(x_ + n);
	y_ = setVerticalScale(y_ + n);

	double espace = setHorizontalScale((w_ - n) / 4);

	w_ = espace - setHorizontalScale(n);
	h_ = setVerticalScale(h_ - n * 2);

	// construccion y asignacion del panel:
	Panel* p = new Panel(Targets);
	allPanels[Targets] = p;

	// BOTONES:
	for (int i = 0; i < nEnemys; i++) {
		p->addButton(iManager->addButton<ButtonTarget>(Vector2D(x_ + espace * i, y_), w_, h_, getHeroTxt(i), (target)i));
	}
}

void Interfaz::createHabilities()
{
	CombatManager* c = GETCMP2(TheElementalMaze::instance(), CombatManager);
	uint nEnemys = c->getEnemysTam();

	// posici�n en pixeles del 'fondo'
	double x_ = 70;
	double y_ = 790;
	// tama�o en pixeles del 'fondo'
	double w_ = 710;
	double h_ = 190;
	// tama�o de los margenes
	double n = 20;

	// posicion del panel respecto a la ventana
	x_ = setHorizontalScale(x_ + n);
	y_ = setVerticalScale(y_ + n);

	double espace = setHorizontalScale((w_ - n) / 4);

	w_ = espace - setHorizontalScale(n);
	h_ = setVerticalScale(h_ - n * 2);

	// construccion y asignacion del panel:
	Panel* p = new Panel(Habilities);
	allPanels[Habilities] = p;

	// BOTONES:
	for (int i = 0; i < nEnemys; i++) {
		p->addButton(iManager->addButton<ButtonHability>(Vector2D(x_ + espace * i, y_), w_, h_, getHeroTxt(i), (HbltType)i, Targets, false, allPanels[Fight]));
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
	case Targets:
		createTargets();
		break;
	case Habilities:
		createHabilities();
		break;
	}
}

void Interfaz::removePanel(idPanel panelID)
{
	allPanels[panelID]->removeButtons();
}

void Interfaz::destroyPanel(idPanel panelID)
{
	/*delete allPanels[panelID];
	allPanels[panelID] = nullptr;*/
}

void Interfaz::togglePanel(Panel* pan)
{
	pan->toggleButtons();
}

void Interfaz::toggleCombat_Movement()
{
	togglePanel(Fight);
	togglePanel(Movement);
}

void Interfaz::init()
{
	//allPanels.reserve(maxPanels);
	initialize(); // convertir a tipo std::map<clave, valor> -> ahora est� hardcodeado
	// Fondo de todo la interfaz, para delimitar claramente los paneles: 
	// (mejor que ButtonSlott ser�a crear unaclase foto/image y que button herede de ella)
	//iManager->addButton<ButtonSlott>(Vector2D(), game_->getWindowWidth(), game_->getWindowHeight(), src::Fondo); 
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
	heroTemplate tem = static_cast<Hero*>(c->getCharacter((int)number, HERO))->getTemplate();

	Resources::TextureId id;

	switch (tem)
	{
	case rpgLogic::WARRIOR:
		id = src::Guerrero;
		break;
	case rpgLogic::WIZARD:
		id = src::Brujo;
		break;
	case rpgLogic::RANGER:
		id = src::Explorador;
		break;
	case rpgLogic::BARD:
		id = src::Bardo;
		break;
	case rpgLogic::CLERIC:
		id = src::Clerigo;
		break;
	case rpgLogic::PALADIN:
		id = src::Paladin;
		break;
	case rpgLogic::BARBARIAN:
		id = src::Barbaro;
		break;
	case rpgLogic::ROGUE:
		id = src::Picaro;
		break;
	case rpgLogic::DRUID:
		id = src::Druida;
		break;
	default:
		id = Resources::TextureId();
		break;
	}

	return id;
} // hace falta un metodo como este para los enemigos y otro para las habilidades (tambien estan armas, armaduras y objetos, pero urgen menos)

void Interfaz::initialize()
{
	for (uint i = 0; i < maxPanels; ++i)
	{
		allPanels.push_back(nullptr);
	}
}

