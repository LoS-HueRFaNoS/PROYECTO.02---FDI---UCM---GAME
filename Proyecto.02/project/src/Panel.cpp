#include "Panel.h"
#include "../TheElementalMaze.h"
#include "InterfazManager.h"

void Panel::removeButtons()
{
	//for (auto it = buttonList.begin(); it != buttonList.end(); ++it)
	for (auto it = buttonList.begin(); it != buttonList.end(); )
	{
		(*it)->disable();
		it++;
	}
	buttonList.clear();
}