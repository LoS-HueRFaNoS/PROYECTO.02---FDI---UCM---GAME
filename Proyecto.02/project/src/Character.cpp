#include "Character.h"
using namespace rpgLogic;

bool Character::checkHit(int hit)
{
	return hit > (throwDice(1, _sheet.getStat(DEX).value) + _sheet.getStat(DEX).getMod());
}

void Character::recieveDamage(int damage, rpgLogic::damageType type)
{
	if (_sheet.recieveDamage(damage, type)) {
		cout << "Se ha muerto - Character.cpp linea 12" << endl;
	}

}

bool Character::savingThrow(int save, rpgLogic::mainStat stat)
{
	return save < (throwDice(1, 20) + _sheet.getStat(stat).getMod());
}

void Character::startTurn()
{

	for (std::vector<AlteredState*>::iterator it = _states.begin(); it != _states.end();) {
		if (!(*it)->passTurn(this)) {
			AlteredState* s = (*it);
			it = _states.erase(it);
			delete s;
		}
		else {
			it++;
		}
	}

	for (Hability* h : _habilities)
		h->passTurn();
}
