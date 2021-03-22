#ifndef _COMBAT_MANAGER_
#define _COMBAT_MANAGER_
#include "Component.h"
#include "RPGLogic.h"
#include "Character.h"
#include "checkML.h"

#include <queue>

using Objective = std::vector<Character*>;

class CombatManager : Component {
private:

	vector<Hero*> _heroes;
	vector<Enemy*> _enemies;

	queue<Character*> _turnQueue;

	Character* currentTurn;

public:

	Character* nextTurn() {
		if (!_turnQueue.empty()) return _turnQueue.front();
	}

	void addCharacter(Character* c) {
		if (c->getType())
			_enemies.push_back(dynamic_cast<Enemy*>(c));
		else
			_heroes.push_back(dynamic_cast<Hero*>(c));
	}


	void passTurn() {
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