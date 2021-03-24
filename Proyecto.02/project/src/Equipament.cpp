#include <fstream>
#include <iostream>
#include "Equipament.h"
#include "jute.h"

using namespace rpgLogic;

void Equipament::loadWeaponTemplate(weaponsId t)
{
	string file = Resources::jsons_[Resources::Weapons].filename;
	loadFromJson(file, t);
}


//void Weapon::loadFromJson(string json, int t, string weaponGroup)
//{
//	ifstream in(json);
//
//	if (in.is_open()) {
//		// Guardamos todo lo que se puede leer del archivo en un string
//		string str = "";
//		string tmp;
//		while (getline(in, tmp)) str += tmp;
//
//		in.close();
//
//		// El parser lo transforma de string a un Jvalue del que podremos sacar la información
//		jute::jValue v = jute::parser::parse(str);
//
//		name = v["Armas"][weaponGroup][t]["Name"].as_string();
//
//		_damageType = v["Armas"][t]["Type"].as_int();
//
//		int damage = getDamage(v["Armas"][t]["Type"].as_int());
//
//		int weight = v["Armas"][t]["Weight"].as_int();
//	}
//
//	else {
//		// HACER THROW EN EL ELSE
//	}
//}

