#pragma once
#include <string>
#include <list>
#include "Component.h"
#include "Panel.h"
#include "Cursor.h"

using namespace std;

class InterfazManager : public Component {
private:
	vector<Panel*> allPanels;
	Cursor* c_;

	Cursor* createCursor(Vector2D pos, uint width, uint height, Resources::TextureId image);
	Button* createButton(Panel* p, InterfazManager* im, CallBackOnClick* cb, Vector2D pos, uint width, uint height, Resources::TextureId image);
	/*void createButtonFight(Panel* p, AtkType type, PlayerMotion* plmot, Vector2D pos, uint width, uint height, Resources::TextureId image);
	void createButtonMovement(Panel * p, MovType type, PlayerMotion * plmot, Vector2D pos, uint width, uint height, Resources::TextureId image);
	void createButtonHeroes(Panel * p, HeroNum type, PlayerMotion * plmot, Vector2D pos, uint width, uint height, Resources::TextureId image);
	void createButtonInfo(Panel * p, Inf type, PlayerMotion * plmot, Vector2D pos, uint width, uint height, Resources::TextureId image);*/

	void createFight();
	void createMovement();
	void createHeroes();
	void createInfo();
	void createMinimap(){}; //
	void createInventory(); 
	void createHeroesStats(){}; //
	void createBigMap(){}; //
	void createTurns(){}; //
	void createSettings(){}; //
	void createChat(){}; //

public:
	InterfazManager() : 
		Component(ecs::InterfazManager), 
		allPanels(vector<Panel*>()), 
		c_(nullptr) 
	{};
	virtual ~InterfazManager();

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