#ifndef _COMBAT_MANAGER_
#define _COMBAT_MANAGER_
#include "Component.h"
#include "RPGLogic.h"
#include "Character.h"
#include "checkML.h"

#include <queue>

using Objective = std::vector<Character*>;

class CombatManager : public Component {
private:

	vector<Hero*> _heroes;
	vector<Enemy*> _enemies;

	queue<Character*> _turnQueue;

	Character* currentTurn;

	struct Initiative {
		characterType type;
		int pos;
		int roll;
		Initiative(characterType t, int p, int r) {
			type = t;
			pos = p;
			roll = r;
		}

	};

	struct initiative_roll
	{
		inline bool operator() (const Initiative& in1, const Initiative& in2)
		{
			return (in1.roll > in2.roll);
		}
	};

	void calculateTurns() {
		vector<Initiative> ini;
		for (int i = 0; i < _heroes.size(); i++)
			ini.push_back(Initiative(_heroes[i]->getType(), i, throwDice(1, _heroes[i]->getStat(DEX)) + _heroes[i]->getMod(DEX)));
		for (int i = 0; i < _enemies.size(); i++)
			ini.push_back(Initiative(_enemies[i]->getType(), i, throwDice(1, _enemies[i]->getStat(DEX)) + _enemies[i]->getMod(DEX)));

		sort(ini.begin(), ini.end(), initiative_roll());

		for (Initiative i : ini) {
			if (i.type)
				_turnQueue.push(_enemies[i.pos]);
			else
				_turnQueue.push(_heroes[i.pos]);
		}

	}

public:

	CombatManager() : currentTurn(nullptr), _heroes(vector<Hero*>()), _enemies(vector<Enemy*>()), Component(ecs::CombatManager)
	{}

	~CombatManager() {}

	Character* nextTurn() {
		if (!_turnQueue.empty()) return _turnQueue.front();
	}

	void addCharacter(Character* c) {
		if (c->getType())
			_enemies.push_back(dynamic_cast<Enemy*>(c));
		else
			_heroes.push_back(dynamic_cast<Hero*>(c));
	}

	void startCombat() {
		currentTurn = nullptr;
		calculateTurns();
		passTurn();
	}

	void passTurn() {
		if (currentTurn)
			_turnQueue.push(currentTurn);

		currentTurn = _turnQueue.front();

		_turnQueue.pop();
	}



	//for (Character* c : obj)
	//{
	//	if (c->checkHit(throwDice(1, 20) + caster->getMod(_mod)))
	//		throwHability(caster, obj);
	//	else
	//		cout << "Fallo - HabilityResources.cpp linea 13" << endl;
	//}

	//bool checkHit(int hit)
	//{
	//	return hit > (throwDice(1, _sheet.getStat(DEX).value) + _sheet.getStat(DEX).getMod());
	//}

	//void castHability(Character* caster, Character* obj)
	//{
	//	if (canCast()) {
	//		_nextCast = _cd;
	//		if (obj->checkHit(throwDice(1, 20) + caster->getMod(_mod)))
	//			throwHability(caster, obj);
	//		else
	//			cout << "Fallo - HabilityResources.cpp linea 13" << endl;
	//	}
	//	else
	//		cout << "Aun no puede castear quedan " << _nextCast << " turnos - HabilityResources.cpp linea 13" << endl;
	//}

};


#endif