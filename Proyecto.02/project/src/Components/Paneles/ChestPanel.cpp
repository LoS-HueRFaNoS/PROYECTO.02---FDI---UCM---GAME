#include "ChestPanel.h"

void ChestPanel::init()
{
	chest_ = new ObjectChest(game_);
	chest_->Init();
}

void ChestPanel::update()
{
	chest_->update();
}

void ChestPanel::draw()
{
	chest_->draw();
}
