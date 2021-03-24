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

	_turnQueue[_turn]->startTurn(this);

	cout << "---------- PRESS ENTER TO END TURN ----------" << endl;

	cin.get();
	passTurn();
}

void CombatManager::mostrarHabilidades()
{
	for (Hability* h : currentTurn->getHabilities())
		cout << typeid(h).name();
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
	currentTurn = nullptr;
	calculateTurns();
}

void CombatManager::passTurn()
{
	_turn = ++_turn % _turnQueue.size();
}

void CombatManager::calculateTurns()
{
	vector<Initiative> ini;
	for (int i = 0; i < _heroes.size(); i++)
		ini.push_back(Initiative(_heroes[i]->getType(), i, throwDice(1, _heroes[i]->getStat(DEX)) + _heroes[i]->getMod(DEX)));
	for (int i = 0; i < _enemies.size(); i++)
		ini.push_back(Initiative(_enemies[i]->getType(), i, throwDice(1, _enemies[i]->getStat(DEX)) + _enemies[i]->getMod(DEX)));

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