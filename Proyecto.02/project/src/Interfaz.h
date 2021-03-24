#pragma once
#include <string>
#include <list>
#include "Game.h"
#include "Panel.h"

using namespace std;

class Interfaz {
private:
	list<Panel*> allPanels;
	int contador;
	Game* g_;
	EntityManager* mngr_;

	Button* createButton(Panel* p, CallBackOnClick* cb);
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
	Interfaz(Game* juego, EntityManager* manager);
	~Interfaz();

	void createPanel(idPanel panelID);
	void destroyPanel(idPanel panelID);

};