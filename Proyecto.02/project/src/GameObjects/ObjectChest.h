#pragma once
#include "../ecs/Entity.h"
#include "../Templates/interfaz/ObjectPanel.h"
#include "../Utilities/interfaz/MousePanelMecanics.h"
#include "../ecs/Manager.h"
#include "../Structures/Item.h"

class Item;

const int NUM_ITEMS_IN_CHEST = 20;

class ObjectChest : public EntityManager, public ObjectPanel, public MousePanelMecanics
{
private:
	SDL_Panel pan;
	Entity* fondo_ = nullptr;
	int numItems_ = NUM_ITEMS_IN_CHEST;
	void addTemplate();
	void example();
	void itemChest(vector<Item*> items);
	Chest* interiorCofre;
	bool generated = false;
	bool alreadyOpen = false;
public:
	ObjectChest(SDLGame* game) : EntityManager(game) {
		pan = game_->relativePanel(1470, 320, 420, 410, 1, 4, 30, 30, 10, 10, 0, 5);
	};

	ObjectChest(SDLGame* game, Chest* ch) : EntityManager(game) {
		pan = game_->relativePanel(1470, 320, 420, 410, 1, 4, 30, 30, 10, 10, 0, 5);
		interiorCofre = ch;
	};

	virtual ~ObjectChest() { 

		delete fondo_;
		fondo_ = nullptr;
		entities.clear();
	};

	void Init();
	void update();
	void draw();

	bool getAlreadyOpen() { return alreadyOpen; }
	void setAlreadyOpen(bool aO) { alreadyOpen = aO; }

	Chest* getChest() { return interiorCofre; }

};
