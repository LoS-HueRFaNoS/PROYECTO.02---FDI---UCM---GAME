#ifndef _PARTY_MANAGER_
#define _PARTY_MANAGER_

#include <vector>
#include "../../Utilities/checkML.h"

class Hero;
class Item;
const int NUM_ITEMS = 25;

using uint = unsigned int;

class PartyManager
{
private:

	std::vector<Hero*> heroes_;

	std::vector<Item*> items_;

	bool levelKey = false;

	uint chestKeys = 0;

public:

	PartyManager();

	PartyManager(std::vector<Hero*> heroes, std::vector<Item*> items, int gold, int manaP, int healthP);

	~PartyManager();

	int gold;

	int manaPotions;

	int healthPotions;

	// Añade un heroe en la posición que pides y devuelve el que ya se encontraba en esa posición
	Hero* addHero(Hero* h, int pos);

	bool addHero(Hero* h);
	
	void removeHero(Hero* h);

	void removeHero(int h);

	void swapHeroes(int first, int second);

	void partyLost();

	void clearItems();

	bool addItem(Item* i);

	void changeItemWithHero(int index, int hero);

	std::vector<Hero*> getHeroes() { return heroes_; }

	std::vector<Item*> getItems() { return items_; }

	void usePotion(int hero, bool mana);

	void usePotion(Hero* hero, bool mana);

	void itemFromInventoryToStash(int itemIndex);

	void giveWeaponFromInventory(bool isWeapon, int itemid,int heroid);


	//Llaves
	void takeChestKey() { chestKeys++; }

	void takeLevelKey() { levelKey = true; }

	void useChestKey() { chestKeys--; }

	void useLevelKey() { levelKey = false; }

	bool hasChestKeys() { return chestKeys > 0; }

	bool hasLevelKey() { return levelKey; }

	void resetKeys() { levelKey = false; chestKeys = 0; }

	bool getLevelKey() { return levelKey; }

	uint getChestKeys() { return chestKeys; }
};

#endif // !_PARTY_MANAGER_
