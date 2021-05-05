#ifndef _LOBBY_MANAGER_
#define _LOBBY_MANAGER_


#include "Component.h"

class Hero;
class Item;

struct Stash {
public:
	Stash() :
		heroes_(std::vector<Hero*>()),
		items_(std::vector<Item*>())

	{
	}
	~Stash() {
		heroes_.clear();
		heroes_.clear();

		for (Item* i : items_)
		{
			delete i; i = nullptr;
		}
		items_.clear();
		for (Item* i : items_)
		{
			delete i; i = nullptr;
		}
		items_.clear();
	}
	std::vector<Hero*> heroes_;
	std::vector<Item*> items_;
};

class LobbyManager // : public Component  //  NO SE SI SERÍA UN COMPONENTE O NO
{
private:
	
	Stash* playerStash_;

	Stash* lobbyStash_;


public:
	LobbyManager();
	~LobbyManager();


	Stash* getPlayerStash();

	Stash* getLobbyStash();

};
#endif // !_LOBBY_MANAGER_

