#include "ChestPanel.h"

void ChestPanel::init()
{
	//objChest_ = new ObjectChest(game_, chest_);
	objChest_->Init();
}

void ChestPanel::update()
{
	objChest_->update();
}

void ChestPanel::draw()
{
	objChest_->draw();
}
