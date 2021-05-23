#include "PartyManager.h"
#include "../../Structures/Item.h"
#include "../../GameObjects/Character.h"


PartyManager::PartyManager() :
	gold(0),
	manaPotions(5),
	healthPotions(5),
	items_(std::vector<Item*>(0)),
	heroes_(std::vector<Hero*>(4, nullptr))
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
	for (int i = 0; i < 4; i++) {
		if (!heroes_[i]) {
			heroes_[i] = h;
			return true;
		}
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
	assert(/*pos < items_.size() &&*/ pos >= 0);
	items_.resize(items_.size() + 1);
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

void PartyManager::changeItemWithHero(int index, int hero)
{
	if (!heroes_[hero] || !items_[index])
		return;

	Item* it = items_[index];
	ItemType t = it->getItemType();
	Item* ret = nullptr;

	if (t) {
		Armor* a = heroes_[hero]->getArmor();
		heroes_[hero]->giveArmor((Armor*)it);
		if (a)
			ret = a;
	}
	else {
		Weapon* w = heroes_[hero]->getWeapon();
		heroes_[hero]->giveWeapon((Weapon*)it);
		if (w->getWeaponId() != weaponId::DESARMADO)
			ret = w;
	}
	if (ret)
		items_[index] = ret;
}

void PartyManager::usePotion(int hero, bool mana)
{
	if (mana) {
		if (manaPotions > 0) {
			heroes_[hero]->recieveMana(5);
			manaPotions--;
		}
		else
			cout << "Not enough mana potions\n";
	}
	else {
		if (healthPotions > 0) {
			heroes_[hero]->recieveHealing(5);
			healthPotions--;
		}
		else
			cout << "Not enough health potions\n";
	}
}

void PartyManager::usePotion(Hero* hero, bool mana)
{
	int i = 0;
	for (Hero* h : heroes_) {
		if (h == hero) {
			usePotion(i, mana);
			return;
		}
		i++;
	}
}
