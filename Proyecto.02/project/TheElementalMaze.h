#pragma once
#include "src/Entity.h"

class CombatManager;
class InterfazManager;
class Interfaz;
class ItemManager;
class Laberinto;
class CharacterManager;
class PartyManager;
class LobbyManager;

// A los componentes se pueden acceder mediante la entidad y se pueden comunicar entre s�
// del mismo modo, mediante el puente que es la entidad.

enum GameState {
	COMBAT,
	EXPLORING,
	LOBBY
};

class TheElementalMaze : public Entity
{
private:

	static TheElementalMaze* instance_;

	CombatManager* combatManager_; // compt
	Laberinto* laberinto_; // 
	Entity* player_; // 
	Interfaz* uiManager_;
	InterfazManager* iManager_; // compt
	ItemManager* itemManager_; //
	CharacterManager* characterManager_; // 
	PartyManager* partyManager_;
	LobbyManager* lobbyManager_;

	GameState state_;

	bool pause_ = false;

	void onStateChanged();

public:
	TheElementalMaze(SDLGame* game, EntityManager* mngr, CharacterManager* chMngr, InterfazManager* iMngr) :
		characterManager_(chMngr),
		iManager_(iMngr),
		Entity(game, mngr)
	{};

public:

	inline static TheElementalMaze* initInstace(SDLGame* game, EntityManager* mngr, CharacterManager* chMngr,InterfazManager* iMngr) {
		assert(instance_ == nullptr);
		instance_ = new TheElementalMaze(game, mngr, chMngr, iMngr);
		instance_->init();
		return instance_;
	}

	inline static TheElementalMaze* instance() {
		assert(instance_ != nullptr);
		return instance_;
	}

	TheElementalMaze(TheElementalMaze&) = delete;

	TheElementalMaze& operator=(TheElementalMaze&) = delete;

	~TheElementalMaze();

	void init();

	Laberinto* getLaberinto() { return laberinto_; };

	Entity* getPlayer() { return player_; };

	CharacterManager* getCharacterManager() { return characterManager_; }

	InterfazManager* getUIManager() { return iManager_; }

	ItemManager* getItemManager() { return itemManager_; }

	CombatManager* getCombatManager() { return combatManager_; }

	PartyManager* getPartyManager() { return partyManager_; }

	LobbyManager* getLobbyManager() { return lobbyManager_; }

	GameState gameState() { return state_; }


	bool isPause() { return pause_; }

	void setPauseState(bool set) { pause_ = set; }

	void changeState(GameState state);
};