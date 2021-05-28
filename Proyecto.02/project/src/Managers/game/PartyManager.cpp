#include "PartyManager.h"
#include "LobbyManager.h"
#include "../TheElementalMaze.h"
#include "../../Structures/Item.h"
#include "../../GameObjects/Character.h"
#include "ChatManager.h"


PartyManager::PartyManager() :
	gold(0),
	manaPotions(5),
	healthPotions(5),
	items_(std::vector<Item*>(NUM_ITEMS)),
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
	for (Item* i : items_) {
		delete i; i = nullptr;
	}
	heroes_.clear();
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
	for (int i = 0; i < 4; i++) {
		if (heroes_[i] == h) {
			heroes_[i]->disable();
			heroes_[i] = nullptr;
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
	clearItems();
	heroes_ = std::vector<Hero*>(4, nullptr);
	gold = 0;
	manaPotions = 0;
	healthPotions = 0;
}

void PartyManager::clearItems()
{
	items_.clear();
	items_ = std::vector<Item*>(NUM_ITEMS);
}

bool PartyManager::addItem(Item* i)
{
	int iterator = 0;
	while (iterator < NUM_ITEMS && items_[iterator] != nullptr)
		iterator++;
	if (items_[iterator] == nullptr)
	{
		items_[iterator] = i;
		return true;
	}
	else {
		return false;
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
		ChatManager::instance()->addLine(std::to_string(manaPotions) + " mana potions left", linCol::White);
	}
	else {
		if (healthPotions > 0) {
			heroes_[hero]->recieveHealing(5);
			healthPotions--;
		}
		else
			cout << "Not enough health potions\n";
		ChatManager::instance()->addLine(std::to_string(healthPotions) + " health potions left", linCol::White);
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

void PartyManager::itemFromInventoryToStash(int itemIndex)
{
	assert(itemIndex >= 0 && itemIndex <= 25);

	LobbyManager* lo = TheElementalMaze::instance()->getLobbyManager();
	Item* item = items_[itemIndex];
	bool change = false;
	int i = 0;
	while (i < lo->getPlayerStash()->items.size() && lo->getPlayerStash()->items[i] != nullptr)
		i++;
	if (i < lo->getPlayerStash()->items.size() && lo->getPlayerStash()->items[i] == nullptr)
	{
		lo->getPlayerStash()->items[i] = item;
		items_.erase(items_.begin() + itemIndex);
	}
	else
	{
		lo->getPlayerStash()->items.push_back(item);
		items_.erase(items_.begin() + itemIndex);
	}

}

void PartyManager::giveWeaponFromInventory(bool isWeapon, int itemid, int heroid)
{
	Item* item = nullptr;
	item = items_[itemid];

	if (isWeapon) heroes_[heroid]->giveWeapon(static_cast<Weapon*>(item));
	else heroes_[heroid]->giveArmor(static_cast<Armor*>(item));
	items_.erase(items_.begin() + itemid);
}
