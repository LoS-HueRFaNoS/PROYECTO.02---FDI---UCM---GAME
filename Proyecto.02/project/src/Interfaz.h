#pragma once
#include <string>
#include <list>
#include "Component.h"
#include "Panel.h"
#include "Cursor.h"

class InterfazManager;

using namespace std;

class Interfaz : public Component {

private:

	InterfazManager* iManager;
	vector<Panel*> allPanels;

	void createFight();
	void createMovement();
	void createHeroes();
	void createInfo();
	void createMinimap() {}; //
	void createInventory();
	void createHeroesStats() {}; //
	void createBigMap() {}; //
	void createTurns() {}; //
	void createSettings() {}; //
	void createChat() {}; //
	void createMenuPrincipal() ; //
	void createLobby() ; //
public:
	Interfaz(InterfazManager* i) :
		Component(ecs::InterfazManager),
		allPanels(vector<Panel*>()),
		iManager(i)
	{};
	virtual ~Interfaz();

	void createPanel(idPanel panelID);
	void destroyPanel(idPanel panelID);

	void togglePanel(idPanel panID) {
		allPanels[panID]->toggleButtons();
	}

	virtual void init() override;
	virtual void update() override {};
	virtual void draw() override {};

	Entity* getEntity();
};