#include "Panel.h"
#include "../TheElementalMaze.h"
#include "InterfazManager.h"

void Panel::removeButtons()
{
	//for (auto it = buttonList.begin(); it != buttonList.end(); ++it)
	for (auto it = buttonList.begin(); it != buttonList.end(); it++)
	{
		(*it)->disable();
	}/*
	for (auto& b : buttonList) {
		TheElementalMaze::instance()->getUIManager()->removeEntity(b);
	}*/
	buttonList.clear();
}

ButtonPanel* Panel::getButtonActive()
{
	for (Button* b : buttonList) {
		ButtonPanel* b_ = dynamic_cast<ButtonPanel*>(b);
		if (b_ != nullptr) {
			if (b_->getActive()) {
				return b_;
			}
		}
	}
	return nullptr;
}
