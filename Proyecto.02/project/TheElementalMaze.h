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

	static unique_ptr<TheElementalMaze> instance_;

	CombatManager* combatManager_; // compt
	Entity* laberinto_; // 
	Entity* player_; // 
	Interfaz* uiManager_;
	InterfazManager* iManager_; // compt
	ItemManager* itemManager_; //
	CharacterManager* characterManager_; // 

	bool pause_ = false;

public:
	TheElementalMaze(SDLGame* game, EntityManager* mngr, CharacterManager* chMngr, InterfazManager* iMngr) :
		characterManager_(chMngr),
		iManager_(iMngr),
		Entity(game, mngr)
	{};

public:

	inline static TheElementalMaze* initInstace(SDLGame* game, EntityManager* mngr, CharacterManager* chMngr,InterfazManager* iMngr) {
		assert(instance_.get() == nullptr);
		instance_.reset(new TheElementalMaze(game, mngr, chMngr));
		instance_.get()->init();
		return instance_.get();
	}

	inline static TheElementalMaze* instance() {
		assert(instance_.get() != nullptr);
		return instance_.get();
	}

	TheElementalMaze(TheElementalMaze&) = delete;

	TheElementalMaze& operator=(TheElementalMaze&) = delete;

	virtual ~TheElementalMaze() {};

	void init();

	Entity* getLaberinto() { return laberinto_; };

	Entity* getPlayer() { return player_; };

	CharacterManager* getCharacterManager() { return characterManager_; }

	ItemManager* getItemManager() { return itemManager_; }

	bool isPause() { return pause_; }

	void setPauseState(bool set) { pause_ = set; }
};