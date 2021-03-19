#pragma once

#include <vector>
#include "RPGLogic.h"

using namespace rpgLogic;


// MOVER AL MANAGER DE COMBATE
// using Objective = std::vector<Character*>;
//for (Character* c : obj)
//{
//	if (c->checkHit(throwDice(1, 20) + caster->getMod(_mod)))
//		throwHability(caster, obj);
//	else
//		cout << "Fallo - HabilityResources.cpp linea 13" << endl;
//}


class Character;

#pragma region HABILITY



enum ObjectiveType
{
	SINGLEALLY,
	SIGLEENEMY,
	ALLYTEAM,
	ENEMYTEAM,
	CASTER
};

class Hability {
protected:
	int _mana;
	int _cd;
	int _nextCast;
	damageType _type;
	mainStat _mod;
	ObjectiveType _obj;

	bool canCast() { return !_nextCast; }

	virtual void throwHability(Character* caster, Character* obj) = 0;

public:
	Hability() :_mana(0), _cd(0), _nextCast(0), _type(_LastTypeId_), _obj(CASTER), _mod(_LastStatId_) {}

	Hability(int mana, int cd, damageType type, ObjectiveType obj, mainStat mod) :_mana(mana), _cd(cd), _nextCast(0), _type(type), _obj(obj), _mod(mod) {}

	~Hability() {}

	void passTurn() { if (_nextCast > 0) _nextCast--; }

	int getCD() { return _cd; }

	int nextCast() { return _nextCast; }

	int getMana() { return _mana; }

	void castHability(Character* caster, Character* obj);
};


// ---------------- EJEMPLO CON UNA BOLA DE FUEGO -----------------------

class Fireball : public Hability {
public:
	Fireball() :Hability(5, 5, FIRE, ENEMYTEAM, INT) {	}

	virtual void throwHability(Character* caster, Character* obj);
};

// ----------------------------------------------------------------------

#pragma endregion

#pragma region HABILITY

class AlteredState {
public:
	bool passTurn(Character* c) { return true; }
};

#pragma endregion