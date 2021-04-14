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
	Cursor* c_;

	Cursor* createCursor(Vector2D pos, uint width, uint height, Resources::TextureId image);
	/*void createButtonFight(Panel* p, AtkType type, PlayerMotion* plmot, Vector2D pos, uint width, uint height, Resources::TextureId image);
	void createButtonMovement(Panel * p, MovType type, PlayerMotion * plmot, Vector2D pos, uint width, uint height, Resources::TextureId image);
	void createButtonHeroes(Panel * p, HeroNum type, PlayerMotion * plmot, Vector2D pos, uint width, uint height, Resources::TextureId image);
	void createButtonInfo(Panel * p, Inf type, PlayerMotion * plmot, Vector2D pos, uint width, uint height, Resources::TextureId image);*/

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

public:
	Interfaz(InterfazManager* i) :
		Component(ecs::InterfazManager),
		allPanels(vector<Panel*>()),
		c_(nullptr),
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