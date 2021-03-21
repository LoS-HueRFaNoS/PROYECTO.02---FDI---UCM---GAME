#include "CharacterSheet.h"


bool CharacterSheet::recieveDamage(int damage, rpgLogic::damageType type)
{
	float res = weaknesses.getWeakness(type);

	damage -= damage * res;

	cout << name << " recibe " << damage << "de danyo - HabilityResources.cpp linea 13" << endl;

	_hitPoints -= damage;

	return _hitPoints <= 0;
}
