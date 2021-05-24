#include "Interfaz.h"
#include "../ecs/ecs.h"
#include "../Templates/callbacks.h"
#include "../GameObjects/Button.h"
#include "../GameObjects/Character.h"
#include "Image.h"
#include "Transform.h"
#include "StateBar.h"
#include "Laberinto.h"
#include "Paneles/PanelTurns.h"
#include "Paneles/PanelDnD.h"
#include "../Utilities/SDL_macros.h"
#include "../Utilities/textures_box.h"
#include "../Managers/SDLGame.h"
#include "../Managers/TheElementalMaze.h"
#include "../Managers/game/PartyManager.h"
#include "../Managers/game/InterfazManager.h"
#include "../Managers/game/CombatManager.h"
#include "../Managers/game/ChatManager.h"
#include "../Managers/game/LobbyManager.h"
#include "../Managers/game/itemManager.h"
#include "ChatInfo.h"

using cb = callbacks;
using src = Resources;
using namespace textures_box;

Interfaz::~Interfaz()
{
	for (int i = 0; i < maxPanels; i++)
		delete allPanels[i];
	allPanels.clear();
}

void Interfaz::createFight()
{
	// posicion en pixeles del 'fondo'
	double x_ = 70;
	double y_ = 790;
	// tamano en pixeles del 'fondo'
	double w_ = 540;
	double h_ = 190;
	// tamano de los margenes
	double n = 20;

	// posicion del panel respecto a la ventana
	x_ = game_->setHorizontalScale(x_ + n);
	y_ = game_->setVerticalScale(y_ + n);

	// espacios entre objetos
	double espace = game_->setHorizontalScale((w_ - n) / 4);

	// ancho y alto de cada objeto
	w_ = espace - game_->setHorizontalScale(n);
	h_ = game_->setVerticalScale(h_ - n * 2);

	// construccion y asignacion del panel:
	Panel* p = new Panel(Fight);
	allPanels[Fight] = p;

	// BOTONES: normal, magic, defend, escape
	p->addButton(iManager->addButton<ButtonCombate>(Vector2D(x_ + 0, y_), w_, h_, src::AtaqueNormal, CmbtType::attack));
	p->addButton(iManager->addButton<ButtonCombate>(Vector2D(x_ + espace, y_), w_, h_, src::AtaqueMagico, CmbtType::magic));
	p->addButton(iManager->addButton<ButtonCombate>(Vector2D(x_ + espace * 2, y_), w_, h_, src::Enter, CmbtType::defend));
	p->addButton(iManager->addButton<ButtonCombate>(Vector2D(x_ + espace * 3, y_), w_, h_, src::Huida, CmbtType::escape));
}

void Interfaz::createEnemies()
{
	CombatManager* c = GETCMP2(TheElementalMaze::instance(), CombatManager);
	std::vector<Enemy*> enemies = c->getEnemiesTeam();
	size_t nEnemies = c->getEnemysTam();

	// posicion en pixeles del 'fondo'
	double x_ = 70;
	double y_ = 70;
	// tamano en pixeles del 'fondo'
	double w_ = 1340;
	double h_ = 620;
	// tamano de los margenes
	double n = 50;

	// posicion del panel respecto a la ventana
	x_ = game_->setHorizontalScale(x_ + n);
	y_ = game_->setVerticalScale(y_ + n);

	// espacios entre objetos
	double espace = game_->setHorizontalScale((w_ - n) / 4);

	// ancho y alto de cada objeto
	w_ = espace - game_->setHorizontalScale(n);
	h_ = game_->setVerticalScale(h_ - n * 2);

	// construccion y asignacion del panel:
	Panel* p = new Panel(Enemies);
	allPanels[Enemies] = p;

	for (int i = 0; i < nEnemies; i++) {
		SDL_Object* b_ = iManager->addButton<SDL_Object>(Vector2D(x_ + i * espace, y_), w_, h_, getEnemyTxt(i));
		uint k = 6;
		b_->addComponent<StateBar>(enemies[i], health, SDL_Rect(RECT((x_ + i * espace), (y_ + h_ * 1 / k), w_ * 2, h_ / k)));
		//b_->addComponent<StateBar>(enemies[i], mana, SDL_Rect(RECT((x_ + i * espace), (y_ + h_ * 2.5 / k), w_ * 2, h_ / k)));
		p->addButton(b_);
	}
}

void Interfaz::createMovement()
{
	// posicion en pixeles del 'fondo'
	double x_ = 70;
	double y_ = 790;
	// tamano en pixeles del 'fondo'
	double w_ = 540;
	double h_ = 190;
	// tamano de los margenes
	double n = 20;

	// posicion del panel respecto a la ventana
	x_ = game_->setHorizontalScale(x_ + n);
	y_ = game_->setVerticalScale(y_ + n);

	/* || 20px - button - 20px - button - 20px - button - 20px - button - 20px - button - 20px || */
	double espace = game_->setHorizontalScale((w_ - n) / 3);

	w_ = espace - game_->setHorizontalScale(n);
	h_ = game_->setVerticalScale(h_ - n * 2);

	// construccion y asignacion del panel:
	Panel* p = new Panel(Movement);
	allPanels[Movement] = p;

	// BOTONES: rotR, rotL, forward, touch
	p->addButton(iManager->addButton<ButtonMovimiento>(Vector2D(x_ + 0, y_), w_, h_, src::RotarI, MovType::rotL));
	p->addButton(iManager->addButton<ButtonMovimiento>(Vector2D(x_ + espace, y_), w_, h_, src::Avanzar, MovType::forward));
	p->addButton(iManager->addButton<ButtonMovimiento>(Vector2D(x_ + espace * 2, y_), w_, h_, src::RotarD, MovType::rotR));
	//p->addButton(iManager->addButton<ButtonMovimiento>(Vector2D(x_ + espace * 3, y_), w_, h_, src::Interactuar, MovType::touch));
}

void Interfaz::createHeroes()
{
	PartyManager* c = TheElementalMaze::instance()->getPartyManager();
	std::vector<Hero*> heroes = c->getHeroes();
	size_t nHeros = heroes.size();

	// posicion en pixeles del 'fondo'
	double x_ = 1510;
	double y_ = 360;
	// tamano en pixeles del 'fondo'
	double w_ = 340;
	double h_ = 330;
	// tamano de los margenes
	double n = 5.0 + 5.0;

	// posicion del panel respecto a la ventana
	x_ = game_->setHorizontalScale(x_ + n);
	y_ = game_->setVerticalScale(y_ + n);

	double espace = game_->setVerticalScale((h_ - n) / nHeros);

	h_ = espace - game_->setVerticalScale(n);
	w_ = h_;

	// construccion del panel de heroes
	Panel* p = new Panel(Heroes);
	allPanels[Heroes] = p;

	// BOTONES: hero1, hero2, hero3, hero4
	for (int i = 0; i < nHeros; i++) {
		if (c->getHeroes()[i] != nullptr)
		{
			ButtonHero* b_ = iManager->addButton<ButtonHero>(Vector2D(x_, y_ + i * espace), w_, h_, getHeroTxt(i), (HeroNum)i, DDPan, false);
			uint k = 6;
			b_->addComponent<StateBar>(heroes[i], health, SDL_Rect(RECT((x_ + w_ + n), (y_ + i * espace + h_ * 1 / k), w_ * 2, h_ / k)));
			b_->addComponent<StateBar>(heroes[i], mana, SDL_Rect(RECT((x_ + w_ + n), (y_ + i * espace + h_ * 2.5 / k), w_ * 2, h_ / k)));
			b_->addComponent<StateBar>(heroes[i], experience, SDL_Rect(RECT((x_ + w_ + n), (y_ + i * espace + h_ * 4 / k), w_ * 2, h_ / k)));
			p->addButton(b_);
		}
	}
}

void Interfaz::createInfo()
{
	uint nInfoButton_H = 4; // separaciones horizontales
	uint nInfoButton_V = 2; // separaciones verticales

	// posicion en pixeles del 'fondo'
	double x_ = 1350; //880;
	double y_ = 790; //790;
	// tamano en pixeles del 'fondo'
	double w_ = 500;
	double h_ = 190;
	// tamano de los margenes
	double n = 5;

	// posicion del panel respecto a la ventana
	x_ = game_->setHorizontalScale(x_ + n);
	y_ = game_->setVerticalScale(y_ + n);

	double espace_H = game_->setHorizontalScale((w_ - n) / nInfoButton_H);
	double espace_V = game_->setVerticalScale((h_ - n) / nInfoButton_V);

	w_ = espace_H - game_->setHorizontalScale(n);
	h_ = espace_V - game_->setVerticalScale(n);

	// construccion del panel de informacion
	Panel* p = new Panel(Info);
	allPanels[Info] = p;

	// BOTONES: health, mana, resurrection
	p->addButton(iManager->addButton<ButtonPanel>(Vector2D(x_, y_), w_ * 2, h_ * 2, src::Inventario, Inventory, false));
	p->addButton(iManager->addButton<ButtonPotion>(Vector2D(x_ + 2 * espace_H, y_ + 0 * espace_V), w_, h_, src::PocionVida, PtnType::health));
	p->addButton(iManager->addButton<ButtonPotion>(Vector2D(x_ + 2 * espace_H, y_ + 1 * espace_V), w_, h_, src::PocionMana, PtnType::mana));
	//p->addButton(iManager->addButton<ButtonPotion>(Vector2D(width * 5 / 7, height * 5 / 6 + space), tamBoton * 0.8, tamBoton * 0.8, src::PocionRess, PtnType::resurrection));

	//p->addButton(iManager->addButton<ButtonPanel>(Vector2D(x_ + 3 * espace_H, y_ + 0 * espace_V), w_, h_, src::Chat, Chat, false));
	p->addButton(iManager->addButton<ButtonSettings>(Vector2D(x_ + 3 * espace_H, y_ + 0 * espace_V), w_, h_, src::Change));
	p->addButton(iManager->addButton<ButtonPanel>(Vector2D(x_ + 3 * espace_H, y_ + 1 * espace_V), w_, h_, src::Configuracion, Settings, false));

} // 

void Interfaz::createInventory()
{
	SDLGame* game_ = entity_->getSDLGame();
	vector<Item*> items = TheElementalMaze::instance()->getPartyManager()->getItems();
	double slotTam = game_->getWindowWidth() / 16;
	double posX;
	double posY = slotTam * 1.8;

	Panel* p = new Panel(Inventory);
	//allPanels.emplace(allPanels.begin() + Inventory, p);
	allPanels[Inventory] = p;

	// Cuadro de inventario 5x5
	int margen = 0.1 * slotTam;
	int itemTam = 0.8 * slotTam;
	Resources::TextureId id;
	uint pivot, auxId;
	for (int i = 0; i < 5; ++i) {

		posX = slotTam * 1.5; //Se resetea la coordenada X

		for (int j = 0; j < 5; ++j) {
			p->addButton(iManager->addButton<SDL_Object>(Vector2D(posX, posY), slotTam, slotTam, src::Slot));

			int indice = i * 5 + j;
			if (indice < items.size())
			{
				Item* item = items[indice];
				if (item != nullptr) {
					ItemType itemType = item->getItemType();

					if (itemType == ItemType::ARMOR) {
						pivot = src::_firstArmorId_;
						auxId = (int) static_cast<Armor*>(item)->getArmorId();
					}
					else {
						pivot = src::_firstWeaponId_;
						auxId = (int) static_cast<Weapon*>(item)->getWeaponId();
					}
					id = (Resources::TextureId) (pivot + auxId + 1);
					p->addButton(iManager->addButton<SDL_Object>(Vector2D(posX + margen, posY + margen), itemTam, itemTam, id));
				}
			}

			posX += slotTam;
		}
		posY += slotTam; // Se suma la coordenada Y

	}

	posX += slotTam; // Se suma la coordenada X dejando un espacio.
	posY = slotTam * 1.8;


	// Inventario personajes: clase + arma + armadura
	PartyManager* c = TheElementalMaze::instance()->getPartyManager();
	std::vector<Hero*> heroes = c->getHeroes();
	for (int i = 0; i < 4; ++i) {
		p->addButton(iManager->addButton<SDL_Object>(Vector2D(posX, posY), slotTam, slotTam, getHeroTxt(i)));

		Weapon* weapon = heroes[i]->getWeapon();
		if (weapon != nullptr) {
			p->addButton(iManager->addButton<SDL_Object>(Vector2D(posX + slotTam, posY), slotTam, slotTam, src::Slot));
			pivot = src::_firstWeaponId_;
			auxId = (int)weapon->getWeaponId();
			id = (Resources::TextureId) (pivot + auxId + 1);
			p->addButton(iManager->addButton<SDL_Object>(Vector2D(posX + slotTam + margen, posY + margen), itemTam, itemTam, id));
		}
		else
			p->addButton(iManager->addButton<SDL_Object>(Vector2D(posX + slotTam, posY), slotTam, slotTam, src::WeaponSlot));

		Armor* armor = heroes[i]->getArmor();
		if (armor != nullptr) {
			p->addButton(iManager->addButton<SDL_Object>(Vector2D(posX + slotTam * 2, posY), slotTam, slotTam, src::Slot));
			pivot = src::_firstArmorId_;
			auxId = (int)armor->getArmorId();
			id = (Resources::TextureId) (pivot + auxId + 1);
			p->addButton(iManager->addButton<SDL_Object>(Vector2D(posX + slotTam * 2 + margen, posY + margen), 0.8 * slotTam, 0.8 * slotTam, id));
		}
		else
			p->addButton(iManager->addButton<SDL_Object>(Vector2D(posX + slotTam * 2, posY), slotTam, slotTam, src::ArmorSlot));



		posY += slotTam * 1.33;
	}
}

void Interfaz::createFichaDD(uint nCharacter)
{
	PartyManager* c = TheElementalMaze::instance()->getPartyManager();
	std::vector<Hero*> heroes = c->getHeroes();
	int w, h;
	w = game_->getWindowWidth();
	h = game_->getWindowHeight();
	// construccion y asignacion del panel:
	Panel* p = new Panel(DDPan);
	allPanels[DDPan] = p;
	if (TheElementalMaze::instance()->gameState() == GameState::LOBBY)
		p->addButton(iManager->addButton<ButtonHeroManagement>(Vector2D(w / 2 + w / 3 - 150, 0), 300, 100, src::FireButton, accionHero::sendHeroToStash, nCharacter, this));
	TheElementalMaze::instance()->addComponent<PanelDnD>(game_, p, heroes[nCharacter], iManager);
}

void Interfaz::createChat()
{

}

void Interfaz::createTargets()
{
	CombatManager* c = GETCMP2(TheElementalMaze::instance(), CombatManager);
	std::vector<Character*> targets = c->getCurrentTargetList();
	size_t nTargets = targets.size();

	// posicion en pixeles del 'fondo'
	double x_ = 70;
	double y_ = 790;
	// tamano en pixeles del 'fondo'
	double w_ = 710;
	double h_ = 190;
	// tamano de los margenes
	double n = 20;

	// posicion del panel respecto a la ventana
	x_ = game_->setHorizontalScale(x_ + n);
	y_ = game_->setVerticalScale(y_ + n);

	double espace = game_->setHorizontalScale((w_ - n) / 4);

	w_ = espace - game_->setHorizontalScale(n);
	h_ = game_->setVerticalScale(h_ - n * 2);

	// construccion y asignacion del panel:
	Panel* p = new Panel(Targets);
	allPanels[Targets] = p;

	// BOTONES:
	for (int i = 0; i < nTargets; i++) {
		src::TextureId img = size_t(targets[i]->getType()) ? getEnemyTxt(i) : getHeroTxt(i);
		p->addButton(iManager->addButton<ButtonTarget>(Vector2D(x_ + espace * i, y_), w_, h_, img, (target)i));
	}
}

void Interfaz::createHabilities()
{
	CombatManager* c = GETCMP2(TheElementalMaze::instance(), CombatManager);
	Hero* hero = static_cast<Hero*>(c->getCurrentCharacter());
	std::vector<Hability*> habilities = hero->getHabilities();
	size_t nHabilities = habilities.size();

	// posicion en pixeles del 'fondo'
	double x_ = 70;
	double y_ = 790;
	// tamano en pixeles del 'fondo'
	double w_ = 710;
	double h_ = 190;
	// tamano de los margenes
	double n = 20;

	// posicion del panel respecto a la ventana
	x_ = game_->setHorizontalScale(x_ + n);
	y_ = game_->setVerticalScale(y_ + n);

	double espace = game_->setHorizontalScale((w_ - n) / nHabilities);

	w_ = espace - game_->setHorizontalScale(n);
	h_ = game_->setVerticalScale(h_ - n * 2);

	// construccion y asignacion del panel:
	Panel* p = new Panel(Habilities);
	allPanels[Habilities] = p;

	// BOTONES:
	for (int i = 0; i < nHabilities; i++) {
		p->addButton(iManager->addButton<ButtonHability>(Vector2D(x_ + espace * i, y_), w_, h_, getHabilityTxt(hero, i), i));
	}
	togglePanel(Fight); // oculta el panel fight
}

void Interfaz::createMenuPrincipal()
{
	Panel* p = new Panel(MenuPrincipal);
	allPanels[MenuPrincipal] = p;
	int w, h;
	w = game_->getWindowWidth();
	h = game_->getWindowHeight();
	p->addButton(iManager->addButton<SDL_Object>(Vector2D(0, 0), w, h, src::mFondo));

	int x, y;
	x = w / 2 - 150;	y = h / 2 - 50;
	p->addButton(iManager->addButton<ButtonMenu>(Vector2D(x, y), 300, 100, src::start, accionMenu::lobby, this));
	y += 120;
	p->addButton(iManager->addButton<ButtonMenu>(Vector2D(x, y), 300, 100, src::options, accionMenu::options, this));
	y += 120;
	p->addButton(iManager->addButton<ButtonMenu>(Vector2D(x, y), 300, 100, src::howToPlay, accionMenu::how_to_play, this));
	y += 120;
	p->addButton(iManager->addButton<ButtonMenu>(Vector2D(x, y), 300, 100, src::quit, accionMenu::quit, this));
}

void Interfaz::createLobby()
{
	Panel* p = new Panel(Lobby);
	allPanels[Lobby] = p;
	int w, h, x, y;
	string text;
	SDL_Color color;

	w = game_->getWindowWidth();
	h = game_->getWindowHeight();
	p->addButton(iManager->addButton<SDL_Object>(Vector2D(0, 0), w, h, src::Fondo));
	createPanel(Heroes);
	y = 50;
	color = { 205,105,0,255 };
	text = "Tu equipo de combate";
	p->addButton(iManager->addButton<Line>(Vector2D(w / 2 - text.size() * 22, y), text.size() * 30, 70, text, Resources::FontId::HERMAN, color));

	// Botón para ir a la tienda
	p->addButton(iManager->addButton<ButtonMenu>(Vector2D(w / 2 - 150, 2 * h / 3 + 100), 300, 100, src::BuyButton, accionMenu::shop, this));
	// Botón para ir al stash
	p->addButton(iManager->addButton<ButtonMenu>(Vector2D(w / 6 - 150, 2 * h / 3 + 100), 300, 100, src::Inventario, accionMenu::stash, this));
	// Botón para empezar la partida
	p->addButton(iManager->addButton<ButtonMenu>(Vector2D(w / 2 + w / 3 - 150, 2 * h / 3 + 100), 300, 100, src::start, accionMenu::start, this));

	p->addButton(iManager->addButton<ButtonMenu>(Vector2D(0, 0), 64, 64, src::close, accionMenu::backToMenu, this));
}
void Interfaz::createShop()
{
	Panel* p = new Panel(Shop);
	nameItemTienda = " ";
	descrItemTienda = " ";
	createPanel(infoTiendaPanel);
	allPanels[Shop] = p;
	int w, h;
	SDL_Color color;
	string text;
	w = game_->getWindowWidth();
	h = game_->getWindowHeight();

	// Botón para retroceder al lobby
	p->addButton(iManager->addButton<ButtonMenu>(Vector2D(w / 2 + w / 3 - 150, 2 * h / 3 + 100), 300, 100, src::start, accionMenu::shop_lobby, this));
	LobbyManager* loManager = TheElementalMaze::instance()->getLobbyManager();
	if (loManager->getLobbyStore() != nullptr)
	{
		text = "Tienda";
		color = { 155,155,0,255 };
		p->addButton(iManager->addButton<Line>(Vector2D(w / 3 + text.size(), 40), text.size() * 30, 70, text, Resources::FontId::HERMAN, color));

		// Dinero del jugador
		text = to_string(loManager->getPlayerStash()->gold);
		color = { 155,155,0,255 };
		p->addButton(iManager->addButton<Line>(Vector2D(4 * w / 6 - 20, 20), text.size() * 30, 70, text, Resources::FontId::HERMAN, color));


		// Slots de la tienda
		p->addButton(iManager->addButton<SDL_Object>(Vector2D(90, 140), w - 500, 100, src::inventory_slots));
		p->addButton(iManager->addButton<SDL_Object>(Vector2D(90, 340), w - 500, 100, src::inventory_slots));

		// Se generan 10 héroes a la venta
		for (int i = 0; i < 10; i++)
		{
			HeroContract* her = loManager->getLobbyStore()->heroes[i];
			int tex = src::_firstHeroRId_ + (int)her->hero->getTemplate() + 1;
			// Dibujo del héroe
			p->addButton(iManager->addButton<ButtonInfoTienda>(Vector2D(99 + 94 * i, 150), 75, 80, static_cast<Resources::TextureId>(tex), true, i, this));
			// Si se han vendido se marcan como tal, si no se escribe su precio
			if (her->sold) text = "sold";
			else text = "x" + to_string(her->price);
			p->addButton(iManager->addButton<Line>(Vector2D(100 + 94 * i, 95), text.size() * 15, 50, text, Resources::FontId::HERMAN, color));
			// Botón de comprar
			p->addButton(iManager->addButton<ButtonBuyHero>(Vector2D(100 + 94 * i, 250), 70, 50, src::BuyButton, i, this));
		}
		int tam = loManager->getLobbyStore()->items.size();
		// Se generan 10 objetos a la venta
		int tex;
		for (int i = 0; i < 10 && i < tam; i++)
		{
			ItemToBuy* it = loManager->getLobbyStore()->items[i];
			if ((int)it->item->getItemType() == 0)
			{
				Weapon* arma = static_cast<Weapon*>(it->item);
				tex = (int)src::_firstWeaponId_ + (int)arma->getWeaponId() + 1;
			}
			else
			{
				Armor* armadura = static_cast<Armor*>(it->item);
				tex = (int)src::_firstArmorId_ + (int)armadura->getArmorId() + 1;
			}
			// Dibujo del objeto
			p->addButton(iManager->addButton<ButtonInfoTienda>(Vector2D(99 + 94 * i, 350), 75, 80, static_cast<Resources::TextureId>(tex), false, i, this));
			// Si se han vendido se marcan como tal, si no se escribe su precio
			if (it->sold) text = "sold";
			else text = "x" + to_string(it->item->getBuyValue());
			p->addButton(iManager->addButton<Line>(Vector2D(100 + 94 * i, 290), text.size() * 15, 50, text, Resources::FontId::HERMAN, color));
			// Botón de comprar
			p->addButton(iManager->addButton<ButtonBuyItem>(Vector2D(100 + 94 * i, 450), 70, 50, src::BuyButton, i, 1, this));
		}
	}
}
void Interfaz::createInfoTienda()
{
	int w, h;
	w = game_->getWindowWidth();
	h = game_->getWindowHeight();
	Panel* p = new Panel(infoTiendaPanel);
	allPanels[infoTiendaPanel] = p;
	SDL_Color color = { 0.0,0.0,0.0 };
	p->addButton(iManager->addButton<Line>(Vector2D(w / 6 - 150, 2 * h / 3 + 100), nameItemTienda.size() * 15, 50, nameItemTienda, Resources::FontId::HERMAN, color));
	p->addButton(iManager->addButton<Line>(Vector2D(w / 2 - 150, 2 * h / 3 + 100), descrItemTienda.size() * 15, 50, descrItemTienda, Resources::FontId::HERMAN, color));
}
void Interfaz::createStash() {
	Panel* p = new Panel(StashPanel);
	LobbyManager* loManager = TheElementalMaze::instance()->getLobbyManager();
	allPanels[StashPanel] = p;
	int w, h, tam;
	w = game_->getWindowWidth();
	h = game_->getWindowHeight();
	EntityManager* mngr_ = TheElementalMaze::instance()->getEntityMangr();


	// Botón para volver al lobby
	p->addButton(iManager->addButton<ButtonMenu>(Vector2D(w / 2 + w / 3 - 150, 2 * h / 3 + 100), 300, 100, src::howToPlay, accionMenu::stash_lobby, this));

	// Slots del stash de héroes
	p->addButton(iManager->addButton<SDL_Object>(Vector2D(50, 50), w - 500, 100, src::inventory_slots));
	p->addButton(iManager->addButton<SDL_Object>(Vector2D(50, 150), w - 500, 100, src::inventory_slots));
	if (pagHeroes == 0)
		p->addButton(iManager->addButton<ButtonMenu>(Vector2D(w - 435, 70), 50, 50, src::AvanzarBloqueado, accionMenu::retrocederHeroes, this));
	else p->addButton(iManager->addButton<ButtonMenu>(Vector2D(w - 435, 70), 50, 50, src::Avanzar, accionMenu::retrocederHeroes, this));
	if (loManager->getPlayerStash()->heroes.size() > 20 * (pagHeroes + 1))
		p->addButton(iManager->addButton<ButtonMenu>(Vector2D(w - 435, 180), 50, 50, src::Retroceder, accionMenu::avanzarHeroes, this));
	else p->addButton(iManager->addButton<ButtonMenu>(Vector2D(w - 435, 180), 50, 50, src::RetrocederBloqueado, accionMenu::avanzarHeroes, this));
	// Slots del stash de objetos
	p->addButton(iManager->addButton<SDL_Object>(Vector2D(50, 300), w - 500, 100, src::inventory_slots));
	p->addButton(iManager->addButton<SDL_Object>(Vector2D(50, 400), w - 500, 100, src::inventory_slots));
	if (pagItems == 0)
	p->addButton(iManager->addButton<ButtonMenu>(Vector2D(w - 435, 330), 50, 50, src::AvanzarBloqueado, accionMenu::retrocederItems, this));
	else p->addButton(iManager->addButton<ButtonMenu>(Vector2D(w - 435, 330), 50, 50, src::Avanzar, accionMenu::retrocederItems, this));
	if (loManager->getPlayerStash()->items.size() > 20 * (pagItems + 1))
		p->addButton(iManager->addButton<ButtonMenu>(Vector2D(w - 435, 430), 50, 50, src::Retroceder, accionMenu::avanzarItems, this));
	else p->addButton(iManager->addButton<ButtonMenu>(Vector2D(w - 435, 430), 50, 50, src::RetrocederBloqueado, accionMenu::avanzarItems, this));
	//for (int i = 0; i < 81; i++)
	//{
		//Hero* a = new Hero(game_, mngr_);
		//a->setTemplate(heroTemplate::WARRIOR);
		//loManager->addHeroToStash(a);

	//}
	tam = loManager->getPlayerStash()->heroes.size();
	// Por cada fila de slots de héroes
	for (int i = 0; i < 2; i++)
	{
		// Por cada héroe de la fila
		for (int j = 0; j < 10 && pagHeroes * 20 + i * 10 + j < tam; j++)
		{
			Hero* her = loManager->getPlayerStash()->heroes[20 * pagHeroes + i * 10 + j];
			auto tex = src::_firstHeroRId_ + (int)her->getTemplate() + 1;
			p->addButton(iManager->addButton<ButtonShowHeroToParty>(Vector2D(57 + 94 * j, 60 + 100 * i), 75, 80, static_cast<Resources::TextureId>(tex), 20 * pagHeroes + i * 10 + j, this));
			//p->addButton(iManager->addButton<ButtonHeroEquipar>(Vector2D(x, y + 100), 100, 60, src::howToPlay, i, this));
		}
	}
	ItemManager* itemMngr_ = TheElementalMaze::instance()->getItemManager();
	int Itemtam = loManager->getPlayerStash()->items.size();
	// Por cada fila de slots de objetos
	int tex;
	int a;
	for (int i = 0; i < 2; i++)
	{
		// Por cada objeto de la fila
		for (int j = 0; j < 10 && pagItems *20+ i * 10 + j < Itemtam; j++)
		{
			Item* objeto = loManager->getPlayerStash()->items[pagItems *20+ i * 10 + j];
			if ((int)objeto->getItemType() == 0)
			{
				Weapon* arma = static_cast<Weapon*>(loManager->getPlayerStash()->items[pagItems * 20 + i * 10 + j]);
				tex = (int)src::_firstWeaponId_ + (int)arma->getWeaponId() + 1;
			}
			else
			{
				Armor* armadura = static_cast<Armor*>(loManager->getPlayerStash()->items[pagItems * 20 + i * 10 + j]);
				tex = (int)src::_firstArmorId_ + (int)armadura->getArmorId() + 1;
			}
			p->addButton(iManager->addButton<ButtonItemManagement>(Vector2D(57 + 94 * j, 110 + 100 * (i + 2)), 75, 80, static_cast<Resources::TextureId>(tex), accionItem::showSellButton, j,this));
			//p->addButton(iManager->addButton<ButtonHeroEquipar>(Vector2D(x, y + 100), 100, 60, src::howToPlay, i, this));
		}
	}

}

void Interfaz::createOptions()
{
	Panel* p = new Panel(Options);
	allPanels[Options] = p;
	int w, h;
	int x, y;
	//int ancho;
	string text;
	SDL_Color color;

	w = game_->getWindowWidth();
	h = game_->getWindowHeight();
	p->addButton(iManager->addButton<SDL_Object>(Vector2D(0, 0), w, h, src::mFondo));


	x = w / 2 - 200; y = 100;
	color = { 0,0,0,255 };
	text = "Options";
	p->addButton(iManager->addButton<Line>(Vector2D(x, y), 400, 200, text, Resources::FontId::HERMAN, color));

	x = w / 2 - 75;
	y += 75;
	text = "Volume"; //Volumen con 4 botones
	p->addButton(iManager->addButton<Line>(Vector2D(x, y), 150, 40, text, Resources::FontId::HERMAN, color));
	//
	//p->addButton(iManager->addButton<ButtonOption>(Vector2D(w - 100, 36), 64, 64, src::close, accionOption::volumen, 1, this));
	//p->addButton(iManager->addButton<ButtonOption>(Vector2D(w - 100, 36), 64, 64, src::close, accionOption::volumen, 2,this));
	//p->addButton(iManager->addButton<ButtonOption>(Vector2D(w - 100, 36), 64, 64, src::close, accionOption::volumen, 3,this));
	//p->addButton(iManager->addButton<ButtonOption>(Vector2D(w - 100, 36), 64, 64, src::close, accionOption::volumen, 4,this));

	x = w / 2 - 100;
	y += 50;
	text = "Animation speed";
	p->addButton(iManager->addButton<Line>(Vector2D(x, y), 200, 40, text, Resources::FontId::HERMAN, color));
	//x0.5 x1 x2 x4
	//p->addButton(iManager->addButton<ButtonOption>(Vector2D(w - 100, 36), 64, 64, src::close, accionOption::velocidad,1 , this));
	//p->addButton(iManager->addButton<ButtonOption>(Vector2D(w - 100, 36), 64, 64, src::close, accionOption::velocidad,2,this));
	//p->addButton(iManager->addButton<ButtonOption>(Vector2D(w - 100, 36), 64, 64, src::close, accionOption::velocidad,3, this));
	//p->addButton(iManager->addButton<ButtonOption>(Vector2D(w - 100, 36), 64, 64, src::close, accionOption::velocidad,4,this));


	p->addButton(iManager->addButton<ButtonMenu>(Vector2D(w - 100, 36), 64, 64, src::close, accionMenu::options, this));

}

void Interfaz::createGuide()
{
	Panel* p = new Panel(HowToPlay);
	allPanels[HowToPlay] = p;
	int w, h;
	int x, y;
	int ancho;
	string text;
	SDL_Color color;

	w = game_->getWindowWidth();
	h = game_->getWindowHeight();
	p->addButton(iManager->addButton<SDL_Object>(Vector2D(0, 0), w, h, src::mFondo));

	p->addButton(iManager->addButton<SDL_Object>(Vector2D(100, 100), w - 200, h - 200, src::Pergamino));

	x = w / 2 - 200; y = 250;
	color = { 0,0,0,255 };
	text = "How To Play";
	p->addButton(iManager->addButton<Line>(Vector2D(x, y), 400, 100, text, Resources::FontId::HERMAN, color));

	color = { 100,50,0,255 };
	x = 250; y = 370;
	text = "Click on the virtual buttons to play the game";
	ancho = int(text.size()) * 15 - 100;
	p->addButton(iManager->addButton<Line>(Vector2D(x, y), ancho, 30, text, Resources::Fornite64, color));

	color = { 150,150,0,255 };
	y += 50;
	text = "Special Keyboards";
	ancho = int(text.size()) * 20;
	p->addButton(iManager->addButton<Line>(Vector2D(x + 150, y), ancho, 40, text, Resources::Fornite64, color));

	color = { 100,50,0,255 };
	y += 50;
	text = "Press left-right arrows or A-D keys to rotate the view";
	ancho = int(text.size()) * 15 - 100;
	p->addButton(iManager->addButton<Line>(Vector2D(x, y), ancho, 30, text, Resources::Fornite64, color));

	y += 30;
	text = "Press up arrows or W keys to advance";
	ancho = int(text.size()) * 15 - 30;
	p->addButton(iManager->addButton<Line>(Vector2D(x, y), ancho, 30, text, Resources::Fornite64, color));

	y += 30;
	text = "Press spacebar or E keys to interact";
	ancho = int(text.size()) * 15 - 50;
	p->addButton(iManager->addButton<Line>(Vector2D(x, y), ancho, 30, text, Resources::Fornite64, color));

	p->addButton(iManager->addButton<ButtonMenu>(Vector2D(w - 225, 120), 64, 64, src::close, accionMenu::how_to_play, this));

}

void Interfaz::createTurns()
{
	// construccion y asignacion del panel:
	Panel* p = new Panel(Turns);
	allPanels[Turns] = p;

	TheElementalMaze::instance()->addComponent<PanelTurns>(game_, p, iManager);
}

void Interfaz::toggleMinimap()
{

}

void Interfaz::checkAndDeletePanel(idPanel id)
{
	delete allPanels[id];
	allPanels[id] = nullptr;
}

void Interfaz::createHeroToPartyPanel()
{
	int w, h;
	w = game_->getWindowWidth();
	h = game_->getWindowHeight();
	Panel* p = new Panel(ButtonHeroToPartyPanel);
	allPanels[ButtonHeroToPartyPanel] = p;
	p->addButton(iManager->addButton<ButtonHeroManagement>(Vector2D(w / 2 + w / 3 - 150, 0), 300, 100, src::RecruitButton, accionHero::sendHeroToParty, selectedHeroToParty, this));
}

void Interfaz::createSellButtonPanel()
{
	int w, h;
	w = game_->getWindowWidth();
	h = game_->getWindowHeight();
	Panel* p = new Panel(SellButtonPanel);
	allPanels[SellButtonPanel] = p;
	p->addButton(iManager->addButton<ButtonItemManagement>(Vector2D(w / 2 - w / 3 - 150, 600), 300, 100, src::SellButton, accionItem::sellItem, selectedItem, this));
}

void Interfaz::createPanel(idPanel panelID)
{
	checkAndDeletePanel(panelID);
	switch (panelID) {
	case Fight:
		createFight();
		break;
	case Movement:
		createMovement();
		break;
	case Minimap:
		TheElementalMaze::instance()->getLaberinto()->toggleMiniMap();
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
		//createFichaDD();
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
		TheElementalMaze::instance()->addComponent<ChatInfo>(game_);
		break;
	case Targets:
		createTargets();
		break;
	case Habilities:
		createHabilities();
		break;
	case MenuPrincipal:
		createMenuPrincipal();
		break;
	case HowToPlay:
		createGuide();
		break;
	case Options:
		createOptions();
		break;
	case Enemies:
		createEnemies();
		break;
	case Lobby:
		createLobby();
		break;
	case StashPanel:
		createStash();
		break;
	case Shop:
		createShop();
		break;
	case infoTiendaPanel:
		createInfoTienda();
		break;
	case ButtonHeroToPartyPanel:
		createHeroToPartyPanel();
		break;
	case SellButtonPanel:
		createSellButtonPanel();
		break;
	default:
		break;
	}
}

void Interfaz::removePanel(idPanel panID)
{
	switch (panID)
	{
		/*case interfaz::Movement:
			break;
		case interfaz::Heroes:
			break;
		case interfaz::Inventory:
			break;
		case interfaz::Info:
			break;*/
	case interfaz::Minimap:
		TheElementalMaze::instance()->getLaberinto()->toggleMiniMap();
		break;
		/*case interfaz::Targets:
			break;
		case interfaz::Habilities:
			break;
		case interfaz::Fight:
			break;*/
	case interfaz::Turns:
		TheElementalMaze::instance()->removeComponent(ecs::PanelTurns);
		delete allPanels[panID];
		allPanels[panID] = nullptr;
		break;
		/*case interfaz::HeroesStats:
			break;*/
	case interfaz::DDPan:
		TheElementalMaze::instance()->removeComponent(ecs::PanelDnD);
		delete allPanels[panID];
		allPanels[panID] = nullptr;
		break;
		/*case interfaz::BigMap:
			break;
		case interfaz::Settings:
			break;*/
	case interfaz::Chat:
		TheElementalMaze::instance()->removeComponent(ecs::ChatInfo);
		break;
		/*case interfaz::MenuPrincipal:
			break;
		case interfaz::Lobby:
			break;
		case interfaz::Options:
			break;
		case interfaz::HowToPlay:
			break;
		case interfaz::Enemies:
			break;
		case interfaz::_LastPanId_:
			break;*/
	default:
		delete allPanels[panID];
		allPanels[panID] = nullptr;
		break;
	}
}

void Interfaz::removeChat()
{
	TheElementalMaze::instance()->removeComponent(ecs::ChatInfo);
}

void Interfaz::destroyPanel(idPanel panelID)
{
	/*delete allPanels[panelID];
	allPanels[panelID] = nullptr;*/
}

void Interfaz::togglePanel(Panel* pan)
{
	pan->toggleEnable();
}

bool Interfaz::getEnablePan(idPanel panID)
{
	if (getActivePan(panID)) return allPanels[panID]->getEnable();
	else return false;
}

void Interfaz::avPagHeroes()
{
	LobbyManager* loManager = TheElementalMaze::instance()->getLobbyManager();
	if (loManager->getPlayerStash()->heroes.size() > 20 * (pagHeroes + 1))
		pagHeroes++;
}
void Interfaz::rePagHeroes()
{
	if (pagHeroes > 0)
		pagHeroes--;
}
void Interfaz::avPagItems()
{
	LobbyManager* loManager = TheElementalMaze::instance()->getLobbyManager();
	if (loManager->getPlayerStash()->items.size() > 20 * (pagItems + 1))
		pagItems++;
}
void Interfaz::rePagItems()
{

	if (pagItems > 0)
		pagItems--;
}

void Interfaz::toggleCombat_Movement()
{
	togglePanel(Fight);
	togglePanel(Movement);
}

void Interfaz::init()
{
	ChatManager::Init();
	// Fondo de todo la interfaz, para delimitar claramente los paneles: 
	// (mejor que ButtonSlott ser�a crear unaclase foto/image y que button herede de ella)
	//iManager->addButton<ButtonSlott>(Vector2D(), game_->getWindowWidth(), game_->getWindowHeight(), src::Fondo); 
	createPanel(MenuPrincipal);
	createPanel(HowToPlay);
	createPanel(Options);

	togglePanel(HowToPlay);
	togglePanel(Options);

	/*createPanel(Movement);
	createPanel(Heroes);
	createPanel(Info);

	togglePanel(Movement);
	togglePanel(Heroes);
	togglePanel(Info);*/


}

void Interfaz::update()
{
	InputHandler* ih_ = InputHandler::instance();
	if (ih_->isKeyDown(SDLK_t)) {
		// mouse event
		toggleCombat_Movement();
	}
	GameState state_ = TheElementalMaze::instance()->gameState();
	switch (state_)
	{
	case gameST::MainMenu:
		break;
	case gameST::LOBBY:
		break;
	case gameST::START_EXPLORING:
		if (!getActivePan(Movement))
		{
			createPanel(Movement);
			//createPanel(Heroes);
			createPanel(Info);
			createPanel(Chat);
			string s = "Habia una vez una casita de una bruja hecha de chocolate, entonces Hansel dijo....";
			int k = s.size();
			ChatManager::instance()->addLine(s, linTy::Experience);
		}
		break;
	case gameST::EXPLORING:
		if (!getEnablePan(Movement))
		{
			togglePanel(Movement);
			if (getActivePan(Fight)) {
				removePanel(Fight);
			}
		}
		break;
	case gameST::COMBAT:
		if (!getActivePan(Fight))
		{
			togglePanel(Movement);
			createPanel(Fight);
			createPanel(Enemies);
			createPanel(Turns);
			toggleMinimap();
		}
		break;
	case gameST::END_COMBAT:
		if (getActivePan(Enemies))
		{
			toggleMinimap();
			removePanel(Enemies);
			TheElementalMaze::instance()->removeComponent(ecs::PanelTurns);
			checkHerosParty(); // check de puertas de la muerte
			TheElementalMaze::instance()->changeState(gameST::COMBAT);
		}
		break;
	case gameST::END_EXPLORING:
		removePanel(Movement);
		removePanel(Heroes);
		removePanel(Info);
		removeChat();
		break;
	default:
		break;
	}
}

Entity* Interfaz::getEntity()
{
	return entity_;
}

void Interfaz::checkActiveHeroButton(HeroNum nAct)
{
	ButtonPanel* b = allPanels[Heroes]->getButtonActive();
	if (b != nullptr) {
		ButtonHero* b_hero = dynamic_cast<ButtonHero*>(b);
		if (b_hero != nullptr && b_hero->getNumHero() != nAct) {
			b->turnOFF();
			removePanel(DDPan);
		}
	}
}

void Interfaz::checkHerosParty()
{
	bool changed = false;
	vector<Entity*> savedHeroes;
	PartyManager* c = TheElementalMaze::instance()->getPartyManager();
	std::vector<Hero*> heroes = c->getHeroes();
	auto n = heroes.size(); // max number of heros
	for (auto i = 0u; i < n; i++)
		if (heroes[i]->getDeathGate()) {
			allPanels[Heroes]->removeButton(i);
			changed = true;
		}
		else {
			savedHeroes.push_back(allPanels[Heroes]->getButton(i));
		}
	if (changed) allPanels[Heroes]->swapButtonList(savedHeroes);
}

