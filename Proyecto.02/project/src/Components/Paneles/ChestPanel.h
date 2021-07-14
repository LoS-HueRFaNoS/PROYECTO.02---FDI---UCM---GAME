#pragma once
#include "../../ecs/Component.h"
#include "../../GameObjects/ObjectChest.h"

class ChestPanel : public Component 
{
private:
	ObjectChest* objChest_ = nullptr;
	Chest* chest_;

public:
	ChestPanel() : Component(ecs::ChestPanel) {};
	ChestPanel(ObjectChest* ch) : Component(ecs::ChestPanel) { objChest_ = ch; };
	virtual ~ChestPanel() { /*delete objChest_; objChest_ = nullptr;*/ };

	void init() override;
	void update() override;
	void draw() override;

};
