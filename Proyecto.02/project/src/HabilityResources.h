#pragma once

#include <vector>
#include "RPGLogic.h"
#include <string>

using namespace rpgLogic;

class Character;

#pragma region HABILITY

enum ObjectiveType
{
	SINGLEALLY,
	SINGLEENEMY,
	ALLYTEAM,
	ENEMYTEAM,
	CASTER
};

class Hability {
protected:
	int level;
	int _mana;
	/*string name;
	string description;*/

	damageType _type;
	mainStat _mod;
	ObjectiveType _obj;


	Character* _caster;

public:
	Hability() :_caster(nullptr), _mana(0), _type(_LastTypeId_), _obj(CASTER), _mod(_LastStatId_) {}

	Hability(Character* caster, int mana, damageType type, ObjectiveType obj, mainStat mod) :_caster(caster), _mana(mana), _type(type), _obj(obj), _mod(mod) {}

	~Hability() {}

	int getMana() { return _mana; }

	Character* getCaster() { return _caster; }

	virtual void throwHability(Character* obj)const = 0;
};

class LightAttack : public Hability {
public:
	LightAttack(Character* caster) :Hability(caster, 0, SLASH, SINGLEENEMY, STR) { }

	void throwHability(Character* obj)const override;
};

// ---------------- EJEMPLO CON UNA BOLA DE FUEGO -----------------------

class Fireball : public Hability {
public:
	Fireball(Character* caster) :Hability(caster, 5, FIRE, ENEMYTEAM, INT) {	}

	void throwHability(Character* obj)const override;
};

// ----------------------------------------------------------------------

#pragma endregion