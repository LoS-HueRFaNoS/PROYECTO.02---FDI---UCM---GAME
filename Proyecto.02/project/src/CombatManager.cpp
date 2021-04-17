#include "CombatManager.h"
#include "RPGLogic.h"
#include "CharacterManager.h"
#include "../TheElementalMaze.h"


#pragma region CombatePorConsola

#include <iomanip>
#include <string>

void CombatManager::showTeams()
{
	system("CLS");
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

void CombatManager::showTargets()
{
	cout << "TARGETS" << endl;
	maxTargets = 0;

	if (targetList) {
		maxTargets = int(_enemies.size());
		for (int i = 0; i < _enemies.size(); i++) {
			CharacterSheet* c = _enemies[i]->getComponent<CharacterSheet>(ecs::CharacterSheet);
			cout << i << ". " << std::setfill(' ') << std::left << setw(12) << c->name << setw(15) << "HP " + to_string(c->hitPoints()) + "/" + to_string(c->maxHitPoints()) << endl;
		}
	}
	else {
		maxTargets = int(_heroes.size());
		for (int i = 0; i < _heroes.size(); i++) {
			CharacterSheet* c = _heroes[i]->getComponent<CharacterSheet>(ecs::CharacterSheet);
			cout << i << ". " << std::setfill(' ') << std::left << setw(12) << c->name << setw(15) << "HP " + to_string(c->hitPoints()) + "/" + to_string(c->maxHitPoints()) << endl;
		}
	}
	cout << "Choose target: ";
}

#pragma endregion


void CombatManager::startCombat()
{
	changeState(COMBAT_START);
}

void CombatManager::passTurn()
{
	if (!checkEnd()) {
		for (std::vector<Character*>::iterator it = _turnQueue.begin(); it != _turnQueue.end();) {
			if ((*it)->isDead() && (*it)->getType()) {
				it = _turnQueue.erase(it);
			}
			else {
				it++;
			}
		}
		_turn = ++_turn % _turnQueue.size();
		currentCharacter = _turnQueue[_turn];
		changeState(START_TURN);
	}
	else
		changeState(COMBAT_END);
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
	if (_win) {
		cout << "GANASTE, ERES BUENISIMO NO ?" << endl << _exp << " DE EXPERIENCIA GANADA" << endl;
	}
	else
		cout << "PERDISTE, ASI ES LA VIDA" << endl;

	_heroes.clear();
	for (Enemy* e : _enemies) {
		TheElementalMaze::instance()->getCharacterManager()->removeEntity(e);
	}
}

void CombatManager::castHability(Hability* hability)
{
	ObjectiveType t = hability->getObjectiveType();
	cout << "\n";

	_habilityToCast = hability;

	switch (t)
	{
	case SINGLEALLY:
		targetList = currentCharacter->getType();
		changeState(ACTION_PHASE_TARGET);
		break;
	case SINGLEENEMY:
		targetList = (characterType)((int)currentCharacter->getType() ^ 1);
		changeState(ACTION_PHASE_TARGET);
		break;
	case ALLYTEAM:
		targetList = currentCharacter->getType();
		castToTeam();
		break;
	case ENEMYTEAM:
		targetList = (characterType)((int)currentCharacter->getType() ^ 1);
		castToTeam();
		break;
	case CASTER:
		throwHability(hability->getCaster(), hability);
		break;
	default:
		break;
	}
}


void CombatManager::castToTeam()
{
	if (targetList) {
		for (Enemy* e : _enemies)
			if (!e->isDead())throwHability(e, _habilityToCast);
	}
	else {
		for (Hero* h : _heroes)
			if (!h->isDead())throwHability(h, _habilityToCast);
	}

}

void CombatManager::castToSingleTarget(int input)
{
	if (!(input < maxTargets && input >= 0)) {
		cout << "Use a valid index please: \n";
		return;
	}

	throwHability(targetList ? dynamic_cast<Character*>(_enemies[input]) : dynamic_cast<Character*>(_heroes[input]), _habilityToCast);
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

	changeState(END_TURN);
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
	currentCharacter = _turnQueue[0];
}

void CombatManager::calculateExp()
{
	for (Enemy* e : _enemies)
		_exp += e->getExp();
}


void CombatManager::onStateChanged()
{
	stateChanged = false;

	switch (_state)
	{
	case COMBAT_START:
		_turn = 0;
		_exp = 0;
		currentCharacter = nullptr;
		calculateTurns();
		calculateExp();
		changeState(START_TURN);
		break;
	case PASS_TURN:
		passTurn();
		break;
	case START_TURN:
		showTeams();
		showQ();
		cout << "---------- PRESS ENTER TO START TURN ----------" << endl;
		break;
	case ACTION_PHASE_SPELL:
		if (!currentCharacter->getType())
			static_cast<Hero*>(currentCharacter)->showSpellList();
		break;
	case ACTION_PHASE_TARGET:
		showTargets();
		break;
	case END_TURN:
		cout << "---------- PRESS ENTER TO END TURN ----------" << endl;
		break;
	case COMBAT_END:
		endCombat();
		break;
	case NO_COMBAT:
		break;
	default:
		break;
	}
}

void CombatManager::sendKeyEvent(int key)
{
	switch (_state)
	{
	case START_TURN:
		if (key == -1) {
			changeState(ACTION_PHASE_SPELL);
			currentCharacter->startTurn(this);
		}
		break;
	case END_TURN:
		if (key == -1) changeState(PASS_TURN);
		break;
	case ACTION_PHASE_SPELL:
		if (!currentCharacter->getType())
			static_cast<Hero*>(currentCharacter)->manageInput(this, key);
		break;
	case ACTION_PHASE_TARGET:
		if (!currentCharacter->getType())
			castToSingleTarget(key);
		break;
	default:
		break;
	}

}


void CombatManager::update()
{
	if (stateChanged)
		onStateChanged();

	InputHandler* ih = InputHandler::instance();

	if (ih->keyDownEvent()) {
		if (ih->isKeyDown(SDLK_0)) sendKeyEvent(0);
		else if (ih->isKeyDown(SDLK_1)) sendKeyEvent(1);
		else if (ih->isKeyDown(SDLK_2)) sendKeyEvent(2);
		else if (ih->isKeyDown(SDLK_3)) sendKeyEvent(3);
		else if (ih->isKeyDown(SDLK_4)) sendKeyEvent(4);
		else if (ih->isKeyDown(SDLK_5)) sendKeyEvent(5);
		else if (ih->isKeyDown(SDLK_6)) sendKeyEvent(6);
		else if (ih->isKeyDown(SDLK_7)) sendKeyEvent(7);
		else if (ih->isKeyDown(SDLK_8)) sendKeyEvent(8);
		else if (ih->isKeyDown(SDLK_9)) sendKeyEvent(9);
		else if (ih->isKeyDown(SDLK_RETURN)) sendKeyEvent(-1);
	}

}