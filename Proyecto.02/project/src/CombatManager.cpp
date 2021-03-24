#include "CombatManager.h"
#include "RPGLogic.h"


#pragma region CombatePorConsola

#include <iomanip>

void CombatManager::consoleCombat()
{
	system("CLS");

	mostratEstadoEquipos();

	mostrarCola();

	cout << "---------- PRESS ENTER TO START TURN ----------" << endl;

	cin.get();

	currentCharacter->startTurn(this);

	cout << "---------- PRESS ENTER TO END TURN ----------" << endl;

	cin.clear();    // Restore input stream to working state
	cin.ignore(100, '\n');    // Get rid of any garbage that user might have entered
	cin.get();
	passTurn();
}

void CombatManager::mostratEstadoEquipos()
{
	cout << "---------- HEROES ----------" << endl;
	for (Hero* h : _heroes) {
		CharacterSheet* s = h->getComponent<CharacterSheet>(ecs::CharacterSheet);
		cout << std::setfill(' ') << std::left << setw(10) << s->name << std::right << setw(5) << s->hitPoints() << " HP" << setw(5) << s->manaPoints() << " MP  " << setw(5)
			<< " STR " << std::setfill('0') << setw(2) << s->getStat(rpgLogic::STR).value << "  CON " << std::setfill('0') << setw(2) <<
			s->getStat(rpgLogic::CON).value << "  DEX " << std::setfill('0') << setw(2) << s->getStat(rpgLogic::DEX).value << "  INT " <<
			std::setfill('0') << setw(2) << s->getStat(rpgLogic::INT).value << endl;
	}

	cout << endl << "---------- ENEMIES ----------" << endl;

	for (Enemy* e : _enemies) {
		CharacterSheet* s = e->getComponent<CharacterSheet>(ecs::CharacterSheet);
		cout << std::setfill(' ') << std::left << setw(10) << s->name << std::right << setw(5) << s->hitPoints() << " HP" << setw(5) << s->manaPoints() << " MP  " << setw(5)
			<< " STR " << std::setfill('0') << setw(2) << s->getStat(rpgLogic::STR).value << "  CON " << std::setfill('0') << setw(2) <<
			s->getStat(rpgLogic::CON).value << "  DEX " << std::setfill('0') << setw(2) << s->getStat(rpgLogic::DEX).value << "  INT " <<
			std::setfill('0') << setw(2) << s->getStat(rpgLogic::INT).value << endl;
	}

}

void CombatManager::mostrarCola()
{
	cout << std::left << std::setfill(' ') << "\n---------- TURN QUEUE ----------" << endl;

	for (int i = 0; i < _turnQueue.size(); i++) {
		cout << setw(15) << _turnQueue[i]->name();
		if (i == _turn)
			cout << "<----";
		cout << "\n";
	}

}

#pragma endregion


void CombatManager::startCombat()
{
	_turn = 0;
	currentCharacter = nullptr;
	calculateTurns();
	currentCharacter = _turnQueue[0];
}

void CombatManager::passTurn()
{
	_turn = ++_turn % _turnQueue.size();
	currentCharacter = _turnQueue[_turn];
}

void CombatManager::castHability(Hability* hability)
{
	ObjectiveType t = hability->getType();
	cout << "\n";

	switch (t)
	{
	case SINGLEALLY:

		break;
	case SINGLEENEMY:

		break;
	case ALLYTEAM:
		castToTeam(currentCharacter->getType(), hability);
		break;
	case ENEMYTEAM:
		castToTeam((characterType)((int)currentCharacter->getType() ^ 1), hability);
		break;
	case CASTER:

		break;
	default:
		break;
	}
}


void CombatManager::castToTeam(characterType team, Hability* hability)
{
	if (team)
		for (Enemy* e : _enemies)
			throwHability(e, hability);
	else
		for (Hero* h : _heroes)
			throwHability(h, hability);
}

void CombatManager::throwHability(Character* objective, Hability* hability)
{
	cout << "Attack on " << objective->name() << endl;
	if (objective->checkHit(currentCharacter->throw20PlusMod(hability->getMod()))) {
		cout << hability->name() << " hits" << endl;;
		hability->throwHability(objective);
	}
	else {
		cout << "No Hit" << endl;
	}
	cout << "\n\n";
}


void CombatManager::calculateTurns()
{
	vector<Initiative> ini;
	for (int i = 0; i < _heroes.size(); i++)
		ini.push_back(Initiative(_heroes[i]->getType(), i, throwDice(1, _heroes[i]->getStat(DEX), false) + _heroes[i]->getMod(DEX)));
	for (int i = 0; i < _enemies.size(); i++)
		ini.push_back(Initiative(_enemies[i]->getType(), i, throwDice(1, _enemies[i]->getStat(DEX), false) + _enemies[i]->getMod(DEX)));

	sort(ini.begin(), ini.end(), initiative_roll());

	for (Initiative i : ini) {
		if (i.type)
			_turnQueue.push_back(_enemies[i.pos]);
		else
			_turnQueue.push_back(_heroes[i.pos]);
	}

}

void CombatManager::update()
{
	consoleCombat();
}