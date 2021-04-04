#include <fstream>
#include <iostream>
#include "CombatManager.h"
//#include "Equipement.h"

using namespace rpgLogic;


#pragma region CHARACTER

void Character::startTurn(CombatManager* cm)
{

	// Manejar estados y cambios que ocurren al pasar de turnos
	cout << name() << " TURN" << endl;
	manageTurn(cm);
}

void Character::loadFromTemplate(jute::jValue v, heroTemplate t)
{
	loadFromJson(v, t);
}

void Character::loadFromTemplate(jute::jValue v, enemyTemplate t)
{
	loadFromJson(v, t);
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

void Character::recieveBuff(int buff,mainStat stat)
{
	_sheet->changeStat(stat,buff);
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

void Hero::loadFromJson(jute::jValue v, int t) {

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
	_sheet->setMaxManaPoints(mp);

	// Guardamos las debilidades en un vector para luego inicializarlas
	vector<float> weak = vector<float>();
	for (int i = 0; i < _LastTypeId_; i++) {
		weak.push_back((float)v["Characters"][t]["Weaknesses"][i]["Value"].as_double());
	}

	_sheet->weaknesses = CharacterSheet::Weaknesses(weak);

	//_equipement -> loadWeaponTemplate("pruebasArmas.json", getRandomWeapon());

	//Escoge un arma aleatoria simple
	//int idRWeapons = v["Characters"][t]["Equipement"]["ListWeapons"].as_int();


	//int r2 = v["Characters"][t]["Equipement"]["ListArmors"].size();
	//int idRArmor = v["Characters"][t]["Equipement"]["ListArmors"][game_->getRandGen()->nextInt(0, r2)].as_int();

	// JSON DE ARMAS Y ARMADURAS 

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

	while (true) {

		cin >> spell;

		if (!cin.good() || spell >= _habilities.size()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "Use a valid index please: ";
		}
		else if (_habilities[spell]->getMana() > _sheet->manaPoints()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "Not enough mana, try again: ";
		}
		else if (spell == -1)
			break;
		else
		{
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cm->castHability(_habilities[spell]);
			//_sheet->setManaPoints(_sheet->manaPoints() - _habilities[spell]->getMana());
			break;
		}
		cin.sync();
	}
	cin.sync();
}

#pragma endregion

#pragma endregion



#pragma region ENEMY

void Enemy::loadFromJson(jute::jValue v, int t)
{

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
	_sheet->setMaxManaPoints(mp);

	// Guardamos las debilidades en un vector para luego inicializarlas
	vector<float> weak = vector<float>();
	for (int i = 0; i < _LastTypeId_; i++) {
		weak.push_back((float)v["Characters"][t]["Weaknesses"][i]["Value"].as_double());
	}

	_sheet->weaknesses = CharacterSheet::Weaknesses(weak);

}

void Enemy::manageTurn(CombatManager* cm)
{
	cout << "AQUI EL ENEMIGO HACE COSAS" << endl;
}

#pragma endregion
