#include "Character.h"
#include <fstream>
#include <iostream>
#include "jute.h"
using namespace rpgLogic;


void Character::loadFromTemplate(characterTemplate t)
{
	string file = Resources::jsons_[Resources::Heroes].filename;
	loadFromJson(file, t);
}

void Character::loadFromTemplate(enemyTemplate t)
{
	string file = Resources::jsons_[Resources::Enemies].filename;
	loadFromJson(file, t);
}

void Character::recieveDamage(int damage, rpgLogic::damageType type)
{
	if (_sheet->recieveDamage(damage, type)) {
		cout << "Se ha muerto - Character.cpp linea 12" << endl;
	}

}

bool Character::savingThrow(int save, rpgLogic::mainStat stat)
{
	return save < (throwDice(1, 20) + _sheet->getStat(stat).getMod());
}

void Character::startTurn()
{

}

void Hero::loadFromJson(string json, int t)
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

		// Buscamos las stats en el json dentro de nuestro heroe "t" y asignamos un valor aleatorio entre los valores dados
		for (int i = 0; i < _LastStatId_; i++) {
			int min = v["Characters"][t]["Stats"][i]["Min"].as_int();
			int max = v["Characters"][t]["Stats"][i]["Max"].as_int();
			_sheet->setStat(i, game_->getRandGen()->nextInt(min, max + 1));
		}

		_sheet->name = v["Characters"][t]["Name"].as_string();

		// Igual con la vida y el mana
		_sheet->setHitPoints(v["Characters"][t]["HitPoints"].as_int());
		_sheet->setManaPoints(v["Characters"][t]["ManaPoints"].as_int());

		// Guardamos las debilidades en un vector para luego inicializarlas
		vector<float> weak = vector<float>();
		for (int i = 0; i < _LastTypeId_; i++) {
			weak.push_back((float)v["Characters"][t]["Weaknesses"][i]["Value"].as_double());
		}

		_sheet->weaknesses = CharacterSheet::Weaknesses(weak);

		//Si r1 es 2, puede armas simples y marciales
		int r1 = v["Characters"][t]["Equipement"]["ListWeapons"].size();
		//Escoge un arma aleatoria simple
		int idRWeapons = v[game_->getRandGen()->nextInt(0, _LastWeaponId_)].as_int();


		//int r2 = v["Characters"][t]["Equipement"]["ListArmors"].size();
		//int idRArmor = v["Characters"][t]["Equipement"]["ListArmors"][game_->getRandGen()->nextInt(0, r2)].as_int();

		// JSON DE ARMAS Y ARMADURAS 

	}
	else {
		// HACER THROW EN EL ELSE
	}
}

void Enemy::loadFromJson(string json, int t)
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

		// Buscamos las stats en el json dentro de nuestro heroe "t" y asignamos un valor aleatorio entre los valores dados
		for (int i = 0; i < _LastStatId_; i++) {
			_sheet->setStat(i, v["Characters"][t]["Stats"][i]["Value"].as_int());
		}

		_sheet->name = v["Characters"][t]["Name"].as_string();

		// Igual con la vida y el mana
		_sheet->setHitPoints(v["Characters"][t]["HitPoints"].as_int());
		_sheet->setManaPoints(v["Characters"][t]["ManaPoints"].as_int());

		// Guardamos las debilidades en un vector para luego inicializarlas
		vector<float> weak = vector<float>();
		for (int i = 0; i < _LastTypeId_; i++) {
			weak.push_back((float)v["Characters"][t]["Weaknesses"][i]["Value"].as_double());
		}

		_sheet->weaknesses = CharacterSheet::Weaknesses(weak);
	}

	else {
		// HACER THROW EN EL ELSE
	}
}

