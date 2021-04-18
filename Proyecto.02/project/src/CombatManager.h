#ifndef _COMBAT_MANAGER_
#define _COMBAT_MANAGER_
#include "Component.h"
#include "Character.h"
#include "checkML.h"

#include <queue>

using Objective = std::vector<Character*>;

class CombatManager : public Component {
private:

	vector<Hero*> _heroes;	// equipo formado por los heroes elegidos
	vector<Enemy*> _enemies; // enemigos en combate

	vector<Character*> _turnQueue; // lista ordenada de turnos

	Character* currentCharacter; // personaje actual en combate

	int _turn = 0;

	int _exp = 0;

	bool _combatEnd = true;

	bool _win = true;

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

	void passTurn();

	bool checkEnd();

	void endCombat();

	void throwHability(Character* objective, Hability* hability);

	void castToTeam(characterType team, Hability* hability);

	void castToSingleTarget(characterType team, Hability* hability);

#pragma region CombatePorConsola

	void consoleCombat();

	void showTeams();

	void showQ();

#pragma endregion
public:
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

	void castHability(Hability* hability);

	Character* getCharacter(int index, characterType type) {
		return  type ? static_cast<Character*>(_enemies[index]) : static_cast<Character*>(_heroes[index]);
	};


};


#endif