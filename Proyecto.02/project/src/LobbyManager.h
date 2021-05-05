#ifndef _LOBBY_MANAGER_
#define _LOBBY_MANAGER_


#include "Component.h"

class Hero;
class Item;

struct HeroContract
{
public:
	HeroContract(Hero* h, int p, int i) :
		hero(h),
		sold(false),
		price(p),
		index(i)
	{}
	~HeroContract() {
		hero->disable();
	}
	Hero* hero;
	int price;
	int index;
	bool sold;
};

struct ItemToBuy
{
public:
	ItemToBuy(Item* it, int i) :
		item(it),
		index(i),
		sold(false)
	{}
	Item* item;
	int index;
	bool sold;
};

struct Store {
public:
	Store() :
		heroes(std::vector<HeroContract*>()),
		items(std::vector<ItemToBuy*>())

	{
	}
	~Store() {
		heroes.clear();
		items.clear();

		for (ItemToBuy* i : items)
		{
			delete i; i = nullptr;
		}
		items.clear();
		for (HeroContract* i : heroes)
		{
			delete i; i = nullptr;
		}
		heroes.clear();
	}
	std::vector<HeroContract*> heroes;
	std::vector<ItemToBuy*> items;
};


struct Stash {
public:
	Stash() :
		heroes(std::vector< Hero*>()),
		items(std::vector<Item*>())
	{
	}
	~Stash() {
		heroes.clear();
		items.clear();

		for (Item* i : items)
		{
			delete i; i = nullptr;
		}
		items.clear();
		for (Hero* i : heroes)
		{
			i->disable();
		}
		heroes.clear();
	}
	std::vector<Hero*> heroes;
	std::vector<Item*> items;
};

class LobbyManager // : public Component  //  NO SE SI SERÍA UN COMPONENTE O NO
{
private:

	Stash* playerStash_;

	Store* lobbyStore_;

	void startExploring();

	void clearLobby();

	void generateHeroStash();

	void generateItemStash();

public:

	LobbyManager();
	~LobbyManager();

	Stash* getPlayerStash();

	void addHeroToParty(int index, int partyIndex = -1);

	void addHeroToStash(Hero* hero);

	void addItemToStash(Item* item);

	Store* getLobbyStore();

	void buyItem(int item);

	void buyHero(int hero);

};
#endif // !_LOBBY_MANAGER_

