#ifndef _LOBBY_MANAGER_
#define _LOBBY_MANAGER_


#include "Component.h"

class Hero;
class Item;
class PartyManager;

struct HeroContract
{
public:
	HeroContract(Hero* h, int p) :
		hero(h),
		sold(false),
		price(p)
	{}
	~HeroContract();
	Hero* hero;
	int price;
	bool sold;
};

struct ItemToBuy
{
public:
	ItemToBuy(Item* it) :
		item(it),
		sold(false)
	{}
	~ItemToBuy();
	Item* item;
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
		items(std::vector<Item*>()),
		gold(0)
	{
	}
	~Stash();
	std::vector<Hero*> heroes;
	std::vector<Item*> items;
	int gold;
};

class LobbyManager // : public Component  //  NO SE SI SERÍA UN COMPONENTE O NO
{
private:

	Stash* playerStash_;

	Store* lobbyStore_;

	PartyManager* party_;

	void startExploring();

	void clearLobby();

	void generateHeroStash();

	void generateItemStash();

	void removeItemFromStash(Item* i);

public:

	LobbyManager(PartyManager* party);
	~LobbyManager();

	Stash* getPlayerStash();

	void addHeroToParty(int index, int partyIndex = -1);

	void addHeroToStash(Hero* hero);

	void addItemToStash(Item* item);

	Store* getLobbyStore();

	void buyItem(int item);

	void buyHero(int hero);

	void sellItem(Item* item);

	void backFromDungeon();

};
#endif // !_LOBBY_MANAGER_

