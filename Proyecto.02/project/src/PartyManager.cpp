#include "PartyManager.h"
#include "Item.h"
#include "Character.h"

PartyManager::PartyManager() :
	gold_(0),
	items_(std::vector<Item*>(30)),
	heroes_(std::vector<Hero*>(4))
{
}

PartyManager::PartyManager(std::vector<Hero*> heroes, std::vector<Item*> items, int gold) :
	heroes_(heroes), items_(items), gold_(gold)
{
}

PartyManager::~PartyManager()
{
	heroes_.clear();
	for (Item* i : items_) {
		delete i; i = nullptr;
	}
}

Hero* PartyManager::addHero(Hero* h, int pos)
{
	assert(pos < 4 && pos >= 0);

	if (heroes_[pos] == nullptr) {
		heroes_[pos] = h;
		return nullptr;
	}
	else {
		Hero* oldHero = heroes_[pos];
		heroes_[pos] = h;
		return oldHero;
	}
}

void PartyManager::addHero(Hero* h)
{
	for (int i = 0; i < heroes_.size(); i++) {
		if (!heroes_[i]) {
			heroes_[i] = h;
			return;
		}
	}
}

Item* PartyManager::addItem(Item* i, int pos)
{
	assert(pos < items_.size() && pos >= 0);

	if (items_[pos] == nullptr) {
		items_[pos] = i;
		return nullptr;
	}
	else {
		Item* oldItem = items_[pos];
		items_[pos] = i;
		return oldItem;
	}
}
