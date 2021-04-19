#include <fstream>
#include <iostream>
#include "Item.h"


using namespace rpgLogic;

void Weapon::loadWeaponTemplate(jute::jValue v, weaponId t)
{
	_name = v["Armas"][t]["Name"].as_string();
	_description = "Arma interesante";

	int _damType = v["Armas"][t]["Type"].as_int();
	_damageType = damageType(_damType);

	marcial = v["Armas"][t]["Marcial"].as_bool();

	damage = v["Armas"][t]["Damage"].as_int();

	diceNumber = v["Armas"][t]["Ndice"].as_int();

	hands = v["Armas"][t]["Damage"].as_int();
}

void Armor::loadArmorTemplate(jute::jValue v, armorId t)
{

	_name = v["Armaduras"][t]["Name"].as_string();
	_description = v["Armaduras"][t]["Description"].as_string();

	// Guardamos las debilidades en un vector para luego inicializarlas
	vector<float> weak = vector<float>();
	for (int i = 0; i < _LastTypeId_; i++) {
		weak.push_back((float)v["Armaduras"][t]["Weaknesses"][i]["Value"].as_double());
	}

	_weaknesses = Weaknesses(weak);

	int statNeed = v["Armaduras"][t]["TypeNeeded"].as_int();
	_statNeeded = mainStat(statNeed);

	minStatNeeded = v["Armaduras"][t]["MinNeed"].as_int();
}