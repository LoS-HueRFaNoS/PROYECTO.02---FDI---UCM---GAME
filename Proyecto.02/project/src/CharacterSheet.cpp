#include "CharacterSheet.h"
#include <fstream>
#include <iostream>
#include "jute.h"

void CharacterSheet::loadFromJson(string file, int t)
{
	ifstream in(file);

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
			_stats[i].value = game_->getRandGen()->nextInt(min, max + 1);
		}

		// Igual con la vida y el mana
		hitPoints = v["Characters"][t]["HitPoints"].as_int();
		manaPoints = v["Characters"][t]["ManaPoints"].as_int();

		// Guardamos las debilidades en un vector para luego inicializarlas
		vector<float> weak = vector<float>();
		for (int i = 0; i < _LastTypeId_; i++) {
			weak.push_back((float)v["Characters"][t]["Weaknesses"][i]["Value"].as_double());
		}
		weaknesses = Weaknesses(weak);

		if (v["Characters"][t]["Equipement"]["Check"].as_bool()) {
			int r1 = v["Characters"][t]["Equipement"]["ListWeapons"].size();
			int r2 = v["Characters"][t]["Equipement"]["ListArmors"].size();

			int idRWeapons = v["Characters"][t]["Equipement"]["ListWeapons"][game_->getRandGen()->nextInt(0, r1)].as_int();
			int idRArmor = v["Characters"][t]["Equipement"]["ListArmors"][game_->getRandGen()->nextInt(0, r2)].as_int();

			// JSON DE ARMAS Y ARMADURAS 

		}
		else {

		}
	}
	else {
		// HACER THROW EN EL ELSE
	}
}

void CharacterSheet::loadFromJson(characterTemplate t)
{
	string file = Resources::jsons_[Resources::Heroes].filename;
	loadFromJson(file, t);
}

void CharacterSheet::loadFromJson(enemyTemplate t)
{
	string file = Resources::jsons_[Resources::Enemies].filename;
	loadFromJson(file, t);
}

bool CharacterSheet::recieveDamage(int damage, rpgLogic::damageType type)
{
	float res = weaknesses.getWeakness(type);

	damage -= damage * res;

	cout << name << " recibe " << damage << "de daño - HabilityResources.cpp linea 13" << endl;

	hitPoints -= damage;

	return hitPoints <= 0;
}
