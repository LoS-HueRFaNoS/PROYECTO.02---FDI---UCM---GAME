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

	Character* currentCharacter;

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

	void throwHability(Character* objective, Hability* hability);
	
	void castToTeam(characterType team, Hability* hability);

public:

#pragma region CombatePorConsola

	void consoleCombat();

	void mostratEstadoEquipos();

	void mostrarCola();

#pragma endregion

	CombatManager() : currentCharacter(nullptr), _heroes(vector<Hero*>()), _enemies(vector<Enemy*>()), Component(ecs::CombatManager)
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

	void castHability(Hability* hability);

};


#endif