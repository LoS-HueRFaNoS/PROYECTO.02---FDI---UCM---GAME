#pragma once
#include <string>
#include <list>
#include "../ecs/Component.h"
#include "../Structures/Panel.h"

class Font;

class InterfazManager;

using namespace std;

class Interfaz : public Component {

private:

	InterfazManager* iManager;
	vector<Panel*> allPanels;

	void createFight();
	void createEnemies();
	void createMovement();
	void createHeroes();
	void createInfo();
	void createInventory();
	void createBigMap() {}; //
	void createTurns(); //
	void createSettings() {}; //
	void createChat();
	void createTargets(); //
	void createHabilities(); //

	void createMenuPrincipal();
	void createLobby();
	void createOptions();
	void createGuide();

	void toggleMinimap();

public:
	Interfaz(InterfazManager* i) :
		Component(ecs::Interfaz),
		allPanels(vector<Panel*>()),
		iManager(i)
	{};
	virtual ~Interfaz();

	void createPanel(idPanel panelID);
	void removePanel(idPanel panelID);
	void removeChat();
	void destroyPanel(idPanel panelID);

	void togglePanel(Panel* pan);
	void togglePanel(idPanel panID) { togglePanel(allPanels[panID]); };
	bool getEnablePan(idPanel panID);

	void toggleCombat_Movement();

	virtual void init() override;
	virtual void update() override;
	virtual void draw() override {};

	Entity* getEntity();
	bool getActivePan(idPanel pan) { return allPanels[pan] != nullptr; };
	void checkActiveHeroButton(HeroNum nAct);
	void checkHerosParty();
	void createFichaDD(uint nCharacter);

private:
	void initialize();
};