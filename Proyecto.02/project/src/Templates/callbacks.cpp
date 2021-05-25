#include <iostream>
#include "callbacks.h"
#include "../ecs/ecs.h"
#include "../ecs/Entity.h"
#include "../ecs/Component.h"
#include "../Components/Interfaz.h"
#include "../Game.h"
#include "../Managers/game/LobbyManager.h"
#include "../Managers/game/ItemManager.h"

// ----------------------------------------------------

#pragma region SettingsButtons
#include "../Game.h"

void callbacks::toggleThemeFondo() {
	Game::Instance()->getFondo()->changeTheme();
}

#pragma endregion

// ----------------------------------------------------

#pragma region PruebasBotones


void callbacks::pruebaGame0(Interfaz* app) {
	std::cout << "pruebaGame0" << std::endl;
}
void callbacks::pruebaGame1(Interfaz* app) {
	std::cout << "pruebaGame1" << std::endl;
}
void callbacks::pruebaGame2(Interfaz* app) {
	std::cout << "pruebaGame2" << std::endl;
}
void callbacks::pruebaGame3(Interfaz* app) {
	std::cout << "pruebaGame3" << std::endl;
}

#pragma endregion

// ----------------------------------------------------

#pragma region PanelHeroes
#include "../Managers/TheElementalMaze.h"
#include "../Managers/game/CombatManager.h"
#include "../Components/Interfaz.h"

void callbacks::heroType(uint numberHeroe) {
	CombatManager* c = GETCMP2(TheElementalMaze::instance(), CombatManager);
	string name = c->getCharacter(numberHeroe, charTy::HERO)->name();
	std::cout << "heroe " << numberHeroe << ": " << name << std::endl;
}

void callbacks::createDDPan(bool active, uint numberHeroe) {
	Interfaz* i = GETCMP2(TheElementalMaze::instance(), Interfaz);
	
	if (!active) i->createFichaDD(numberHeroe);
	else if (active) i->removePanel(DDPan);
}

#pragma endregion

// ----------------------------------------------------

#pragma region PanelMovimiento
#include "../Managers/TheElementalMaze.h"
#include "../Components/PlayerMotion.h"

void callbacks::movCommand(int movType)
{
	PlayerMotion* p = GETCMP2(TheElementalMaze::instance()->getPlayer(), PlayerMotion);

	switch (movType)
	{
	case 0:
		std::cout << "has girado a la derecha" << std::endl;
		p->rotarDerecha();
		break;
	case 1:
		std::cout << "has girado a la izquierda" << std::endl;
		p->rotarIzquierda();
		break;
	case 2:
		std::cout << "has avanzado" << std::endl;
		p->avanzar();
		break;
	case 3:
		std::cout << "has interactuado" << std::endl;
		break;
	default:
		break;
	}
}

#pragma endregion

// ----------------------------------------------------

#pragma region PanelInformation
#include "../Managers/TheElementalMaze.h"
#include "../Managers/game/PartyManager.h"
#include "../Managers/game/CombatManager.h"

void callbacks::inventario(Interfaz* app)
{
	//app->createPanel(Inventory);
	std::cout << "has abierto el inventario" << std::endl;
}

void callbacks::configuracion(Interfaz* app)
{
	//app->createPanel(Settings);
	std::cout << "has abierto la configuración" << std::endl;
}

void callbacks::potionType(int potionType_)
{
	CombatManager* c = GETCMP2(TheElementalMaze::instance(), CombatManager); // falta paso intermedio para guardar la habilidad y seleccionar enemigos
	GameState gameST = TheElementalMaze::instance()->gameState();
	switch (potionType_)
	{
	case 0:
		std::cout << "has usado la pocion de vida" << std::endl;
		if (gameST == gameST::COMBAT) c->sendKeyEvent(-6); //indice de la habilidad
		else if (gameST == gameST::EXPLORING) callbacks::set_hability(-6);
		break;
	case 1:
		std::cout << "has usado la pocion de mana" << std::endl;
		if (gameST == gameST::COMBAT) c->sendKeyEvent(-5); //indice de la habilidad
		else if (gameST == gameST::EXPLORING) callbacks::set_hability(-5);
		break;
	case 2:
		std::cout << "has usado la pocion de resurreccion" << std::endl;
		//c->sendKeyEvent(-7); //indice de la habilidad
		break;
	default:
		break;
	}
}

#pragma endregion

// ----------------------------------------------------

#pragma region PanelResources
#include "../Managers/TheElementalMaze.h"
#include "../Components/Interfaz.h"

void callbacks::createPanel(bool active, int panelType)
{
	Interfaz* i_ = GETCMP2(TheElementalMaze::instance(), Interfaz);

	if (!active) i_->createPanel((idPanel)panelType);
	else if (active) i_->removePanel((idPanel)panelType);
}

#pragma endregion

// ----------------------------------------------------

#pragma region PanelChatMapa

void callbacks::chat(Interfaz* app)
{
	std::cout << "has usado el boton de chat" << std::endl;
}

#pragma endregion

// ----------------------------------------------------

#pragma region PanelCombate
#include "../Managers/TheElementalMaze.h"
#include "../Managers/game/CombatManager.h"

void callbacks::combatType(int combatType_)
{
	Interfaz* i = GETCMP2(TheElementalMaze::instance(), Interfaz);
	CombatManager* c = GETCMP2(TheElementalMaze::instance(), CombatManager);
	switch (combatType_)
	{
	case 0:
		if (c->getState() == ACTION_PHASE_SPELL) {
			std::cout << "ataque cuerpo a cuerpo" << std::endl;
			if (!i->getActivePan(WeaponsAttacks)) callbacks::createPanel(false, WeaponsAttacks);
			if (i->getEnablePan(Fight)) i->togglePanel(Fight);
		}
		else
			std::cout << "ERROR: aun no has comenzado tu turno" << std::endl;
		break;
	case 1:
		if (c->getState() == ACTION_PHASE_SPELL) {
			std::cout << "has seleccionado una habilidad" << std::endl;
			if (!i->getActivePan(Habilities)) callbacks::createPanel(false, Habilities);
			if (i->getEnablePan(Fight)) i->togglePanel(Fight);
		}
		else
			std::cout << "ERROR: aun no has comenzado tu turno" << std::endl;
		break;
	case 2:
		c->sendKeyEvent(-1);
		std::cout << "Pulsaste enter" << std::endl;
		break;
	case 3:
		c->sendKeyEvent(-4);
		std::cout << "huir del combate" << std::endl;
		break;
	default:
		break;
	}
}

void callbacks::addTarget(int objetive_) // -1 para volver atrás
{
	CombatManager* c = GETCMP2(TheElementalMaze::instance(), CombatManager);
	c->sendKeyEvent(objetive_); // sólo uno
	Interfaz* i = GETCMP2(TheElementalMaze::instance(), Interfaz);
	// cambia a combate
	if (i->getActivePan(Targets)) i->removePanel(Targets);
	if (!i->getEnablePan(Fight)) i->togglePanel(Fight);
	std::cout << "has fijado tu objetivo" << std::endl;
}

void callbacks::set_hability(int hability_)
{
	CombatManager* c = GETCMP2(TheElementalMaze::instance(), CombatManager); // falta paso intermedio para guardar la habilidad y seleccionar enemigos
	c->sendKeyEvent(hability_); //indice de la habilidad
	
	Interfaz* i = GETCMP2(TheElementalMaze::instance(), Interfaz);
	if (i->getActivePan(Habilities)) i->removePanel(Habilities);
	if (i->getActivePan(WeaponsAttacks)) i->removePanel(WeaponsAttacks);

	// team or single target
	if (c->getState() != END_TURN) {
		// abre panel selecionar objetivo
		callbacks::createPanel(false, Targets);
	}
	else { 
		if (!i->getEnablePan(Fight)) i->togglePanel(Fight); 
	}
}

#pragma endregion

// ----------------------------------------------------
#pragma region MenuPrincipal
void callbacks::startLobby(Interfaz* app)
{
	std::cout << "startLobby se ha activado\n";
	if (app->getActivePan(MenuPrincipal)) 	app->removePanel(MenuPrincipal);
	if (TheElementalMaze::instance()->gameState() != gameST::MainMenu)
	{
		TheElementalMaze::instance()->backFromDungeon();
	}
	else if (!TheElementalMaze::instance()->isFirstLobbyCreated())
	{
		TheElementalMaze::instance()->firstLobby();
	
	}

	TheElementalMaze::instance()->changeState(gameST::DURING_LOBBY);
	cout << "LOBBY REACHED" << endl;
	
	app->createPanel(Lobby);
	
	
}
void callbacks::startExp(Interfaz* app)
{
	PartyManager* paManager = TheElementalMaze::instance()->getPartyManager();
	bool partyCompleta = true;
	for (int i = 0; i < 4; ++i)
	{
		if (paManager->getHeroes()[i] == nullptr) partyCompleta = false;
	}
	if (partyCompleta)
	{
		if (app->getActivePan(DDPan))
			app->removePanel(DDPan);

		app->removePanel(Lobby);
		//app->removePanel(Heroes);
		TheElementalMaze::instance()->changeState(gameST::START_EXPLORING);
		

		std::cout << "startExploration se ha activado\n";
	}
}
void callbacks::options(Interfaz* app)
{
	app->togglePanel(MenuPrincipal);
	app->togglePanel(Options);
	std::cout << "options se ha activado\n";
}
void callbacks::howToPlay(Interfaz* app)
{
	app->togglePanel(MenuPrincipal);
	app->togglePanel(HowToPlay);
}
void callbacks::quit(Interfaz* app)
{
	Game::Instance()->exitGame();
	std::cout << "quit se ha activado\n";
}

void callbacks::shoppingHero(Interfaz* app, int her)
{
	LobbyManager* lo = TheElementalMaze::instance()->getLobbyManager();
	lo->buyHero(her);
	std::cout << "Heroe comprado" << std::endl;
	app->togglePanel(Shop);
	app->createPanel(Shop);
}
void callbacks::shopping(Interfaz* app, int itemType, int itemid)
{
	LobbyManager* lo = TheElementalMaze::instance()->getLobbyManager();
	lo->buyItem(itemid);
	std::cout << "Objeto comprado" << std::endl;
	app->togglePanel(Shop);
	app->createPanel(Shop);
}

void callbacks::stash(Interfaz* app)
{
	if (app->getActivePan(DDPan))
		app->removePanel(DDPan);
	app->removePanel(Lobby);
	app->removePanel(Heroes);
	app->createPanel(StashPanel);
	app->createPanel(ButtonHeroToPartyPanel);
	app->togglePanel(ButtonHeroToPartyPanel);
	std::cout << " vamos al stash"<< std::endl;
}
void callbacks::shop(Interfaz* app)
{
	if (app->getActivePan(DDPan))
		app->removePanel(DDPan);
	app->removePanel(Lobby);
	app->removePanel(Heroes);
	app->createPanel(Shop);
	std::cout << "vamos a la tienda" << std::endl;
}

void callbacks::shop_lobby(Interfaz* app)
{
	app->togglePanel(Shop);
	app->createPanel(Lobby);
	app->togglePanel(infoTiendaPanel);
	std::cout << "volvemos al lobby desde la tienda" << std::endl;
}
void callbacks::stash_lobby(Interfaz* app)
{
	if (app->getActivePan(ButtonHeroToPartyPanel))
		app->removePanel(ButtonHeroToPartyPanel);
	if (app->getActivePan(SellButtonPanel))
		app->removePanel(SellButtonPanel);
	app->removePanel(StashPanel);
	app->createPanel(Lobby);
	std::cout << "volvemos al lobby desde el stash" << std::endl;
}
void callbacks::avanzarHeroes(Interfaz* app)
{
	app->avPagHeroes();
	app->togglePanel(StashPanel);
	app->createPanel(StashPanel);

	std::cout << "mostramos más héroes" << std::endl;
}
void callbacks::avanzarItems(Interfaz* app)
{
	app->avPagItems();
	app->togglePanel(StashPanel);
	app->createPanel(StashPanel);

	std::cout << "mostramos más items" << std::endl;
}
void callbacks::retrocederHeroes(Interfaz* app)
{
	app->rePagHeroes();
	app->togglePanel(StashPanel);
	app->createPanel(StashPanel);

	std::cout << "retrocedemos en la página de héroes" << std::endl;
}
void callbacks::retrocederItems(Interfaz* app)
{
	app->rePagItems();
	app->togglePanel(StashPanel);
	app->createPanel(StashPanel);

	std::cout << "retrocedemos en la página de items" << std::endl;
}

void callbacks::infoTienda(Interfaz* app,bool isHero, int id)
{
	LobbyManager* lo = TheElementalMaze::instance()->getLobbyManager();
	if (!isHero)
	{
		app->setNameItem(lo->getLobbyStore()->items[id]->item->getName());
		app->setDescrItem(lo->getLobbyStore()->items[id]->item->getDescription());
		app->togglePanel(infoTiendaPanel);
		app->createPanel(infoTiendaPanel);	
	}
	std::cout << "Descripción de la tienda actualizada" << std::endl;
	
}
void callbacks::sendHeroToStash(Interfaz* app, int heroid)
{
	app->removePanel(DDPan);
	app->removePanel(Heroes);
	LobbyManager* lo = TheElementalMaze::instance()->getLobbyManager();
	//PartyManager* pa = TheElementalMaze::instance()->getPartyManager();
	//EntityManager* en = TheElementalMaze::instance()->getEntityMangr();
	//SDLGame* game = TheElementalMaze::instance()->getSDLGame();
	lo->heroFromPartyToStash(heroid);
	app->createPanel(Heroes);
}
void callbacks::sendHeroToParty(Interfaz* app, int heroid)
{
	app->removePanel(StashPanel);
	app->removePanel(ButtonHeroToPartyPanel);
	PartyManager* paManager = TheElementalMaze::instance()->getPartyManager();
	int hueco = -1;
	for (int i = 0; i < 4; ++i)
	{
		if (paManager->getHeroes()[i] == nullptr) hueco = i;
	}
	if (hueco != -1)
	{
		LobbyManager* lo = TheElementalMaze::instance()->getLobbyManager();
		lo->addHeroToParty(heroid, hueco);
	}
	app->createPanel(StashPanel);
}
void callbacks::showHeroToParty(Interfaz* app, int heroid)
{
	if (app->getActivePan(ButtonHeroToPartyPanel)) app->removePanel(ButtonHeroToPartyPanel);
	app->setSelectedHeroToParty(heroid);
	app->createPanel(ButtonHeroToPartyPanel);
}

void callbacks::backToMenu(Interfaz* app)
{
	if (app->getActivePan(DDPan)) app->removePanel(DDPan);
	app->removePanel(Lobby);
	app->removePanel(Heroes);
	app->createPanel(MenuPrincipal);
	TheElementalMaze::instance()->changeState(gameST::MainMenu);
	std::cout << "vamos al menu" << std::endl;
}

void callbacks::inventarioLobby(Interfaz* app)
{
	if (app->getActivePan(DDPan)) app->removePanel(DDPan);
	app->removePanel(Lobby);
	app->removePanel(Heroes);
	app->createPanel(InventoryLobby);
	if (app->getActivePan(UnequipPanel)) app->removePanel(UnequipPanel);
	std::cout << "vamos al inventario" << std::endl;
}
void callbacks::sellStashItem(Interfaz* app,int itemid)
{
	LobbyManager* lo = TheElementalMaze::instance()->getLobbyManager();
	lo->sellItemFromStash(itemid);
	std::cout << "Objeto vendido" << std::endl;
	app->removePanel(StashPanel);
	app->createPanel(StashPanel);
	app->removePanel(SellButtonPanel);
}
void callbacks::showSellButton(Interfaz* app, int itemid)
{
	if (app->getActivePan(SellButtonPanel))
		app->removePanel(SellButtonPanel);
	app->setSelectedItem(itemid);
	app->createPanel(SellButtonPanel);
	if (app->getActivePan(UnequipPanel)) app->removePanel(UnequipPanel);
}
#include "../Components/Tutorial.h"
void callbacks::closeMessage()
{
	TutorialManager* t = GETCMP3(TheElementalMaze::instance(), ecs::Tutorial, TutorialManager);
	t->exitMessage();
	std::cout << "saliendo del mensaje del tutorial" << std::endl;
}

void callbacks::inventarioToLobby(Interfaz* app)
{
	if (app->getActivePan(DDPan)) app->removePanel(DDPan);
	if (app->getActivePan(sendToStashPanel)) app->removePanel(sendToStashPanel);
	if (app->getActivePan(UnequipPanel)) app->removePanel(UnequipPanel);
	app->removePanel(InventoryLobby);
	app->removePanel(Heroes);
	app->createPanel(Lobby);
	std::cout << "vamos al lobby" << std::endl;
}

void callbacks::showSendToStash(Interfaz* app, int itemid){
	if (app->getActivePan(sendToStashPanel)) app->removePanel(sendToStashPanel);
	app->setSelectedInventoryItem(itemid);
	app->createPanel(sendToStashPanel);
}

void callbacks::sendToStash(Interfaz* app,int itemid)
{
	PartyManager* pa = TheElementalMaze::instance()->getPartyManager();
	LobbyManager* lo = TheElementalMaze::instance()->getLobbyManager();
	pa->itemFromInventoryToStash(itemid);
	app->removePanel(sendToStashPanel);
	app->removePanel(InventoryLobby);
	app->createPanel(InventoryLobby);
	std::cout << "Enviar objeto al stash" << std::endl;
}

void callbacks::sendToInventory(Interfaz* app, int itemid)
{
	PartyManager* pa = TheElementalMaze::instance()->getPartyManager();
	LobbyManager* lo = TheElementalMaze::instance()->getLobbyManager();
	lo->itemFromStashToInventory(itemid);
	app->removePanel(StashPanel);
	app->createPanel(StashPanel);
	app->removePanel(SellButtonPanel);
	std::cout << "Enviar objeto al stash" << std::endl;
}
void callbacks::showUnequipButton(Interfaz* app,bool isWeapon_, int heroid)
{
	PartyManager* pa = TheElementalMaze::instance()->getPartyManager();
	LobbyManager* lo = TheElementalMaze::instance()->getLobbyManager();
	if (app->getActivePan(UnequipPanel)) app->removePanel(UnequipPanel);
	if (isWeapon_ && pa->getHeroes()[heroid]->getWeapon()->getWeaponId() == wID::DESARMADO) return;
	app->setSelectedInventoryHero(heroid);
	app->setIsWeapon(isWeapon_);
	app->createPanel(UnequipPanel);
}
void callbacks::unequip(Interfaz* app, bool isWeapon, int heroid)
{
	PartyManager* pa = TheElementalMaze::instance()->getPartyManager();
	LobbyManager* lo = TheElementalMaze::instance()->getLobbyManager();
	ItemManager* itemManager_ = TheElementalMaze::instance()->getItemManager();
	Item* item = nullptr;
	bool espacio = false;
	if (isWeapon)
	item = pa->getHeroes()[heroid]->getWeapon();
	else
	item = pa->getHeroes()[heroid]->getArmor();
	espacio = pa->addItem(item);
	if (espacio)
	{
		if (isWeapon) pa->getHeroes()[heroid]->giveWeapon(itemManager_->getWeaponFromId(wID::DESARMADO));
		else pa->getHeroes()[heroid]->removeArmor(); //giveArmor(itemManager_->getArmorFromId(aID::);
	}
	app->removePanel(UnequipPanel);
	if (app->getActivePan(InventoryLobby))
	{
		app->removePanel(InventoryLobby);
		app->createPanel(InventoryLobby);
	}
	else if (app->getActivePan(Inventory))
	{
		app->removePanel(Inventory);
		app->createPanel(Inventory);
	}
}
#include "../Managers/game/LobbyManager.h"
#include"../GameObjects/Character.h"

#pragma endregion
//void callbacks::start(Game* app) // previo app->setLevel(lvl);
//{
//	/*app->getMachine()->setAction(goGame);
//	app->setLevel(FIRST_LVL);
//	app->setSalida(true);*/
//}
//
//void callbacks::exitGame(Game* app)
//{
//	/*app->getMachine()->setAction(goBack);
//	app->setSalida(true);*/
//}
//
//void callbacks::exitApp(Game* app)
//{
//	/*app->getMachine()->setAction(shutDown);
//	app->setSalida(true);*/
//}
//
//void callbacks::backToMenu(Game* app)
//{
//	/*app->getMachine()->setAction(pauseToMenu);
//	app->setSalida(true);*/
//}
//
//void callbacks::saveOpt(Game* app)
//{
//	/*app->getMachine()->setAction(saveOption);
//	MenuState* menu = static_cast<MenuState*>(app->getMachine()->currentState());
//	MenuButton* mb = menu->engine->getActual();
//	mb->setHidden(true);
//	menuState ms = mb->getMenuState();
//	menu->engine->setState(ms);
//	static_cast<PauseState*>(menu)->clearUserOpt();*/
//}
//
//void callbacks::save(Game* app)
//{
//	/*app->getMachine()->setAction(saveCurrent);
//	app->setSalida(true);*/
//}
//
//void callbacks::load(Game* app)
//{
//	/*app->getMachine()->setAction(loadOption);
//	app->setSalida(true);*/
//}
//
//void callbacks::change(Game* app)
//{
//	/*MenuState* menu = static_cast<MenuState*>(app->getMachine()->currentState());
//	MenuButton* mb = menu->engine->getActual();
//	menuState ms = mb->getMenuState();
//	menu->engine->setState(ms);
//	menu->setRdy(false);*/
//}
//
//void callbacks::startLvl(Game* app)
//{
//	/*MenuState* menu = static_cast<MenuState*>(app->getMachine()->currentState());
//	uint n = menu->engine->getActual()->getLvl();
//	app->getMachine()->setAction(goGame);
//	app->setLevel(n);
//	app->setSalida(true);*/
//}
//
//// IN-GAME
//void callbacks::game_over(Game* app)
//{
//	/*app->getMachine()->setAction(goGameOver);
//	app->setSalida(true);*/
//}
//
//void callbacks::lose_life(Game* app)
//{
//	/*app->getMachine()->setAction(goLoseLife);
//	app->setSalida(true);*/
//}
//
//void callbacks::stage_complete(Game* app)
//{
//	/*app->getMachine()->setAction(goStageClear);
//	app->setSalida(true);*/
//}
//
//void callbacks::game_complete(Game* app)
//{
//	/*app->getMachine()->setAction(goGameClear);
//	app->setSalida(true);*/
//}