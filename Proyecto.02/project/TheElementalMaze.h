#pragma once
#include "src/Entity.h"
#include "src/CombatManager.h"
#include "src/CharacterManager.h"
#include "src/InterfazManager.h"
#include "src/Laberinto.h"
#include "src/PlayerMotion.h"
#include "src/PlayerViewer.h"
#include "src/ItemManager.h"
using jv = jute::jValue;
// A los componentes se pueden acceder mediante la entidad y se pueden comunicar entre sí
// del mismo modo, mediante el puente que es la entidad.

class TheElementalMaze : public Entity
{
private:
	CombatManager* combatManager_; // compt
	Entity* laberintoE_; // 
	Entity* player_; // 
	InterfazManager* uiManager_; // compt
	ItemManager* itemManager_; //
	Laberinto* laberintoC_;	//compt
	PlayerMotion* playerMotion_; // compt
	CharacterManager* characterManager_; // 

public:
	TheElementalMaze(SDLGame* game, EntityManager* mngr, CharacterManager* chMngr) :
		characterManager_(chMngr),
		Entity(game, mngr)
	{};
	virtual ~TheElementalMaze() {};

	void init();

	Entity* getLaberinto() { return laberintoE_; };

	Entity* getPlayer() { return player_; };

	PlayerMotion* getPlayerMotion() { return playerMotion_; };

	CharacterManager* getCharacterManager() { return characterManager_; }

	ItemManager* getItemManager() { return itemManager_; }
};