#include "LobbyManager.h"
#include "Character.h"
#include "CharacterManager.h"

LobbyManager::LobbyManager()
{
	playerStash_ = new Stash();
	lobbyStash_ = new Stash();
}

LobbyManager::~LobbyManager()
{
	delete playerStash_;
	delete lobbyStash_;
}

Stash* LobbyManager::getPlayerStash()
{
	return playerStash_;
}

Stash* LobbyManager::getLobbyStash()
{
	return lobbyStash_;
}