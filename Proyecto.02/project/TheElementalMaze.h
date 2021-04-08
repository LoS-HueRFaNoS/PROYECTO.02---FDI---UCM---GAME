#pragma once
#include "src/Entity.h"
#include "src/CombatManager.h"
#include "src/InterfazManager.h"
#include "src/Laberinto.h"
#include "src/PlayerMotion.h"
#include "src/PlayerViewer.h"
#include "src/ItemManager.h"

// A los componentes se pueden acceder mediante la entidad y se pueden comunicar entre sí
// del mismo modo, mediante el puente que es la entidad.
class TheElementalMaze : public Entity
{
private:
	CombatManager* cm; // compt
	Entity* laberinto; // 
	Entity* player; // 
	InterfazManager* F; // compt
	ItemManager* itemManager_; //
	Laberinto* lab;	//compt
	PlayerMotion* plmot; // compt

public:
	TheElementalMaze(SDLGame* game, EntityManager* mngr) : Entity(game, mngr) {};
	virtual ~TheElementalMaze() {};

	void init(SDLGame* game, EntityManager* mngr);

	Entity* getLaberinto() { return laberinto; };
	Entity* getPlayer() { return player; };
};