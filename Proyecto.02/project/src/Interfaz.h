#pragma once
#include <string>
#include <list>
#include "Component.h"
#include "Panel.h"

class InterfazManager;

using namespace std;

class Interfaz : public Component {

private:

	InterfazManager* iManager;
	vector<Panel*> allPanels;
	vector<Entity*> entitiesV;

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
	void createTargets(); //
	void createHabilities(); //

public:
	Interfaz(InterfazManager* i) :
		Component(ecs::Interfaz),
		allPanels(vector<Panel*>()),
		iManager(i)
	{};
	virtual ~Interfaz();

	void createPanel(idPanel panelID);
	void destroyPanel(idPanel panelID);

	void togglePanel(Panel* pan) { pan->toggleButtons(); }
	void togglePanel(idPanel panID) { togglePanel(allPanels[panID]); }

	void toggleCombat_Movement();

	virtual void init() override;
	virtual void update() override;
	virtual void draw() override {};

	Entity* getEntity();
private:
	Resources::TextureId getHeroTxt(uint number);
};