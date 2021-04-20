#pragma once
#include "src/Entity.h"

class CombatManager;
class InterfazManager;
class InterfazManager;
class ItemManager;
class Laberinto;
class CharacterManager;

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
	Entity* laberinto_; // 
	Entity* player_; // 
	InterfazManager* uiManager_; // compt
	ItemManager* itemManager_; //
	CharacterManager* characterManager_; // 

	bool pause_ = false;

	TheElementalMaze(SDLGame* game, EntityManager* mngr, CharacterManager* chMngr) :
		characterManager_(chMngr),
		Entity(game, mngr)
	{};

public:

	inline static TheElementalMaze* initInstace(SDLGame* game, EntityManager* mngr, CharacterManager* chMngr) {
		assert(instance_ == nullptr);
		instance_ = new TheElementalMaze(game, mngr, chMngr);
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

	Entity* getLaberinto() { return laberinto_; };

	Entity* getPlayer() { return player_; };

	CharacterManager* getCharacterManager() { return characterManager_; }

	ItemManager* getItemManager() { return itemManager_; }

	bool isPause() { return pause_; }

	void setPauseState(bool set) { pause_ = set; }
};