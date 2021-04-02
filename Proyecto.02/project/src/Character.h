#ifndef _CHARACTER_
#define _CHARACTER_
#include "CharacterSheet.h"
#include "Entity.h"
#include "Equipement.h"
#include "jute.h"

#pragma region CHARACTER

class CombatManager;

class Character : public Entity
{
protected:

	characterType _type;

	CharacterSheet* _sheet;

	vector<Hability*> _habilities;

	virtual void init() {
		_sheet = addComponent<CharacterSheet>();
	}

	virtual void loadFromJson(jute::jValue v, int t) = 0;

	virtual void manageTurn(CombatManager* cm) = 0;

public:

	Character(SDLGame* game, EntityManager* mngr, characterType type) : _type(type), _habilities(vector<Hability*>()), Entity(game, mngr) {
		init();
	}

	void loadFromTemplate(jute::jValue v, heroTemplate t);
	void loadFromTemplate(jute::jValue v, enemyTemplate t);

	void recieveDamage(int damage, damageType type);

	void recieveHealing(int healing);
	
	void recieveBuff(int buff,mainStat stat);


	bool savingThrow(int save, mainStat stat);

	int throw20PlusMod(mainStat mod, bool crit);

	int throwStat(mainStat stat);

	bool checkHit(int hit);

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

	bool isDead() {
		return !_sheet->hitPoints();
	}
};

#pragma endregion


#pragma region HERO

class Hero : public Character {
private:

	Equipement* _equipement;

	virtual void loadFromJson(jute::jValue v, int t);

	virtual void manageTurn(CombatManager* cm);

	virtual void init() {
		_equipement = addComponent<Equipement>();
		Character::init();
	}

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

	int exp = 0;

	virtual void loadFromJson(jute::jValue v, int t);

	virtual void manageTurn(CombatManager* cm);

public:
	Enemy(SDLGame* game, EntityManager* mngr) : Character(game, mngr, ENEMY) {
		init();
	}

	int getExp() { return exp; }
};


#pragma endregion

#endif

