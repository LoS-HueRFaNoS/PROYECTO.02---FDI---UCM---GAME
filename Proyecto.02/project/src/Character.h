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
		_sheet = new CharacterSheet();
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

	virtual void recieveHealing(int healing);

	void recieveBuff(int buff, mainStat stat);

	bool savingThrow(int save, mainStat stat);

	int throw20PlusMod(mainStat mod, bool crit);

	int throwStat(mainStat stat);

	bool checkHit(int hit);

	CharacterSheet* getCharacterSheet() { return _sheet; }

	int getMod(rpgLogic::mainStat stat) {
		return _sheet->getStat(stat).getMod();
	}

	int getStat(rpgLogic::mainStat stat) {
		return _sheet->getStat(stat).value;
	}

	void startTurn(CombatManager* cm);

	void endTurn();

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

	template<typename T, typename ... TArgs>
	void addCondition(TArgs&& ...mArgs) {
		if (!hasCondition(T::id())) {
			T* c(new T(this, std::forward<TArgs>(mArgs)...));
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

	// -------- METODOS NECESARIOS PARA INTERFAZ ---------

	size_t getMaxHealth() { return _sheet->maxHitPoints(); };	// vida
	size_t getMaxMana() { return _sheet->maxManaPoints(); };	// mana
	size_t getFireRes() { return _sheet->weaknesses.getWeakness(FIRE); };	// fire resistance
	size_t getWaterRes() { return _sheet->weaknesses.getWeakness(WATER); };	// water resistance
	size_t getIceRes() { return _sheet->weaknesses.getWeakness(ICE); };		// ice resistance
	size_t getEarthRes() { return _sheet->weaknesses.getWeakness(EARTH); };	// earth resistance
	size_t getWindRes() { return _sheet->weaknesses.getWeakness(WIND); };	// wind resistance
	size_t getLightRes() { return _sheet->weaknesses.getWeakness(LIGHT); };	// light resistance
	size_t getDarkRes() { return _sheet->weaknesses.getWeakness(DARK); };	// dark resistance

	/*	damageType {
			// Daños físicos
			BLUNT,
			PIERCE,
			SLASH,
			// Daños Elementales
			FIRE,
			WATER,
			ICE,
			EARTH,
			WIND,
			LIGHT,
			DARK,		*/

	// ----------------------------------------------------
};

#pragma endregion


#pragma region HERO

class Hero : public Character {

private:

	Weapon* _weapon;

	Armor* _armor;

	heroTemplate template_;

	bool _marcial;

	int savingSuccess = 0, savingFailure = 0;

	bool _deathGate = false;

	virtual void loadFromJson(jute::jValue v, int t);

	virtual void manageTurn(CombatManager* cm);

public:
	Hero(SDLGame* game, EntityManager* mngr) :Character(game, mngr, HERO) {
	}

	~Hero();

	Weapon* getWeapon() { return _weapon; }

	void giveWeapon(Weapon* w) { _weapon = w; }

	Armor* getArmor() { return _armor; }

	heroTemplate getTemplate() { return template_; }

	void giveArmor(Armor* a) { _armor = a; }

	int getSavingSuccess() { return savingSuccess; }
	int getSavingFailures() { return savingFailure; }

	void savingDeathThrow();

	virtual void recieveHealing(int healing);

	void resetThrows();

	void endCombat();

	void showSpellList();

	void manageInput(CombatManager* cm, int input);

	bool getDeathGate() { return _deathGate; }
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

