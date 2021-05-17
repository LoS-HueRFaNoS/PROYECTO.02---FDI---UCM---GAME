#include "CharacterSheet.h"
#include <iostream>


bool CharacterSheet::recieveDamage(int damage, rpgLogic::damageType type)
{
	float res = weaknesses.getWeakness(type);

	int damageAfterRes = int(damage - (damage * res));

	std::cout << name << " recieves " << damageAfterRes << " damage" << "( " << damage << " " << (int)(res * 100) << "% RES)" << std::endl;

	_hitPoints -= damageAfterRes;

	if (_hitPoints < 0)
		_hitPoints = 0;

	return !_hitPoints;
}

void CharacterSheet::recieveHealing(int healing)
{
	_hitPoints += healing;

	std::cout << name << " heals for " << healing << " points" << std::endl;

	if (_hitPoints > _maxHitPoints)
		_hitPoints = _maxHitPoints;
}

void CharacterSheet::recieveMana(int mana)
{
	_manaPoints += mana;

	std::cout << name << " recovers " << mana << " mana points" << std::endl;

	if (_manaPoints > _maxManaPoints)
		_manaPoints = _maxManaPoints;
}

/*void CharacterSheet::recieveBuff(int buff,mainStat st)
{
	//cambiar el _hitPoints por el stat que aumenta

	_stats[size_t(st)].value += buff;

	//cout << name << " aumenta su "<< stat << buff << " puntos" << endl;


}*/
