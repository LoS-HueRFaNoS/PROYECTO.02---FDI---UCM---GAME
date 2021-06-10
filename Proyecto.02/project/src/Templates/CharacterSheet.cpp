#include "CharacterSheet.h"
#include "../Managers/game/ChatManager.h"
#include <iostream>


std::string CharacterSheet::getResName(rpgLogic::damageType type)
{
	std::string ret = "";

	switch (type)
	{
	case rpgLogic::damageType::BLUNT:
		ret = " blunt";
		break;
	case rpgLogic::damageType::PIERCE:
		ret = " piercing";
		break;
	case rpgLogic::damageType::SLASH:
		ret = " slash";
		break;
	case rpgLogic::damageType::FIRE:
		ret = " fire";
		break;
	case rpgLogic::damageType::WATER:
		ret = " water";
		break;
	case rpgLogic::damageType::ICE:
		ret = " ice";
		break;
	case rpgLogic::damageType::EARTH:
		ret = " earth";
		break;
	case rpgLogic::damageType::WIND:
		ret = " wind";
		break;
	case rpgLogic::damageType::LIGHT:
		ret = " light";
		break;
	case rpgLogic::damageType::DARK:
		ret = " dark";
		break;
	default:
		ret = "damageTypeError";
		break;
	}
	return ret;
}

bool CharacterSheet::recieveDamage(int damage, rpgLogic::damageType type, bool enemy)
{
	float res = weaknesses.getWeakness(type);

	int damageAfterRes = int(damage - (damage * res));

	std::string out = name + " recieves " + std::to_string(damageAfterRes) + getResName(type) + " damage" + "( " + std::to_string(damage) + " " + std::to_string((int)(res * 100)) + "% RES)";
	std::cout << out << std::endl;
	ChatManager::instance()->add(out, enemy ?  linCol::Green : linCol::Red);

	_hitPoints -= damageAfterRes;

	if (_hitPoints < 0)
		_hitPoints = 0;

	return !_hitPoints;
}

void CharacterSheet::recieveHealing(int healing, bool enemy)
{
	_hitPoints += healing;

	std::string out = name + " heals for " + std::to_string(healing) + " points";
	std::cout << out << std::endl;
	ChatManager::instance()->add(out, enemy ? linCol::Red : linCol::Green);

	if (_hitPoints > _maxHitPoints)
		_hitPoints = _maxHitPoints;
}

void CharacterSheet::recieveMana(int mana)
{
	_manaPoints += mana;

	std::string out = name + " recovers " + std::to_string(mana) + " mana points";
	std::cout << out << std::endl;
	ChatManager::instance()->add(out, linCol::Blue);

	if (_manaPoints > _maxManaPoints)
		_manaPoints = _maxManaPoints;
}

/*void CharacterSheet::recieveBuff(int buff,mainStat st)
{
	//cambiar el _hitPoints por el stat que aumenta

	_stats[size_t(st)].value += buff;

	//cout << name << " aumenta su "<< stat << buff << " puntos" << endl;


}*/
