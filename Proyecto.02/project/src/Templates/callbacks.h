#pragma once

class Interfaz;

// MENU
using namespace std;
typedef unsigned int uint;

class callbacks {
public:
	static void toggleThemeFondo();
	// pruebas (solo escriben por consola)
	static void pruebaGame0(Interfaz* app);
	static void pruebaGame1(Interfaz* app);
	static void pruebaGame2(Interfaz* app);
	static void pruebaGame3(Interfaz* app);
	// acceso a heroes
	static void heroType(uint numberHeroe);
	static void createDDPan(bool activated, uint numberHeroe);
	// acceso a movimiento
	static void movCommand(int movType);
	// acceso a informacion
	static void inventario(Interfaz* app);
	static void chat(Interfaz* app);
	static void configuracion(Interfaz* app);
	static void potionType(int potionType_);
	// acceso a combate
	static void combatType(int combatType_);
	static void addTarget(int attackType_);
	static void set_hability(int attackType_);
	// habilitar/deshabilitar paneles
	static void createPanel(bool active, int panelType);
	// acceso por menu
	static void startLobby(Interfaz* app);
	static void options(Interfaz* app);
	static void howToPlay(Interfaz* app);
	static void quit(Interfaz* app);

	//boton de lobby
	static void inventarioLobby(Interfaz* app);
	static void stash(Interfaz* app);
	static void shoppingHero(Interfaz* app , int her_);
	static void shop(Interfaz* app);
	static void shopping(Interfaz* app, int itemType, int itemid);
	static void startExp(Interfaz* app);
	static void shop_lobby(Interfaz* app);
	static void stash_lobby(Interfaz* app);
	static void inventarioToLobby(Interfaz* app);
	static void avanzarHeroes(Interfaz* app);
	static void avanzarItems(Interfaz* app);
	static void retrocederHeroes(Interfaz* app);
	static void retrocederItems(Interfaz* app);
	static void infoTienda(Interfaz* app, bool isHero, int id);
	static void sendHeroToStash(Interfaz* app, int heroid);
	static void sendHeroToParty(Interfaz* app, int heroid);
	static void showHeroToParty(Interfaz* app, int heroid);
	static void backToMenu(Interfaz* app);
	static void sellStashItem(Interfaz* app, int itemid);
	static void showSellButton(Interfaz* app, int itemid);
	static void showSendToStash(Interfaz* app, int itemid);
	static void sendToStash(Interfaz* app, int itemid);
	static void sendToInventory(Interfaz* app, int itemid);
	static void closeMessage();
};