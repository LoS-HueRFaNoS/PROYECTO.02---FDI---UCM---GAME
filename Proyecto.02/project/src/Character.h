#ifndef _CHARACTER_
#define _CHARACTER_
#include "CharacterSheet.h"
#include "Entity.h"
#include "HabilityResources.h"


#pragma region CHARACTER

class CombatManager;

class Character : public Entity
{
protected:

	characterType _type;

	CharacterSheet* _sheet;

	vector<Hability*> _habilities;

	void init() {
		_sheet = addComponent<CharacterSheet>();
	}

	virtual void loadFromJson(string json, int t) {}

	virtual void manageTurn(CombatManager* cm) = 0;

public:

	Character(SDLGame* game, EntityManager* mngr, characterType type) : _type(type), _habilities(vector<Hability*>()), Entity(game, mngr) {
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

	void startTurn(CombatManager* cm);

	characterType getType() {
		return _type;
	}

	string name() {
		return _sheet->name;
	}

	template<typename T>
	T* addHability() {
		T* c(new T(this));
		_habilities.push_back(static_cast<Hability*>(c));
		return c;
	}

	vector<Hability*> getHabilities() {
		return _habilities;
	}
};

#pragma endregion


#pragma region HERO

class Hero : public Character {
private:

	virtual void loadFromJson(string json, int t);

	virtual void manageTurn(CombatManager* cm);

#pragma region CombatePorConsola

	void consoleTurn(CombatManager* cm);

#pragma endregion

public:
	Hero(SDLGame* game, EntityManager* mngr) :Character(game, mngr, HERO) {
		init();
	}
};

#pragma endregion


#pragma region ENEMY

class Enemy : public Character {
private:

	virtual void loadFromJson(string json, int t);

	virtual void manageTurn(CombatManager* cm);

public:
	Enemy(SDLGame* game, EntityManager* mngr) : Character(game, mngr, ENEMY) {
		init();
	}
};


#pragma endregion

#endif

