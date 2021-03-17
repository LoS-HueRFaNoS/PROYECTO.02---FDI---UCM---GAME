#ifndef _CHARACTER_
#define _CHARACTER_
#include "CharacterSheet.h"
#include "Entity.h"
#include "RPGLogic.h"

class Character : public Entity
{
private:

	CharacterSheet _sheet;

	vector<Hability> _habilities;

	void init() {}
public:

	Character(SDLGame* game, EntityManager* mngr) :Entity(game, mngr) {
		init();
	}

	/*void castHability(int hability, Objective objective) {
		_habilities[hability].castHability(objective);
	}*/
};
#endif

