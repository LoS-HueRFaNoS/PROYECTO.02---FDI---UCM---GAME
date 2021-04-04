#include <fstream>
#include <iostream>
#include "Item.h"
#include "jute.h"

using namespace rpgLogic;

void Weapon::loadWeaponTemplate(weaponsId t)
{
	loadFromJson(Resources::jsons_[Resources::Weapons].filename, t);
}

void Armor::loadArmorTemplate(armorId t)
{
	loadFromJson(Resources::jsons_[Resources::Armors].filename, t);
}

void Weapon::loadFromJson(string json, int t)
{
	ifstream in(json);

	if (in.is_open()) {
		// Guardamos todo lo que se puede leer del archivo en un string
		string str = "";
		string tmp;
		while (getline(in, tmp)) str += tmp;

		in.close();

		// El parser lo transforma de string a un Jvalue del que podremos sacar la información
		jute::jValue v = jute::parser::parse(str);

		_name = v["Armas"][t]["Name"].as_string();
		_description = "Arma interesante";
		
		int _damType = v["Armas"][t]["Type"].as_int();
		_damageType = damageType(_damType);

		marcial = v["Armas"][t]["Marcial"].as_bool();

		damage = v["Armas"][t]["Damage"].as_int();

		diceNumber = v["Armas"][t]["Ndice"].as_int();

		hands = v["Armas"][t]["Damage"].as_int();
	}

	else {
		// HACER THROW EN EL ELSE
	}
}

void Armor::loadFromJson(string json, int t)
{
	ifstream in(json);

	if (in.is_open()) {
		// Guardamos todo lo que se puede leer del archivo en un string
		string str = "";
		string tmp;
		while (getline(in, tmp)) str += tmp;

		in.close();

		// El parser lo transforma de string a un Jvalue del que podremos sacar la información
		jute::jValue v = jute::parser::parse(str);

		_name = v["Armaduras"][t]["Name"].as_string();
		_description = "Armadura interesante";

		for (int i = 0; i < _LastTypeId_; i++) {
			_resistances.push_back((float)v["Armaduras"][t]["Weaknesses"][i]["Value"].as_double());
		}

		int statNeed = v["Armaduras"][t]["TypeNeeded"].as_int();
		_statNeeded = mainStat(statNeed);

		minStatNeeded = v["Armaduras"][t]["MinNeed"].as_int();
	}
}