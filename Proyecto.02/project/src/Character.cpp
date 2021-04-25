#include <fstream>
#include <iostream>
#include "CombatManager.h"
#include "ItemManager.h"
#include "Character.h"
#include "../TheElementalMaze.h"

using namespace rpgLogic;

#pragma region CHARACTER

Character::~Character()
{
	for (Hability* h : _habilitiesArray)
	{
		delete h;
		h = nullptr;
	}
	for (Condition* c : _conditonsArray)
	{
		delete c;
		c = nullptr;
	}
}

void Character::startTurn(CombatManager* cm)
{

	// Manejar estados y cambios que ocurren al pasar de turnos
	cout << name() << " TURN" << endl;

	for (std::vector<Condition*>::iterator it = _conditions[ON_TURN_STARTED].begin(); it != _conditions[ON_TURN_STARTED].end();)
	{
		if (!(*it)->onTurnStarted())
		{
			Condition* temp = (*it);
			removeCondition((*it)->getId());
			it = _conditions[ON_TURN_STARTED].erase(it);
			delete temp;
		}
		else
		{
			it++;
		}
	}

	manageTurn(cm);
}

void Character::endTurn()
{
	for (std::vector<Condition*>::iterator it = _conditions[ON_TURN_ENDED].begin(); it != _conditions[ON_TURN_ENDED].end();)
	{
		if (!(*it)->onTurnEnd())
		{
			Condition* temp = (*it);
			removeCondition((*it)->getId());
			it = _conditions[ON_TURN_ENDED].erase(it);
			delete temp;
		}
		else
		{
			it++;
		}
	}
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
	for (std::vector<Condition*>::iterator it = _conditions[ON_ATTACK_RECIEVED].begin(); it != _conditions[ON_ATTACK_RECIEVED].end();)
	{
		if (!(*it)->onAttackRecieved(damage))
		{
			Condition* temp = (*it);
			removeCondition((*it)->getId());
			it = _conditions[ON_ATTACK_RECIEVED].erase(it);
			delete temp;
		}
		else
		{
			it++;
		}
	}
	if (_sheet->recieveDamage(damage, type))
	{
		cout << name() << " has fainted" << endl;
		for (std::vector<Condition*>::iterator it = _conditions[ON_DEATH].begin(); it != _conditions[ON_DEATH].end();)
		{
			if (!(*it)->onDeath())
			{
				Condition* temp = (*it);
				removeCondition((*it)->getId());
				it = _conditions[ON_DEATH].erase(it);
				delete temp;
			}
			else
			{
				it++;
			}
		}
	}
}

void Character::recieveHealing(int healing)
{
	_sheet->recieveHealing(healing);
}

void Character::recieveBuff(int buff, mainStat stat)
{
	_sheet->changeStat(stat, buff);
}

bool Character::savingThrow(int save, rpgLogic::mainStat stat)
{
	cout << "Saving throw (" << save << "): " << endl;
	bool saved = save < throw20PlusMod(stat, false);
	string mess = saved ? "Successful throw\n" : "Failed throw\n";
	cout << mess;
	return saved;
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

Hero::~Hero()
{
	delete _weapon;
	_weapon = nullptr;
	delete _armor;
	_armor = nullptr;
}

void Hero::loadFromJson(jute::jValue v, int t)
{
	template_ = (heroTemplate)t;

	// Buscamos las stats en el json dentro de nuestro heroe "t" y asignamos un valor aleatorio entre los valores dados
	for (int i = 0; i < _LastStatId_; i++)
	{
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
	for (int i = 0; i < _LastTypeId_; i++)
	{
		weak.push_back((float)v["Characters"][t]["Weaknesses"][i]["Value"].as_double());
	}

	_sheet->weaknesses = Weaknesses(weak);

	_marcial = v["Characters"][t]["Marcial"].as_bool();

	int r1 = v["Characters"][t]["Equipement"]["ListWeapons"].size();
	int idRWeapon = v["Characters"][t]["Equipement"]["ListWeapons"][game_->getRandGen()->nextInt(0, r1)].as_int();
	_weapon = TheElementalMaze::instance()->getItemManager()->getWeaponFromId(weaponId(idRWeapon));

	int r2 = v["Characters"][t]["Equipement"]["ListArmors"].size();
	int idRArmor = v["Characters"][t]["Equipement"]["ListArmors"][game_->getRandGen()->nextInt(0, r2)].as_int();
	_armor = TheElementalMaze::instance()->getItemManager()->getArmorFromId(armorId(idRArmor));
}

void Hero::endCombat()
{
}

#include <iomanip>

void Hero::showSpellList()
{
	if (!isDead())
	{
		cout << "\nSpells: " << endl;

		for (int i = 0; i < _habilities.size(); i++)
			cout << i << ". " << setw(30) << _habilities[i]->name() << _habilities[i]->getMana() << setw(15) << " MP" << _habilities[i]->description() << endl;

		cout << "Choose a spell to cast (Enter to skip turn): \n";
	}

	else
	{
		if (getSavingFailures() < 3)
			cout << "This character is at the death gates. \n";

		else
			cout << "This character is dead. \n"
			<< endl;
	}
}

void Hero::savingDeathThrow()
{
	if (getSavingFailures() < 3)
	{
		bool saveThrow = 10 < throwDice(1, 20, false);

		if (saveThrow && getSavingSuccess() < 3)
			savingSuccess++;

		else if (!saveThrow && getSavingFailures() < 3)
			savingFailure++;

		string mess = saveThrow ? "Successful throw\n" : "Failed throw\n";
		cout << "Saving throw from death: " << mess << endl;

		if (getSavingSuccess() >= 3)
		{
			recieveHealing(1);
		}
	}
}

void Hero::recieveHealing(int healing)
{
	Character::recieveHealing(healing);
	resetThrows();
}

void Hero::resetThrows()
{
	savingFailure = 0;
	savingSuccess = 0;
}

void Hero::manageInput(CombatManager* cm, int input)
{
	if (!isDead())
	{
		if (input >= _habilities.size())
			cout << "Use a valid index please:\n";
		else if (_habilities[input]->getMana() > _sheet->manaPoints())
			cout << "Not enough mana, try again:\n";
		else
		{
			cm->castHability(_habilities[input]);
			//_sheet->setManaPoints(_sheet->manaPoints() - _habilities[spell]->getMana());
		}
	}

	else
	{
		savingDeathThrow();
		cm->changeState(END_TURN);
	}

}

#pragma endregion

#pragma region ENEMY

void Enemy::loadFromJson(jute::jValue v, int t)
{

	// Buscamos las stats en el json dentro de nuestro heroe "t" y asignamos un valor aleatorio entre los valores dados
	for (int i = 0; i < _LastStatId_; i++)
	{
		_sheet->setStat(i, v["Characters"][t]["Stats"][i]["Value"].as_int());
	}

	_sheet->name = v["Characters"][t]["Name"].as_string();

	description = v["Characters"][t]["Description"].as_string();

	// Igual con la vida y el mana
	int hp = v["Characters"][t]["HitPoints"].as_int();
	int mp = v["Characters"][t]["ManaPoints"].as_int();

	exp = v["Characters"][t]["Experience"].as_int();
	coins = v["Characters"][t]["Coins"].as_int();

	_sheet->setHitPoints(hp);
	_sheet->setMaxHitPoints(hp);
	_sheet->setManaPoints(mp);
	_sheet->setMaxManaPoints(mp);

	// Guardamos las debilidades en un vector para luego inicializarlas
	vector<float> weak = vector<float>();
	for (int i = 0; i < _LastTypeId_; i++)
	{
		weak.push_back((float)v["Characters"][t]["Weaknesses"][i]["Value"].as_double());
	}

	_sheet->weaknesses = Weaknesses(weak);
}

void Enemy::manageTurn(CombatManager* cm)
{
	cout << "AQUI EL ENEMIGO HACE COSAS" << endl;
	cm->changeState(END_TURN);
}

#pragma endregion