#include "PartyManager.h"
#include "Item.h"
#include "Character.h"


PartyManager::PartyManager() :
	gold(0),
	manaPotions(5),
	healthPotions(5),
	items_(std::vector<Item*>(30)),
	heroes_(std::vector<Hero*>())
{
}

PartyManager::PartyManager(std::vector<Hero*> heroes, std::vector<Item*> items, int gold, int manaP, int healthP) :
	heroes_(heroes), 
	items_(items), 
	gold(gold),
	manaPotions(manaP),
	healthPotions(healthP)
{
}

PartyManager::~PartyManager()
{
	heroes_.clear();
	for (Item* i : items_) {
		delete i; i = nullptr;
	}
}

void PartyManager::reorderVector()
{
	for (auto it = heroes_.begin(); it != heroes_.end();) {
		if (!(*it))
			it = heroes_.erase(it);
		else
			it++;
	}
}

Hero* PartyManager::addHero(Hero* h, int pos)
{
	assert(pos < 4 && pos >= 0);

	if (pos < 4 && pos >= heroes_.size()) {
		heroes_.push_back(h);
		return nullptr;
	}
	else {
		Hero* oldHero = heroes_[pos];
		heroes_[pos] = h;
		return oldHero;
	}
}

bool PartyManager::addHero(Hero* h)
{
	if (heroes_.size() < 4) {
		heroes_.push_back(h);
		return true;
	}
	return false;
}

void PartyManager::removeHero(Hero* h)
{
	for (auto it = heroes_.begin(); it != heroes_.end();) {
		if ((*it) == h) {
			(*it)->disable();
			(*it) = nullptr;
			heroes_.erase(it);
			return;
		}
	}
}

void PartyManager::removeHero(int h)
{
	heroes_[h]->disable();
	heroes_[h] = nullptr;
}

void PartyManager::swapHeroes(int first, int second)
{
	if (!heroes_[first] || !heroes_[second])
		return;
	
	Hero* aux = heroes_[first];
	heroes_[first] = heroes_[second];
	heroes_[second] = aux;

	aux = nullptr;
}

void PartyManager::partyLost()
{
	for (Hero* h : heroes_)
		h->disable();
	heroes_.clear();
	for (Item* i : items_)
		delete i;
	items_.clear();
	gold = 0;
	manaPotions = 0;
	healthPotions = 0;
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
