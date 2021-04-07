#pragma once
#include <string>
#include <list>
#include "Game.h"
#include "Panel.h"
#include "Cursor.h"

using namespace std;

class Interfaz {
private:
	vector<Panel*> allPanels; //TODO: cambiar por muchos atributos xd
	int contador;
	Game* g_;
	EntityManager* mngr_; 
	Cursor* c_;

	Cursor* createCursor(Vector2D pos, uint width, uint height, Resources::TextureId image);
	void createButtonFight(Panel* p, AtkType type, PlayerMotion* plmot, Vector2D pos, uint width, uint height, Resources::TextureId image);
	void createButtonMovement(Panel * p, MovType type, PlayerMotion * plmot, Vector2D pos, uint width, uint height, Resources::TextureId image);
	void createButtonHeroes(Panel * p, HeroNum type, PlayerMotion * plmot, Vector2D pos, uint width, uint height, Resources::TextureId image);
	void createButtonInfo(Panel * p, Inf type, PlayerMotion * plmot, Vector2D pos, uint width, uint height, Resources::TextureId image);

	void createFight(PlayerMotion* plmot);
	void createMovement(PlayerMotion* plmot);
	void createMinimap(){};
	void createHeroes(PlayerMotion* plmot);
	void createInfo(PlayerMotion* plmot);
	void createInventory(){};
	void createHeroesStats(){};
	void createBigMap(){};
	void createTurns(){};
	void createSettings(){};
	void createChat(){};

public:
	Interfaz(Game* juego, EntityManager* manager, PlayerMotion* plmot);
	~Interfaz();

	void togglePanel(idPanel panID) {
		allPanels[panID]->toggleButtons();
	}

	void createPanel(idPanel panelID, PlayerMotion* plmot);
	void destroyPanel(idPanel panelID);

};