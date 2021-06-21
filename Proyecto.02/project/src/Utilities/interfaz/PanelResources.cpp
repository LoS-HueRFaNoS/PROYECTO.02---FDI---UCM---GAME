#include "PanelResources.h"

void PanelResources::removeElements()
{
	for (auto it = list_.begin(); it != list_.end(); it++)
	{
		(*it)->disable();
	}
	list_.clear();
}

void PanelResources::removeElement(uint n)
{
	uint k = 0;
	for (auto it = list_.begin(); it != list_.end(); it++) {
		{
			if (k == n) {
				(*it)->disable();
			}
			k++;
		}
	}
}

void PanelResources::swapElementsList(vector<Entity*> savedHeroes)
{
	list_.swap(savedHeroes);
}

ButtonPanel* PanelResources::getButtonActive()
{
	for (Entity* b : list_) {
		ButtonPanel* b_ = dynamic_cast<ButtonPanel*>(b);
		if (b_ != nullptr) {
			if (b_->getActive()) {
				return b_;
			}
		}
	}
	return nullptr;
}

// HACER ESTE METODO PARA CUALQUIER PANEL (p.e. habilidades)
//void Interfaz::checkActiveHeroButton(HeroNum nAct)
//{
//	ButtonPanel* b = allPanels[Heroes]->getButtonActive();
//	if (b != nullptr) {
//		ButtonHero* b_hero = dynamic_cast<ButtonHero*>(b);
//		if (b_hero != nullptr && b_hero->getNumHero() != nAct) {
//			b->turnOFF();
//			removePanel(DDPan);
//		}
//	}
//}
