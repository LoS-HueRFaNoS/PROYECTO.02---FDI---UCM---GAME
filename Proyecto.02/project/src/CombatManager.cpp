#include "CombatManager.h"
#include "RPGLogic.h"


#pragma region CombatePorConsola

#include <iomanip>
#include <string>

void CombatManager::consoleCombat()
{
	system("CLS");

	showTeams();

	showQ();

	cout << "---------- PRESS ENTER TO START TURN ----------" << endl;
	cin.ignore(INT_MAX, '\n');
	cin.get();
	cin.sync();

	currentCharacter->startTurn(this);

	cout << "---------- PRESS ENTER TO END TURN ----------" << endl;
	cin.ignore(INT_MAX, '\n');
	cin.get();
	cin.sync();

	passTurn();
}

void CombatManager::showTeams()
{
	cout << "---------- HEROES ----------" << endl;
	for (Hero* h : _heroes) {
		CharacterSheet* s = h->getComponent<CharacterSheet>(ecs::CharacterSheet);
		cout << std::setfill(' ') << std::left << setw(12) << s->name << setw(15) << "HP " + to_string(s->hitPoints()) + "/" + to_string(s->maxHitPoints()) <<
			setw(15) << "MP " + to_string(s->manaPoints()) + "/" + to_string(s->maxManaPoints()) << std::right <<
			" STR " << std::setfill('0') << setw(2) << s->getStat(rpgLogic::STR).value << "  CON " << std::setfill('0') << setw(2) <<
			s->getStat(rpgLogic::CON).value << "  DEX " << std::setfill('0') << setw(2) << s->getStat(rpgLogic::DEX).value << "  INT " <<
			std::setfill('0') << setw(2) << s->getStat(rpgLogic::INT).value << endl;
	}

	cout << endl << "---------- ENEMIES ----------" << endl;

	for (Enemy* e : _enemies) {
		CharacterSheet* s = e->getComponent<CharacterSheet>(ecs::CharacterSheet);
		if (e->isDead())
			cout << std::setfill(' ') << std::left << setw(10) << s->name << std::right << setw(8) << "DEAD" << endl;
		else {
			cout << std::setfill(' ') << std::left << setw(12) << s->name << setw(15) << "HP " + to_string(s->hitPoints()) + "/" + to_string(s->maxHitPoints()) <<
				setw(15) << "MP " + to_string(s->manaPoints()) + "/" + to_string(s->maxManaPoints()) << std::right <<
				" STR " << std::setfill('0') << setw(2) << s->getStat(rpgLogic::STR).value << "  CON " << std::setfill('0') << setw(2) <<
				s->getStat(rpgLogic::CON).value << "  DEX " << std::setfill('0') << setw(2) << s->getStat(rpgLogic::DEX).value << "  INT " <<
				std::setfill('0') << setw(2) << s->getStat(rpgLogic::INT).value << endl;
		}
	}

}

void CombatManager::showQ()
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
	_exp = 0;
	_combatEnd = false;
	currentCharacter = nullptr;
	calculateTurns();
	currentCharacter = _turnQueue[0];
}

void CombatManager::passTurn()
{
	if (!checkEnd()) {
		for (std::vector<Character*>::iterator it = _turnQueue.begin(); it != _turnQueue.end();) {
			if ((*it)->isDead() && (*it)->getType()) {
				_exp += dynamic_cast<Enemy*>(*it)->getExp();
				it = _turnQueue.erase(it);
			}
			else {
				it++;
			}
		}
		_turn = ++_turn % _turnQueue.size();
		currentCharacter = _turnQueue[_turn];
	}
	else
		endCombat();
}

bool CombatManager::checkEnd()
{
	bool end = true;
	for (Hero* h : _heroes)
		end *= h->isDead();
	if (end) {
		_win = false;
		return true;
	}
	end = true;
	for (Enemy* e : _enemies)
		end *= e->isDead();
	return end;
}

void CombatManager::endCombat()
{
	_combatEnd = true;
	if (_win) {
		cout << "GANASTE, ERES BUENISIMO NO ?" << endl << _exp << " DE EXPERIENCIA GANADA" << endl;
	}
	else
		cout << "PERDISTE, ASI ES LA VIDA" << endl;
}

void CombatManager::castHability(Hability* hability)
{
	ObjectiveType t = hability->getObjectiveType();
	cout << "\n";

	switch (t)
	{
	case SINGLEALLY:
		castToSingleTarget(currentCharacter->getType(), hability);
		break;
	case SINGLEENEMY:
		castToSingleTarget((characterType)((int)currentCharacter->getType() ^ 1), hability);
		break;
	case ALLYTEAM:
		castToTeam(currentCharacter->getType(), hability);
		break;
	case ENEMYTEAM:
		castToTeam((characterType)((int)currentCharacter->getType() ^ 1), hability);
		break;
	case CASTER:
		throwHability(hability->getCaster(), hability);
		break;
	default:
		break;
	}
}


void CombatManager::castToTeam(characterType team, Hability* hability)
{
	if (team) {
		for (Enemy* e : _enemies)
			if (!e->isDead())throwHability(e, hability);
	}
	else {
		for (Hero* h : _heroes)
			if (!h->isDead())throwHability(h, hability);
	}

}

void CombatManager::castToSingleTarget(characterType team, Hability* hability)
{
	cout << "TARGETS" << endl;
	int maxTarget = 0;

	if (team) {
		maxTarget = int(_enemies.size());
		for (int i = 0; i < _enemies.size(); i++) {
			CharacterSheet* c = _enemies[i]->getComponent<CharacterSheet>(ecs::CharacterSheet);
			cout << i << ". " << std::setfill(' ') << std::left << setw(12) << c->name << setw(15) << "HP " + to_string(c->hitPoints()) + "/" + to_string(c->maxHitPoints()) << endl;
		}
	}
	else {
		maxTarget = int(_heroes.size());
		for (int i = 0; i < _heroes.size(); i++) {
			CharacterSheet* c = _heroes[i]->getComponent<CharacterSheet>(ecs::CharacterSheet);
			cout << i << ". " << std::setfill(' ') << std::left << setw(12) << c->name << setw(15) << "HP " + to_string(c->hitPoints()) + "/" + to_string(c->maxHitPoints()) << endl;
		}
	}

	int target;
	cout << "Choose target: ";
	while (true) {

		cin >> target;
		if (!cin.good() || !(target < maxTarget && target >= 0)) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "Use a valid index please: ";
		}
		else if (target < maxTarget && target >= 0)
			break;
		cin.sync();
	}
	cin.sync();

	throwHability(team ? dynamic_cast<Character*>(_enemies[target]) : dynamic_cast<Character*>(_heroes[target]), hability);
}

void CombatManager::throwHability(Character* objective, Hability* hability)
{
	cout << hability->name() << " on " << objective->name() << endl;
	int hit = hability->getCaster()->throw20PlusMod(hability->getMod(), true);
	if ((hability->getHabilityType() > 1) || objective->checkHit(hit)) {
		cout << hability->name() << " hits" << endl;;
		if (hit == 100)
			cout << "CRITICAL" << endl;
		hability->throwHability(objective, hit == 100);
	}
	else {
		if (hit == -100)
			cout << "CRITICAL FAILURE" << endl;
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
	if (!_combatEnd)
		consoleCombat();
}