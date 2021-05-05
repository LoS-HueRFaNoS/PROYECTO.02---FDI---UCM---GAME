#include "LobbyManager.h"
#include "Character.h"
#include "CharacterManager.h"
#include "PartyManager.h"
#include "../TheElementalMaze.h"


LobbyManager::LobbyManager()
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

}

void LobbyManager::buyHero(int hero)
{

}
