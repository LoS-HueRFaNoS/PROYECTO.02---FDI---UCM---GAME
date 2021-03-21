#ifndef _CHARACTER_
#define _CHARACTER_
#include "CharacterSheet.h"
#include "Entity.h"
#include "HabilityResources.h"

class Character : public Entity
{
protected:

	CharacterSheet* _sheet;

	vector<Hability*> _habilities;

	void init() {
		_sheet = addComponent<CharacterSheet>();
	}

	virtual void loadFromJson(string json, int t) {}

public:

	Character(SDLGame* game, EntityManager* mngr) : _habilities(vector<Hability*>()), Entity(game, mngr) {
		init();
	}

	void loadFromTemplate(characterTemplate t);
	void loadFromTemplate(enemyTemplate t);

	void recieveDamage(int damage, rpgLogic::damageType type);

	bool savingThrow(int save, rpgLogic::mainStat stat);

	void castHability(int hability, Character* objective) {
		_habilities[hability]->throwHability(objective);
	}

	int getMod(rpgLogic::mainStat stat) {
		return _sheet->getStat(stat).getMod();
	}

	int getStat(rpgLogic::mainStat stat) {
		return _sheet->getStat(stat).value;
	}

	void startTurn();

	template<typename T>
	T* addHability() {
		T* c(new T(this));
		_habilities.push_back(static_cast<Hability*>(c));
		return c;
	}
};


class Hero : public Character {
private:
	virtual void loadFromJson(string json, int t);
public:
	Hero(SDLGame* game, EntityManager* mngr) : Character(game, mngr) {
		init();
	}
};

class Enemy : public Character {
private:
	virtual void loadFromJson(string json, int t);
public:
	Enemy(SDLGame* game, EntityManager* mngr) : Character(game, mngr) {
		init();
	}
};

#endif

