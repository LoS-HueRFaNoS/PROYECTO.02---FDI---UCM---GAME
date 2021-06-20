#pragma once
#include "../ecs/Entity.h"
#include "../Templates/interfaz/ObjectPanel.h"
#include "../Utilities/interfaz/MousePanelMecanics.h"
#include "../ecs/Manager.h"


const int NUM_ITEMS_IN_CHEST = 20;

class ObjectChest : public EntityManager, public ObjectPanel, public MousePanelMecanics
{
private:
	Entity* fondo_ = nullptr;
	int numItems_ = NUM_ITEMS_IN_CHEST;
	void addTemplate();

public:
	ObjectChest(SDLGame* game) : EntityManager(game) {};
	virtual ~ObjectChest() { 
		delete fondo_;
		fondo_ = nullptr;
		//entities.clear();
	};

	void Init();
	void update();
	void draw();

};
