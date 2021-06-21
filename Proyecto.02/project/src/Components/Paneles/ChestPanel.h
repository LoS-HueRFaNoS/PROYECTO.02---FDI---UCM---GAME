#pragma once
#include "../../ecs/Component.h"
#include "../../GameObjects/ObjectChest.h"

class ChestPanel : public Component 
{
private:
	ObjectChest* chest_ = nullptr;

public:
	ChestPanel() : Component(ecs::ChestPanel) {};
	virtual ~ChestPanel() { delete chest_; chest_ = nullptr; };

	void init() override;
	void update() override;
	void draw() override;

};
