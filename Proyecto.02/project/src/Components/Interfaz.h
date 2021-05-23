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
	std::vector<Panel*> allPanels;
	uint pagHeroes = 0;
	uint pagItems = 0;
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
	void createShop();
	void createStash();
	void createInfoTienda();
	void toggleMinimap();
	string nameItemTienda;
	string descrItemTienda;
	void checkAndDeletePanel(idPanel id);
	void createHeroToPartyPanel();
	int selectedHeroToParty;
public:
	Interfaz(InterfazManager* i) :
		Component(ecs::Interfaz),
		allPanels(std::vector<Panel*>(maxPanels, nullptr)),
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
	void avPagHeroes();
	void rePagHeroes();
	void avPagItems();
	void rePagItems();
	void toggleCombat_Movement();

	virtual void init() override;
	virtual void update() override;
	virtual void draw() override {};

	Entity* getEntity();
	bool getActivePan(idPanel pan) { return allPanels[pan] != nullptr; };
	void checkActiveHeroButton(HeroNum nAct);
	void checkHerosParty();
	void createFichaDD(uint nCharacter);

	void setNameItem(string name_) { nameItemTienda = name_; }
	void setDescrItem(string descr_) { descrItemTienda = descr_; }
	void setSelectedHeroToParty(int selectedHero) { selectedHeroToParty = selectedHero; }
};