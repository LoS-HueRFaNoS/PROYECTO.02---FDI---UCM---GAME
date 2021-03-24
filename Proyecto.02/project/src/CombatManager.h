#ifndef _COMBAT_MANAGER_
#define _COMBAT_MANAGER_
#include "Component.h"
#include "Character.h"
#include "checkML.h"

#include <queue>

using Objective = std::vector<Character*>;

class CombatManager : public Component {
private:

	vector<Hero*> _heroes;
	vector<Enemy*> _enemies;

	vector<Character*> _turnQueue;

	Character* currentTurn;

	int _turn = 0;

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

	void calculateTurns();

public:

#pragma region CombatePorConsola

	void consoleCombat();

	void mostrarHabilidades();

	void mostratEstadoEquipos();

	void mostrarCola();

#pragma endregion

	CombatManager() : currentTurn(nullptr), _heroes(vector<Hero*>()), _enemies(vector<Enemy*>()), Component(ecs::CombatManager)
	{}

	~CombatManager() {}

	void update()override;

	Character* nextTurn() {
		if (!_turnQueue.empty()) return _turnQueue[_turn];
	}

	void addCharacter(Character* c) {
		if (c->getType())
			_enemies.push_back(dynamic_cast<Enemy*>(c));
		else
			_heroes.push_back(dynamic_cast<Hero*>(c));
	}

	void startCombat();

	void passTurn();


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