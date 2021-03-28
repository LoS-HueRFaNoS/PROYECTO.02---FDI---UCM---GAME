#include <fstream>
#include <iostream>
#include "CombatManager.h"
#include "jute.h"
using namespace rpgLogic;


#pragma region CHARACTER

void Character::startTurn(CombatManager* cm)
{

	// Manejar estados y cambios que ocurren al pasar de turnos
	cout << name() << " TURN" << endl;
	manageTurn(cm);
}

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
		cout << name() << " has fainted" << endl;
	}
}

void Character::recieveHealing(int healing)
{
	_sheet->recieveHealing(healing);
}

bool Character::savingThrow(int save, rpgLogic::mainStat stat)
{
	cout << "Saving throw (" << save << "): " << endl;
	return save < throw20PlusMod(stat, false);
}

int Character::throw20PlusMod(mainStat mod, bool crit)
{
	int dice = rpgLogic::throwDice(1, 20, false);
	int throwS = dice + _sheet->getStat(mod).getMod();
	cout << name() << " throws a " << throwS << " (" << dice << " " << _sheet->getStat(mod).getMod() << " MOD)" << endl;
	if ((dice != 20 && dice != 1) || !crit)
		return throwS;
	else
		return dice == 20 ? 100 : -100;
}

int Character::throwStat(mainStat stat)
{
	int dice = rpgLogic::throwDice(1, _sheet->getStat(stat).value, false);
	int throwS = dice + _sheet->getStat(stat).getMod();
	cout << name() << " throws a " << throwS << " (" << dice << " " << _sheet->getStat(stat).getMod() << " MOD)" << endl;
	return throwS;
}

bool Character::checkHit(int hit)
{
	return hit > throwStat(DEX);
}

#pragma endregion


#pragma region HERO

void Hero::loadFromJson(string json, int t)
{
	ifstream in(json);

	if (in.is_open()) {
		// Guardamos todo lo que se puede leer del archivo en un string
		string str = "";
		string tmp;
		while (getline(in, tmp)) str += tmp;

		in.close();

		// El parser lo transforma de string a un Jvalue del que podremos sacar la informaci�n
		jute::jValue v = jute::parser::parse(str);

		// Buscamos las stats en el json dentro de nuestro heroe "t" y asignamos un valor aleatorio entre los valores dados
		for (int i = 0; i < _LastStatId_; i++) {
			int min = v["Characters"][t]["Stats"][i]["Min"].as_int();
			int max = v["Characters"][t]["Stats"][i]["Max"].as_int();
			_sheet->setStat(i, game_->getRandGen()->nextInt(min, max + 1));
		}

		_sheet->name = v["Characters"][t]["Name"].as_string();

		// Igual con la vida y el mana
		int hp = v["Characters"][t]["HitPoints"].as_int();
		int mp = v["Characters"][t]["ManaPoints"].as_int();
		_sheet->setHitPoints(hp);
		_sheet->setMaxHitPoints(hp);
		_sheet->setManaPoints(mp);
		_sheet->setManaPoints(mp);

		// Guardamos las debilidades en un vector para luego inicializarlas
		vector<float> weak = vector<float>();
		for (int i = 0; i < _LastTypeId_; i++) {
			weak.push_back((float)v["Characters"][t]["Weaknesses"][i]["Value"].as_double());
		}

		_sheet->weaknesses = CharacterSheet::Weaknesses(weak);

		//Si r1 es 2, puede armas simples y marciales
		int r1 = v["Characters"][t]["Equipement"]["ListWeapons"].size();
		//Escoge un arma aleatoria simple
		// int idRWeapons = v["Characters"][t]["Equipement"]["ListWeapons"][game_->getRandGen()->nextInt(0, r1)].as_int();


		//int r2 = v["Characters"][t]["Equipement"]["ListArmors"].size();
		//int idRArmor = v["Characters"][t]["Equipement"]["ListArmors"][game_->getRandGen()->nextInt(0, r2)].as_int();

		// JSON DE ARMAS Y ARMADURAS 

	}
	else {
		// HACER THROW EN EL ELSE
	}
}

void Hero::manageTurn(CombatManager* cm)
{
	consoleTurn(cm);
}

#pragma region CombatePorConsola

#include <iomanip>

void Hero::consoleTurn(CombatManager* cm)
{
	cout << "\nSpells: " << endl;

	for (int i = 0; i < _habilities.size(); i++)
		cout << i << ". " << setw(30) << _habilities[i]->name() << _habilities[i]->getMana() << setw(15) << " MP" << _habilities[i]->description() << endl;

	int spell;
	cout << "Choose a spell to cast (-1 to skip turn): ";
	cin >> spell;

	if (spell >= _habilities.size() || spell == -1) {
		if (spell != -1)
			cout << "Tu lo que eres es un listo, pierdes el turno por tonto" << endl;
		return;
	}

	if (_habilities[spell]->getMana() > _sheet->manaPoints()) {
		cout << "PIERDES EL TURNO PORQUE NO SABES CONTAR" << endl;
	}
	else
	{
		cm->castHability(_habilities[spell]);

		//_sheet->setManaPoints(_sheet->manaPoints() - _habilities[spell]->getMana());
	}

}

#pragma endregion

#pragma endregion



#pragma region ENEMY

void Enemy::loadFromJson(string json, int t)
{
	ifstream in(json);

	if (in.is_open()) {
		// Guardamos todo lo que se puede leer del archivo en un string
		string str = "";
		string tmp;
		while (getline(in, tmp)) str += tmp;

		in.close();

		// El parser lo transforma de string a un Jvalue del que podremos sacar la informaci�n
		jute::jValue v = jute::parser::parse(str);

		// Buscamos las stats en el json dentro de nuestro heroe "t" y asignamos un valor aleatorio entre los valores dados
		for (int i = 0; i < _LastStatId_; i++) {
			_sheet->setStat(i, v["Characters"][t]["Stats"][i]["Value"].as_int());
		}

		_sheet->name = v["Characters"][t]["Name"].as_string();

		// Igual con la vida y el mana
		int hp = v["Characters"][t]["HitPoints"].as_int();
		int mp = v["Characters"][t]["ManaPoints"].as_int();
		_sheet->setHitPoints(hp);
		_sheet->setMaxHitPoints(hp);
		_sheet->setManaPoints(mp);
		_sheet->setManaPoints(mp);

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

void Enemy::manageTurn(CombatManager* cm)
{
	cout << "AQUI EL ENEMIGO HACE COSAS" << endl;
}

#pragma endregion
