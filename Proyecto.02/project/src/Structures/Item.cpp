#include <fstream>
#include <iostream>
#include "Item.h"

using namespace rpgLogic;

void Item::elementalAfinity()
{
	if (throwDice(1, 100, false) > 50)
	{
		int afinityType = throwDice(1, size_t(damTy::_lastDamageTypeId_) - 1, false);
		int afinityAmount = throwDice(1, 100, false);

		sellValue += afinityAmount;
		buyValue += afinityAmount;

		_elementalAfinity.changeWeakness(damageType(afinityType), (float)afinityAmount / 100.0);

		elementalAfinity();
	}
}

void Weapon::loadWeaponTemplate(jute::jValue v, weaponId t)
{
	_name = v["Armas"][size_t(t)]["Name"].as_string();
	_description = "Arma interesante";

	int _damType = v["Armas"][size_t(t)]["Type"].as_int();
	_damageType = damageType(_damType);

	marcial = v["Armas"][size_t(t)]["Marcial"].as_bool();

	damage = v["Armas"][size_t(t)]["Damage"].as_int();

	diceNumber = v["Armas"][size_t(t)]["Ndice"].as_int();

	hands = v["Armas"][size_t(t)]["Damage"].as_int();

	vector<float> resist = vector<float>();
	for (int i = 0; i < size_t(damTy::_lastDamageTypeId_); i++) {
		resist.push_back((float)v["Armas"][size_t(t)]["DamageElement"][i]["Value"].as_double());
	}

	_elementalAfinity = Weaknesses(resist);

	elementalAfinity();

	weapId = t;
}

void Armor::loadArmorTemplate(jute::jValue v, armorId t)
{
	_name = v["Armaduras"][size_t(t)]["Name"].as_string();
	_description = v["Armaduras"][size_t(t)]["Description"].as_string();

	// Guardamos las debilidades en un vector para luego inicializarlas
	vector<float> weak = vector<float>();
	for (int i = 0; i < size_t(damTy::_lastDamageTypeId_); i++) {
		weak.push_back((float)v["Armaduras"][size_t(t)]["Weaknesses"][i]["Value"].as_double());
	}

	_elementalAfinity = Weaknesses(weak);

	elementalAfinity();

	int statNeed = v["Armaduras"][size_t(t)]["TypeNeeded"].as_int();
	_statNeeded = mainStat(statNeed);

	minStatNeeded = v["Armaduras"][size_t(t)]["MinNeed"].as_int();

	armId = t;
}

