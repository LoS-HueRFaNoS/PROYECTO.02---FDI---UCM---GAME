#include "../../Templates/RPGLogic.h"
#include "CombatManager.h"
#include "CharacterManager.h"
#include "PartyManager.h"
#include "../TheElementalMaze.h"
#include "../../Components/Laberinto.h"

#pragma region CombatePorConsola

#include <iomanip>
#include <string>

void CombatManager::showTeams()
{
	system("CLS");
	cout << "---------- HEROES ----------" << endl;
	for (Hero* h : _heroes) {
		CharacterSheet* s = h->getCharacterSheet();
		if (h->isDead())
			cout << std::setfill(' ') << std::left << setw(10) << s->name << std::right << setw(8) << "DEAD" << endl;
		else
		{
			cout << std::setfill(' ') << std::left << setw(12) << s->name << setw(15) << "HP " + to_string(s->hitPoints()) + "/" + to_string(s->maxHitPoints()) <<
				setw(15) << "MP " + to_string(s->manaPoints()) + "/" + to_string(s->maxManaPoints()) << std::right <<
				" STR " << std::setfill('0') << setw(2) << s->getStat(rpgLogic::ms::STR).value << "  CON " << std::setfill('0') << setw(2) <<
				s->getStat(rpgLogic::ms::CON).value << "  DEX " << std::setfill('0') << setw(2) << s->getStat(rpgLogic::ms::DEX).value << "  INT " <<
				std::setfill('0') << setw(2) << s->getStat(rpgLogic::ms::INT).value << endl;
		}
	}

	cout << endl << "---------- ENEMIES ----------" << endl;

	for (Enemy* e : _enemies) {
		CharacterSheet* s = e->getCharacterSheet();
		if (e->isDead())
			cout << std::setfill(' ') << std::left << setw(10) << s->name << std::right << setw(8) << "DEAD" << endl;
		else {
			cout << std::setfill(' ') << std::left << setw(12) << s->name << setw(15) << "HP " + to_string(s->hitPoints()) + "/" + to_string(s->maxHitPoints()) <<
				setw(15) << "MP " + to_string(s->manaPoints()) + "/" + to_string(s->maxManaPoints()) << std::right <<
				" STR " << std::setfill('0') << setw(2) << s->getStat(rpgLogic::ms::STR).value << "  CON " << std::setfill('0') << setw(2) <<
				s->getStat(rpgLogic::ms::CON).value << "  DEX " << std::setfill('0') << setw(2) << s->getStat(rpgLogic::ms::DEX).value << "  INT " <<
				std::setfill('0') << setw(2) << s->getStat(rpgLogic::ms::INT).value << endl;
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
	cout << "TARGETS (Press enter to cancel spell): " << endl;

	maxTargets = 0;
	try {
		for (Character* ch : getCurrentTargetList()) {

			CharacterSheet* c = ch->getCharacterSheet();
			cout << maxTargets << ". " << std::setfill(' ') << std::left << setw(12) << c->name << setw(15) << "HP " + to_string(c->hitPoints()) + "/" + to_string(c->maxHitPoints()) << endl;
			maxTargets++;

		}
	}
	catch (...) { cout << "ERROR: taking out targets"; }
	cout << "Choose target: ";
}

#pragma endregion


void CombatManager::startCombat(bool boss)
{
	_boss = boss;
	changeState(COMBAT_START);
}

void CombatManager::passTurn()
{
	if (!checkEnd()) {
		for (std::vector<Character*>::iterator it = _turnQueue.begin(); it != _turnQueue.end();) {
			if ((*it)->isDead()) {
				if (size_t((*it)->getType()) || (!size_t((*it)->getType()) && static_cast<Hero*>(*it)->getDeathGate()))
					it = _turnQueue.erase(it);
				else
					it++;
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
		end = end * h->isDead();
	if (end) {
		_win = false;
		return true;
	}
	end = true;
	for (Enemy* e : _enemies)
		end = end * e->isDead();
	return end;
}

bool CombatManager::isABoss()
{
	for (Enemy* e : _enemies)
		if (e->isBoss()) _boss = true;

	return _boss;
}

void CombatManager::tryEscape()
{
	if (isABoss()) {
		cout << "YOU CAN'T ESCAPE FROM THIS COMBAT\n";
		return;
	}

	cout << "YOU TRY TO ESCAPE\n";

	int tiradasH = 0;
	int tiradasE = 0;

	for (Hero* h : _heroes) {
		if (!h->isDead())
			tiradasH += h->throwStat(ms::DEX) + h->getMod(ms::DEX);
	}
	for (Enemy* e : _enemies) {
		if (!e->isDead())
			tiradasE += e->throwStat(ms::DEX) + e->getMod(ms::DEX);
	}

	cout << "Heroes: " << tiradasH << "\n";
	cout << "Enemies: " << tiradasE << "\n";

	if (tiradasH > tiradasE) {
		cout << "YOU ESCAPED \n";
		bool leftBehind = false;
		_exp = 0;

		for (Hero* h : _heroes)
			if (h->isDead()) {
				h->killHero();
				leftBehind = true;
				cout << "You just left " << h->name() << " behind !!! \n";
			}
		if (!leftBehind)
			cout << "No one was left behind\n";
		changeState(COMBAT_END);
		_win = true;
	}
	else {
		cout << "YOU FAILED TO ESCAPE \n";
	}
}

void CombatManager::endCombat()
{
	if (_win) {
		cout << "GANASTE, ERES BUENISIMO NO ?" << endl << _exp << " DE EXPERIENCIA GANADA" << endl;

		for (Hero* h : _heroes) {
			if (h->getDeathGate())
				TheElementalMaze::instance()->getPartyManager()->removeHero(h);
			else
				h->endCombat(_exp);
		}
		// si es lich derrotado y vuelve a empezar
	}
	else {
		cout << "PERDISTE, ASI ES LA VIDA" << endl;
		TheElementalMaze::instance()->getPartyManager()->partyLost();
		// vuelta al lobby
	}

	_heroes.clear();
	for (Enemy* e : _enemies) {
		e->disable();
	}
	_enemies.clear();
	TheElementalMaze::instance()->checkOutNoInitialEnemy();

	_turnQueue.clear();
}

void CombatManager::castHability(Hability* hability)
{
	ObjectiveType t = hability->getObjectiveType();
	cout << "\n";

	_habilityToCast = hability;

	switch (t)
	{
	case objTy::SINGLEALLY:
		targetList = currentCharacter->getType();
		changeState(ACTION_PHASE_TARGET);
		break;
	case objTy::SINGLEENEMY:
		targetList = (characterType)((int)currentCharacter->getType() ^ 1);
		changeState(ACTION_PHASE_TARGET);
		break;
	case objTy::ALLYTEAM:
		targetList = currentCharacter->getType();
		castToTeam();
		break;
	case objTy::ENEMYTEAM:
		targetList = (characterType)((int)currentCharacter->getType() ^ 1);
		castToTeam();
		break;
	case objTy::CASTER:
		throwHability(hability->getCaster(), hability);
		break;
	default:
		break;
	}
}


void CombatManager::castToTeam()
{
	if (size_t(targetList)) {
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

	throwHability(size_t(targetList) ? dynamic_cast<Character*>(_enemies[input]) : dynamic_cast<Character*>(_heroes[input]), _habilityToCast);
}

void CombatManager::throwHability(Character* objective, Hability* hability)
{
	cout << hability->name() << " on " << objective->name() << endl;
	int hit = hability->getCaster()->throw20PlusMod(hability->getMod(), true);
	if ((size_t(hability->getHabilityType()) > 1) || objective->checkHit(hit)) {
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
		ini.push_back(Initiative(_heroes[i]->getType(), i, throwDice(1, _heroes[i]->getStat(ms::DEX), false) + _heroes[i]->getMod(ms::DEX)));
	for (int i = 0; i < _enemies.size(); i++)
		ini.push_back(Initiative(_enemies[i]->getType(), i, throwDice(1, _enemies[i]->getStat(ms::DEX), false) + _enemies[i]->getMod(ms::DEX)));

	sort(ini.begin(), ini.end(), initiative_roll());

	for (Initiative i : ini) {
		if (size_t(i.type))
			_turnQueue.push_back(_enemies[i.pos]);
		else
			_turnQueue.push_back(_heroes[i.pos]);
	}
	currentCharacter = _turnQueue[0];
}

int CombatManager::calculateExp()
{
	for (Enemy* e : _enemies)
		_exp += e->getExp();

	return _exp;
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
		cout << "---------- START TURN ----------" << endl;
		changeState(ACTION_PHASE_SPELL);
		currentCharacter->startTurn(this);
		break;
	case ACTION_PHASE_SPELL:
		if (!size_t(currentCharacter->getType()))
			static_cast<Hero*>(currentCharacter)->showSpellList();
		break;
	case ACTION_PHASE_TARGET:
		showTargets();
		break;
	case END_TURN:
		currentCharacter->endTurn();
		cout << "---------- PRESS ENTER TO END TURN ----------" << endl;
		break;
	case COMBAT_END:
		endCombat();
		TheElementalMaze::instance()->changeState(gameST::END_COMBAT);
		changeState(NO_COMBAT);
		break;
	case NO_COMBAT:
		if (_win)
			TheElementalMaze::instance()->changeState(gameST::EXPLORING);
		else
			TheElementalMaze::instance()->changeState(gameST::LOBBY);

		break;
	default:
		break;
	}
}

void CombatManager::sendKeyEvent(int key)
{
	switch (_state)
	{
	case END_TURN:
		if (key == -1) changeState(PASS_TURN);
		break;
	case ACTION_PHASE_SPELL:

		switch (key)
		{
		case -1:
			changeState(END_TURN);
			break;
		case -4:
			tryEscape();
			break;
		case -5: case -6:
			TheElementalMaze::instance()->getPartyManager()->usePotion((Hero*)currentCharacter,(6+key));
			break;
		default:
			if (!size_t(currentCharacter->getType()))
				static_cast<Hero*>(currentCharacter)->manageInput(this, key);
			break;
		}
		break;
	case ACTION_PHASE_TARGET:
		if (key == -1) {
			_habilityToCast = nullptr;
			changeState(ACTION_PHASE_SPELL);
			break;
		}
		if (!size_t(currentCharacter->getType()) && key >= 0)
			castToSingleTarget(key);
		break;
	default:
		break;
	}
}

void CombatManager::update()
{
	if (TheElementalMaze::instance()->gameState() != gameST::COMBAT)
		return;
	if (stateChanged)
		onStateChanged();

#if (defined _DEBUG)
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
		else if (ih->isKeyDown(SDLK_RETURN)) 
										sendKeyEvent(-1);			// Saltar turno , terminar turno
		else if (ih->isKeyDown(SDLK_l)) sendKeyEvent(-2);			// Ataque ligero
		else if (ih->isKeyDown(SDLK_h)) sendKeyEvent(-3);			// Ataque pesado
		else if (ih->isKeyDown(SDLK_x)) sendKeyEvent(-4);			// Intentar Huir
		else if (ih->isKeyDown(SDLK_q)) sendKeyEvent(-5);			// Poción de mana
		else if (ih->isKeyDown(SDLK_e)) sendKeyEvent(-6);			// Poción de vida
	}
#endif
}