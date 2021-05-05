#ifndef _PARTY_MANAGER_
#define _PARTY_MANAGER_

#include <vector>
#include "checkML.h"

class Hero;
class Item;


class PartyManager
{
private:

	int gold_;

	std::vector<Hero*> heroes_;

	std::vector<Item*> items_;

public:

	PartyManager();

	PartyManager(std::vector<Hero*> heroes, std::vector<Item*> items, int gold);

	~PartyManager();

	// Añade un heroe en la posición que pides y devuelve el que ya se encontraba en esa posición
	Hero* addHero(Hero* h, int pos);

	bool addHero(Hero* h);
	
	void removeHero(Hero* h);

	void removeHero(int h);

	Item* addItem(Item* i, int pos);

	std::vector<Hero*> getHeroes() { return heroes_; }

	std::vector<Item*> getItems() { return items_; }
};

#endif // !_PARTY_MANAGER_
