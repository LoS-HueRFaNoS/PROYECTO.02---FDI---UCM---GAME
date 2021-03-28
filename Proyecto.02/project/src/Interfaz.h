#pragma once
#include <string>
#include <list>
#include "Game.h"
#include "Panel.h"
#include "Cursor.h"

using namespace std;

class Interfaz {
private:
	list<Panel*> allPanels;
	int contador;
	Game* g_;
	EntityManager* mngr_;
	Cursor* c_;

	Cursor* createCursor(Vector2D pos, uint width, uint height, Resources::TextureId image);
	Button* createButton(Panel* p, CallBackOnClick* cb, Vector2D pos, uint width, uint height, Resources::TextureId image);
	void createFight();
	void createMovement();
	void createMinimap(){};
	void createHeroes();
	void createInfo();
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