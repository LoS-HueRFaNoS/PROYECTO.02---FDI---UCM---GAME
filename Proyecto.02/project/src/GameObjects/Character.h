#ifndef _CHARACTER_
#define _CHARACTER_

#include "../ecs/Entity.h"
#include "../Templates/CharacterSheet.h"
#include "../Managers/game/HabilityManager.h"
#include "../Structures/Item.h"

#pragma region CHARACTER

class CombatManager;

class Character : public Entity
{
protected:

	Weapon* _weapon;

	characterType _type;

	CharacterSheet* _sheet;

	vector<Hability*> _habilities;

	vector<Hability_Id> _habilitiesExtra;

	Hability* lightAttack_;
	Hability* heavyAttack_;

	std::array<Hability*, size_t(habID::_lastHabilityId_)> _habilitiesArray = {};

	std::vector<Condition*> _conditions;

	std::array<Condition*, size_t(condID::_lastConditionId_)> _conditonsArray = {};

	virtual void init() {
			_conditions = vector<Condition*>();
		_sheet = new CharacterSheet();

		lightAttack_ = new LightAttack(this);
		heavyAttack_ = new HeavyStrike(this);

		_habilitiesArray[size_t(LightAttack::id())] = lightAttack_;
		_habilitiesArray[size_t(HeavyStrike::id())] = heavyAttack_;
	}

	virtual void loadFromJson(jute::jValue v, int t) = 0;

	virtual void manageTurn(CombatManager* cm) = 0;

public:

	Character(SDLGame* game, EntityManager* mngr, characterType type) :_weapon(nullptr),
		_type(type), Entity(game, mngr) {
		init();
	}

	~Character();

	Weapon* getWeapon() { return _weapon; }

	void loadFromTemplate(jute::jValue v, heroTemplate t);

	void loadFromTemplate(jute::jValue v, enemyTemplate t);

	void recieveDamage(int damage, damageType type, Character* attacker = nullptr);

	virtual void recieveHealing(int healing);

	void recieveBuff(int buff, mainStat stat);

	bool savingThrow(int save, mainStat stat);

	int throw20PlusMod(mainStat mod, bool crit);

	int throwStat(mainStat stat);

	bool checkHit(int hit);

	void removeConditions();

	void removeGoodConditions();

	void removeBadConditions();

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

	void addHability(Hability_Id id) {
		if (!hasHability(id)) {
			Hability* c = HabilityManager::instance()->getHability(id);
			c->setCaster(this);
			_habilities.push_back(c);
			_habilitiesArray[size_t(id)] = c;
		}
	}

	template<typename T>
	void addHability() {
		if (!hasHability(T::id())) {
			T* c(new T(this));
			_habilities.push_back(c);
			_habilitiesArray[size_t(T::id())] = c;
		}
	}

	template<typename T, typename ... TArgs>
	void addCondition(TArgs&& ...mArgs) {
		if (!hasCondition(T::id())) {
			T* c(new T(this, std::forward<TArgs>(mArgs)...));
			_conditions.push_back(c);
			_conditonsArray[size_t(T::id())] = c;
			c->init();
		}
		else {
			_conditonsArray[size_t(T::id())]->resetTurns();
			_conditonsArray[size_t(T::id())]->addStack();
		}
	}

	bool hasCondition(Conditions_Id id) {
		return _conditonsArray[size_t(id)] != nullptr;
	}

	bool hasHability(Hability_Id id) {
		return _habilitiesArray[size_t(id)] != nullptr;
	}

	void removeCondition(Conditions_Id id) {
		_conditonsArray[size_t(id)] = nullptr;
	}

	vector<Hability*> getHabilities() {
		return _habilities;
	}

	Hability* getLightAttack() { return lightAttack_; }

	Hability* getHeavyAttack() { return heavyAttack_; }

	bool isDead() {
		return !_sheet->hitPoints();
	}
};

#pragma endregion


#pragma region HERO

class Hero : public Character {

private:

	Armor* _armor;

	heroTemplate template_;

	bool _marcial;

	int savingSuccess = 0, savingFailure = 0;

	int expNeed = 100, expMax = 100;

	int level = 0, pointsPerLevel = 0;

	bool _deathGate = false;

	virtual void loadFromJson(jute::jValue v, int t);

	virtual void manageTurn(CombatManager* cm);

public:
	Hero(SDLGame* game, EntityManager* mngr) :
		_armor(nullptr), 
		Character(game, mngr, charTy::HERO) {};
	void setTemplate(heroTemplate newTemplate) { template_ = newTemplate; } // Debug
	~Hero();

	void giveWeapon(Weapon* w) { _weapon = w; }

	Armor* getArmor() { return _armor; }
	void removeArmor() { _armor = nullptr; }
	heroTemplate getTemplate() { return template_; }


	int getSavingSuccess() { return savingSuccess; }
	int getSavingFailures() { return savingFailure; }

	void savingDeathThrow();

	void giveArmor(Armor* a);

	virtual void recieveHealing(int healing);
	
	virtual void recieveMana(int mana);

	void resetThrows();

	void levelUp(int exp);

	void AddHabilityWithLevel(int level);

	void changeHeroStat(rpgLogic::mainStat stat);

	void endCombat(int exp);

	void showSpellList();

	void killHero();

	void manageInput(CombatManager* cm, int input);

	bool getDeathGate() { return _deathGate; }

	int getExp() { return expMax - expNeed; };
	int getExpMax() { return expMax; };
};

#pragma endregion


#pragma region ENEMY

class Enemy : public Character {
private:

	enemyTemplate template_;

	string description = "A pretty difficult enemy";

	int exp = 0;

	int coins = 0;

	bool boss = false;

	virtual void loadFromJson(jute::jValue v, int t);

	virtual void manageTurn(CombatManager* cm);

public:
	Enemy(SDLGame* game, EntityManager* mngr) : Character(game, mngr, charTy::ENEMY) {
	}

	int getExp() { return exp; }

	bool isBoss() { return boss; }

	enemyTemplate getTemplate() { return template_; }
};


#pragma endregion

#endif

