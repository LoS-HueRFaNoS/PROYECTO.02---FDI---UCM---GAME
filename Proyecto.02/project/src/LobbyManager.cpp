#include "LobbyManager.h"
#include "Character.h"
#include "CharacterManager.h"
#include "PartyManager.h"
#include "../TheElementalMaze.h"


LobbyManager::LobbyManager(PartyManager* party)
	: party_(party)
{
	playerStash_ = new Stash();
	lobbyStore_ = new Store();
}

LobbyManager::~LobbyManager()
{
	delete playerStash_;
	delete lobbyStore_;
}

void LobbyManager::startExploring()
{
	delete lobbyStore_;
	TheElementalMaze::instance()->changeState(START_EXPLORING);
}

void LobbyManager::clearLobby()
{
	delete lobbyStore_;
}

void LobbyManager::generateHeroStash()
{

}

void LobbyManager::generateItemStash()
{

}

void LobbyManager::removeItemFromStash(Item* i)
{
	for (auto it = playerStash_->items.begin(); it != playerStash_->items.end(); it++) {
		if ((*it) == i) {
			playerStash_->items.erase(it);
			return;
		}
	}
}

Stash* LobbyManager::getPlayerStash()
{
	return playerStash_;
}

void LobbyManager::addHeroToParty(int index, int partyIndex)
{
	assert(partyIndex >= 0 && partyIndex <= 3);

	PartyManager* p = TheElementalMaze::instance()->getPartyManager();
	Hero* h = playerStash_->heroes[index];
	Hero* change = nullptr;

	if (partyIndex == -1) {
		if (!p->addHero(h)) {
			change = p->addHero(h, 0);
		}
	}
	else {
		change = p->addHero(h, partyIndex);
	}

	if (change)
		playerStash_->heroes[index] = change;
	else {
		playerStash_->heroes.erase(playerStash_->heroes.begin() + index);
	}
}

void LobbyManager::addHeroToStash(Hero* hero)
{
	playerStash_->heroes.push_back(hero);
}

void LobbyManager::addItemToStash(Item* item)
{
	playerStash_->items.push_back(item);
}

Store* LobbyManager::getLobbyStore()
{
	return lobbyStore_;
}

void LobbyManager::buyItem(int item)
{
	ItemToBuy* itemToBuy = lobbyStore_->items[item];
	if (itemToBuy->sold || party_->gold < itemToBuy->item->getBuyValue())
		return;

	party_->gold -= itemToBuy->item->getBuyValue();
	playerStash_->items.push_back(itemToBuy->item);
	itemToBuy->sold = true;

	std::cout << "Item purchased" << std::endl;
}

void LobbyManager::buyHero(int hero)
{
	HeroContract* contract = lobbyStore_->heroes[hero];
	if (contract->sold || party_->gold < contract->price)
		return;

	party_->gold -= contract->price;
	playerStash_->heroes.push_back(contract->hero);
	contract->sold = true;

	std::cout << "Hero purchased" << std::endl;
}

void LobbyManager::sellItem(Item* item)
{
	playerStash_->gold += item->getSellValue();

	removeItemFromStash(item);

	ItemToBuy* it = new ItemToBuy(item);

	lobbyStore_->items.push_back(it);
}

void LobbyManager::backFromDungeon()
{
	playerStash_->gold += party_->gold;
	party_->gold = 0;

	for(Item* i : party_->getItems())
	{
		addItemToStash(i);
	}
	party_->getItems().clear();
}

Stash::~Stash()
{
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

HeroContract::~HeroContract()
{
	hero->disable();
	hero = nullptr;
}

ItemToBuy::~ItemToBuy()
{
	delete item;
	item = nullptr;
}
