#ifndef _CHARACTER_
#define _CHARACTER_
#include "CharacterSheet.h"
#include "Entity.h"
#include "HabilityResources.h"

class Character : public Entity
{
private:

	CharacterSheet _sheet;

	vector<Hability*> _habilities;

	vector<AlteredState*> _states;

	void init() {}
public:

	Character(SDLGame* game, EntityManager* mngr) :_sheet(CharacterSheet()), _habilities(vector<Hability*>()), _states(vector<AlteredState*>()), Entity(game, mngr) {
		init();
	}

	bool checkHit(int hit);

	void recieveDamage(int damage, rpgLogic::damageType type);

	bool savingThrow(int save, rpgLogic::mainStat stat);

	void castHability(int hability, Character* objective) {
		_habilities[hability]->castHability(this, objective);
	}

	int getMod(rpgLogic::mainStat stat) {
		return _sheet.getStat(stat).getMod();
	}

	int getStat(rpgLogic::mainStat stat) {
		return _sheet.getStat(stat).value;
	}

	void startTurn();
};
#endif

