#ifndef _PARTY_MANAGER_
#define _PARTY_MANAGER_

#include <vector>
#include "../../Utilities/checkML.h"

class Hero;
class Item;
const int NUM_ITEMS = 25;

class PartyManager
{
private:

	std::vector<Hero*> heroes_;

	std::vector<Item*> items_;

	void reorderVector();

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

	Item* addItem(Item* i, int pos);

	void changeItemWithHero(int index, int hero);

	std::vector<Hero*> getHeroes() { return heroes_; }

	std::vector<Item*> getItems() { return items_; }

	void usePotion(int hero, bool mana);

	void usePotion(Hero* hero, bool mana);
};

#endif // !_PARTY_MANAGER_
