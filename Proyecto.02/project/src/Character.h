#ifndef _CHARACTER_
#define _CHARACTER_

#include "CharacterSheet.h"
#include "Entity.h"
#include "Item.h"

#pragma region CHARACTER

class CombatManager;

class Character : public Entity
{
protected:
	characterType _type;

	CharacterSheet* _sheet;

	vector<Hability*> _habilities;

	std::array<Hability*, _lasHabilityId_> _habilitiesArray = {};

	std::map < ConditionType, vector<Condition*>> _conditions;

	std::array<Condition*, _lastConditionId_> _conditonsArray = {};

	virtual void init() {
		for (int i = 0; i < _lastConditionType_; i++)
			_conditions[(ConditionType)i] = vector<Condition*>();
		_sheet = addComponent<CharacterSheet>();
	}

	virtual void loadFromJson(jute::jValue v, int t) = 0;

	virtual void manageTurn(CombatManager* cm) = 0;

public:

	Character(SDLGame* game, EntityManager* mngr, characterType type) : _type(type), Entity(game, mngr) {
		init();
	}
	
	~Character();

	void loadFromTemplate(jute::jValue v, heroTemplate t);

	void loadFromTemplate(jute::jValue v, enemyTemplate t);

	void recieveDamage(int damage, damageType type);

	void recieveHealing(int healing);

	void recieveBuff(int buff, mainStat stat);


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
	void addHability() {
		if (!hasHability(T::id())) {
			T* c(new T(this));
			_habilities.push_back(c);
			_habilitiesArray[T::id()] = c;
		}
	}

	template<typename T>
	void addCondition(Character* caster) {
		if (!hasCondition(T::id())) {
			T* c(new T(caster, this));
			_conditions[c->getType()].push_back(c);
			_conditonsArray[T::id()] = c;
			c->init();
		}
		else {
			_conditonsArray[T::id()]->resetTurns();
			_conditonsArray[T::id()]->addStack();
		}
	}

	bool hasCondition(Conditions_Id id) {
		return _conditonsArray[id] != nullptr;
	}

	bool hasHability(Hability_Id id) {
		return _habilitiesArray[id] != nullptr;
	}

	void removeCondition(Conditions_Id id) {
		_conditonsArray[id] = nullptr;
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

	Weapon* _weapon;

	Armor* _armor;

	bool _marcial;

	virtual void loadFromJson(jute::jValue v, int t);

	virtual void manageTurn(CombatManager* cm) {}

	virtual void init() {
		//_equipement = addComponent<Equipement>();
		Character::init();
	}

public:
	Hero(SDLGame* game, EntityManager* mngr) :Character(game, mngr, HERO) {
	}

	~Hero();

	Weapon* getWeapon() { return _weapon; }

	void giveWeapon(Weapon* w) { _weapon = w; }

	Armor* getArmor() { return _armor; }

	void giveArmor(Armor* a) { _armor = a; }

	void endCombat();

	void showSpellList();

	void manageInput(CombatManager* cm, int input);
};

#pragma endregion


#pragma region ENEMY

class Enemy : public Character {
private:

	string description = "Un enemigo muy chungo";

	int exp = 0;

	int coins = 0;

	virtual void loadFromJson(jute::jValue v, int t);

	virtual void manageTurn(CombatManager* cm);

public:
	Enemy(SDLGame* game, EntityManager* mngr) : Character(game, mngr, ENEMY) {
	}

	int getExp() { return exp; }
};


#pragma endregion

#endif

