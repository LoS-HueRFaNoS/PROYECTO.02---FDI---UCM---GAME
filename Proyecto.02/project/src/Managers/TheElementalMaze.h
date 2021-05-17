#pragma once
#include "../ecs/Entity.h"

class CombatManager;
class InterfazManager;
class Interfaz;
class ItemManager;
class Laberinto;
class CharacterManager;
class PartyManager;
class LobbyManager;
class GameStateManager;

enum class GameState {
	MainMenu,
	LOBBY,
	START_EXPLORING,
	EXPLORING,
	START_COMBAT,
	COMBAT,
	END_COMBAT,
	END_EXPLORING
};
using gameST = GameState;

class TheElementalMaze : public Entity
{
private:

	static TheElementalMaze* instance_;

	CombatManager* combatManager_; // compt
	Laberinto* laberinto_; // 
	Entity* player_; // 
	Entity* lab_; // 
	Interfaz* uiManager_; // compt
	InterfazManager* iManager_; // 
	ItemManager* itemManager_; //
	CharacterManager* characterManager_; // 
	PartyManager* partyManager_;
	LobbyManager* lobbyManager_;
	GameStateManager* stManager_; // compt

	bool pause_ = false;

public:
	TheElementalMaze(SDLGame* game, EntityManager* mngr, CharacterManager* chMngr, InterfazManager* iMngr) :
		characterManager_(chMngr),
		iManager_(iMngr),
		Entity(game, mngr),
		player_(nullptr),
		laberinto_(nullptr)
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
	void startExploring();
	void createLaberinto();
	void backFromDungeon();
	void checkOutNoInitialEnemy();
	void startCombat();
	void onExitLaberinto();

	Laberinto* getLaberinto() { return laberinto_; };

	Entity* getPlayer() { return player_; };

	CharacterManager* getCharacterManager() { return characterManager_; }

	InterfazManager* getUIManager() { return iManager_; }

	ItemManager* getItemManager() { return itemManager_; }

	CombatManager* getCombatManager() { return combatManager_; }

	PartyManager* getPartyManager() { return partyManager_; }

	LobbyManager* getLobbyManager() { return lobbyManager_; }

	GameState gameState();

	bool isPause() { return pause_; }

	void setPauseState(bool set) { pause_ = set; }

	void changeState(GameState state);
};