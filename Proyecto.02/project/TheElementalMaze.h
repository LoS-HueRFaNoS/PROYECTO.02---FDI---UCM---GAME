#pragma once
#include "src/Entity.h"
#include "src/CombatManager.h"
#include "src/Interfaz.h"
#include "src/Laberinto.h"
#include "src/PlayerMotion.h"
#include "src/PlayerViewer.h"
#include "src/CharacterManager.h"
#include "src/ItemManager.h"


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
	CombatManager* combatManager_; // compt
	Entity* laberintoE_; // 
	Entity* player_; // 
	Interfaz* uiManager_;
	InterfazManager* iManager_; // compt
	ItemManager* itemManager_; //
	Laberinto* laberintoC_;	//compt
	PlayerMotion* playerMotion_; // compt
	CharacterManager* characterManager_; // 

	bool pause_ = false;

public:
	TheElementalMaze(SDLGame* game, EntityManager* mngr, CharacterManager* chMngr, InterfazManager* iMngr) :
		characterManager_(chMngr),
		iManager_(iMngr),
		Entity(game, mngr)
	{};
	virtual ~TheElementalMaze() {};

	void init();

	Entity* getLaberinto() { return laberintoE_; };

	Entity* getPlayer() { return player_; };

	PlayerMotion* getPlayerMotion() { return playerMotion_; };

	CharacterManager* getCharacterManager() { return characterManager_; }

	ItemManager* getItemManager() { return itemManager_; }

	bool isPause() { return pause_; }

	void setPauseState(bool set) { pause_ = set; }
};