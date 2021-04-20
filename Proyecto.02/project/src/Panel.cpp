#include "Panel.h"
#include "../TheElementalMaze.h"
#include "InterfazManager.h"

void Panel::removeButtons()
{
	for (Button* b : buttonList)
	{
		TheElementalMaze::instance()->getUIManager()->removeEntity(b);
	}
	buttonList.clear();
}