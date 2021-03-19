#pragma once
#include <string>
#include <list>
#include "SDLGame.h"
#include "Panel.h"

using namespace std;

class Interfaz {
private:
	list<Panel*> allPanels;
	int contador;
	SDLGame* game_;
	EntityManager* mngr_;

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
	Interfaz(SDLGame* juego, EntityManager* manager);
	~Interfaz();

	void createPanel(idPanel panelID);
	void destroyPanel(idPanel panelID);

};