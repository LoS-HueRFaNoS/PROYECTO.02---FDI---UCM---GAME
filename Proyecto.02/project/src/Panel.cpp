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