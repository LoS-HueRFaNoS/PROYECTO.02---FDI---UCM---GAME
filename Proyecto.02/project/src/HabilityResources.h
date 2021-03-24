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
	int level = 0;
	int _mana = 0;
	std::string _name = "DefaultName";
	std::string _description = "DefaultDescription";

	damageType _type = damageType(0);
	mainStat _mod = _LastStatId_;
	ObjectiveType _obj = CASTER;


	Character* _caster;

public:

	Hability() :_caster(nullptr) {}

	Hability(Character* caster) :_caster(caster) {}

	~Hability() {}

	int getMana() { return _mana; }

	Character* getCaster() { return _caster; }

	virtual void throwHability(Character* obj)const = 0;

	std::string name() { return _name; }

	std::string description() { return _description; }

	mainStat getMod() { return _mod; }

	ObjectiveType getType() { return _obj; }
};

class LightAttack : public Hability {
public:
	LightAttack(Character* caster) :Hability(caster) {
		level = 0;
		_mana = 0;
		_name = "Light Attack";
		_description = "Golpe to guapo con el arma, a terminar";

		_mod = STR;
		_obj = SINGLEENEMY;
	}

	void throwHability(Character* obj)const override;
};

// ---------------- EJEMPLO CON UNA BOLA DE FUEGO -----------------------

class Fireball : public Hability {
public:
	Fireball(Character* caster) :Hability(caster) {	

		level = 4;
		_mana = 10;
		_name = "Fireball";
		_description = "Bola de fuego to guapa, a hace 8d6";

		_type = FIRE;
		_mod = INT;
		_obj = ENEMYTEAM;
	}

	void throwHability(Character* obj)const override;
};

// ----------------------------------------------------------------------

#pragma endregion