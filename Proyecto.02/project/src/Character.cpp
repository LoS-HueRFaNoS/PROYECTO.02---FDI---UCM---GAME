#include "Character.h"
using namespace rpgLogic;


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
	for (Hability* h : _habilities)
		h->passTurn();
}
