#include "Panel.h"
#include "../TheElementalMaze.h"
#include "InterfazManager.h"
#include <vector>
#include "Entity.h"

void Panel::removeButtons()
{
	for (auto it = buttonList.begin(); it != buttonList.end(); it++)
	{
		(*it)->disable();
	}
	buttonList.clear();
}

void Panel::removeButton(uint n)
{
	list<Entity*> savedHeroes;
	uint k = 0;
	auto nHeros = buttonList.size();
	for (auto it = buttonList.begin(); it != buttonList.end(); it++) {
		{
			if (k == n) {
				(*it)->disable();
			}
			else {
				savedHeroes.push_back(*it);
			}
			k++;
		}
	}
	buttonList.swap(savedHeroes);
}

ButtonPanel* Panel::getButtonActive()
{
	for (Entity* b : buttonList) {
		ButtonPanel* b_ = dynamic_cast<ButtonPanel*>(b);
		if (b_ != nullptr) {
			if (b_->getActive()) {
				return b_;
			}
		}
	}
	return nullptr;
}
