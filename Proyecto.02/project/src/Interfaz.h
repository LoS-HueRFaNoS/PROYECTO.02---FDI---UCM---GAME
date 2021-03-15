#pragma once
#include <string>
#include <list>
#include "Game.h"
//#include "Panel.h"
using namespace std;

enum idPanel {Fight, Movement, Minimap, Heroes, Info, Inventory, HeroesStats, BigMap, Turns, Settings, Chat};
class Interfaz {
private:
	list<Panel*> allPanels;
	int contador;
	Game* game_;

	void createFight(){};
	void createMovement();
	void createMinimap(){};
	void createHeroes(){};
	void createInfo(){};
	void createInventory(){};
	void createHeroesStats(){};
	void createBigMap(){};
	void createTurns(){};
	void createSettings(){};
	void createChat(){};


public:
	Interfaz(Game* juego);
	~Interfaz();

	void createPanel(idPanel panelID);
	void destroyPanel(idPanel panelID);

};