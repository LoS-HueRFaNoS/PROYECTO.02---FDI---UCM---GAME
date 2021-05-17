#include <fstream>
#include <iostream>
#include "Character.h"
#include "../Managers/game/CombatManager.h"
#include "../Managers/game/ItemManager.h"
#include "../Managers/TheElementalMaze.h"

using namespace rpgLogic;

#pragma region CHARACTER

Character::~Character()
{
	delete _sheet;
	_sheet = nullptr;
	for (Hability* h : _habilities)
	{
		delete h;
		h = nullptr;
	}
	delete lightAttack_;
	lightAttack_ = nullptr;
	delete heavyAttack_;
	heavyAttack_ = nullptr;
	removeConditions();
	delete _weapon;
	_weapon = nullptr;
}

void Character::startTurn(CombatManager* cm)
{

	// Manejar estados y cambios que ocurren al pasar de turnos
	cout << name() << " TURN" << endl;

	for (std::vector<Condition*>::iterator it = _conditions.begin(); it != _conditions.end();)
	{
		if (!(*it)->onTurnStarted())
		{
			Condition* temp = (*it);
			removeCondition((*it)->getID());
			it = _conditions.erase(it);
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
	for (std::vector<Condition*>::iterator it = _conditions.begin(); it != _conditions.end();)
	{
		if (!(*it)->onTurnEnd())
		{
			Condition* temp = (*it);
			removeCondition((*it)->getID());
			it = _conditions.erase(it);
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
	loadFromJson(v, int(t));
}

void Character::loadFromTemplate(jute::jValue v, enemyTemplate t)
{
	loadFromJson(v, int(t));
}

void Character::recieveDamage(int damage, rpgLogic::damageType type, Character* attacker)
{
	for (std::vector<Condition*>::iterator it = _conditions.begin(); it != _conditions.end();)
	{
		if (!(*it)->onAttackRecieved(damage, attacker))
		{
			Condition* temp = (*it);
			removeCondition((*it)->getID());
			it = _conditions.erase(it);
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
		for (std::vector<Condition*>::iterator it = _conditions.begin(); it != _conditions.end();)
		{
			if (!(*it)->onDeath(attacker))
			{
				Condition* temp = (*it);
				removeCondition((*it)->getID());
				it = _conditions.erase(it);
				delete temp;
			}
			else
			{
				it++;
			}
		}
		removeConditions();
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
	return hit > throwStat(ms::DEX);
}

void Character::removeConditions()
{
	for (Condition* c : _conditions)
	{
		delete c;
		c = nullptr;
	}
	_conditions.clear();
}

void Character::removeGoodConditions()
{
	for (auto it = _conditions.begin(); it != _conditions.end();)
	{
		if ((*it)->isPositive())
			it = _conditions.erase(it);
		else
			it++;
	}
}

void Character::removeBadConditions()
{
	for (auto it = _conditions.begin(); it != _conditions.end();)
	{
		if (!(*it)->isPositive())
			it = _conditions.erase(it);
		else
			it++;
	}
}

#pragma endregion

#pragma region HERO

Hero::~Hero()
{
	delete _armor;
	_armor = nullptr;
}

void Hero::loadFromJson(jute::jValue v, int t)
{
	template_ = (heroTemplate)t;

	// Buscamos las stats en el json dentro de nuestro heroe "t" y asignamos un valor aleatorio entre los valores dados
	for (int i = 0; i < size_t(ms::_lastStatId_); i++)
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
	for (int i = 0; i < size_t(damTy::_lastDamageTypeId_); i++)
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

	int size = v["Characters"][t]["ListHabilities"].size();

	for (int i = 0; i < size; i++)
	{
		int h = v["Characters"][t]["ListHabilities"][i].as_int();
		addHability((Hability_Id)h);
	}
}

void Hero::endCombat(int exp)
{
	if (!_deathGate)
	{
		recieveHealing(2);
		levelUp(exp);
	}
}

#include <iomanip>

void Hero::showSpellList()
{

	cout << "\nSpells: " << endl;

	for (int i = 0; i < _habilities.size(); i++)
		cout << i << ". " << setw(30) << _habilities[i]->name() << _habilities[i]->getMana() << setw(15) << " MP" << _habilities[i]->description() << endl;

	cout << "Choose a spell to cast (Enter to skip turn): \n";
}

void Hero::killHero()
{
	_deathGate = true;
}


void Hero::manageTurn(CombatManager* cm)
{
	if (isDead()) {
		cout << "This character is at the death gates. \n";
		savingDeathThrow();
		cm->changeState(END_TURN);
	}
}


void Hero::savingDeathThrow()
{
	if (getSavingFailures() < 3)
	{
		bool saveThrow = 10 < throwDice(1, 20, false);

		if (saveThrow)
			savingSuccess++;

		else
			savingFailure++;

		string mess = saveThrow ? "Successful throw\n" : "Failed throw\n";
		cout << "Saving throw from death: " << mess << endl;

		if (getSavingSuccess() >= 3) {
			cout << name() << " is no longer at the death gates.\n";
			recieveHealing(1);
		}
		else if (getSavingFailures() >= 3) {
			cout << name() << " is dead. \n";
			_deathGate = true;
		}
	}
}

void Hero::recieveHealing(int healing)
{
	Character::recieveHealing(healing);
	resetThrows();
}

void Hero::recieveMana(int mana)
{
	_sheet->recieveMana(mana);
}

void Hero::resetThrows()
{
	savingFailure = 0;
	savingSuccess = 0;
}

void Hero::levelUp(int exp)
{
	int expObtain = exp;

	if (expNeed - expObtain <= 0)
	{
		expMax += 100;

		level++;

		if (level % 4 == 0)
			pointsPerLevel += 4;

		int hp = _sheet->maxHitPoints();
		int pm = _sheet->maxManaPoints();

		int hpMax, pmMax;

		if (getMod(ms::CON) >= 0)
			hpMax = hp + throwStat(ms::CON) + getMod(ms::CON);

		else
			hpMax = hp + throwDice(1, 10, false);

		if (getMod(ms::INT) >= 0)
			pmMax = pm + throwStat(ms::INT) + getMod(ms::INT);

		else
			pmMax = pm + throwDice(1, 10, false);

		_sheet->setMaxHitPoints(hpMax);
		_sheet->setHitPoints(hpMax);
		_sheet->setMaxManaPoints(pmMax);
		_sheet->setManaPoints(pmMax);

		expNeed = expMax;
	}

	else
		expNeed -= expObtain;
}

void Hero::changeHeroStat(rpgLogic::mainStat stat)
{
	if (pointsPerLevel > 0)
	{
		_sheet->changeStat(stat, 1);
		pointsPerLevel--;
	}
}

void Hero::manageInput(CombatManager* cm, int input)
{
	if (input < 0) {
		if (input == -2)
			cm->castHability(lightAttack_);
		else if (input == -3)
			cm->castHability(heavyAttack_);
		return;
	}
	else if (input >= _habilities.size())
		cout << "Use a valid index please:\n";
	else if (_habilities[input]->getMana() > _sheet->manaPoints())
		cout << "Not enough mana, try again:\n";
	else
	{
		cm->castHability(_habilities[input]);
		_sheet->setManaPoints(_sheet->manaPoints() - _habilities[input]->getMana());
	}
}

#pragma endregion

#pragma region ENEMY

void Enemy::loadFromJson(jute::jValue v, int t)
{

	template_ = (enemyTemplate)t;

	// Buscamos las stats en el json dentro de nuestro heroe "t" y asignamos un valor aleatorio entre los valores dados
	for (int i = 0; i < size_t(ms::_lastStatId_); i++)
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
	for (int i = 0; i < size_t(damTy::_lastDamageTypeId_); i++)
	{
		weak.push_back((float)v["Characters"][t]["Weaknesses"][i]["Value"].as_double());
	}

	for (int i = 0; i < v["Characters"][t]["ListHabilities"].size(); i++)
	{
		int h = v["Characters"][t]["ListHabilities"][i].as_int();
		addHability((Hability_Id)h);
	}

	_sheet->weaknesses = Weaknesses(weak);

	_weapon = TheElementalMaze::instance()->getItemManager()->getWeaponFromId(wID::DESARMADO);
}

void Enemy::manageTurn(CombatManager* cm)
{
	int aux = game_->getRandGen()->nextInt(0, int(_habilities.size()));

	Hability* hab = _habilities[aux];

	if (hab->getObjectiveType() == objTy::ENEMYTEAM || hab->getObjectiveType() == objTy::ALLYTEAM
		|| hab->getObjectiveType() == objTy::CASTER)
		cm->castHability(hab);

	else
	{
		if (hab->getObjectiveType() == objTy::SINGLEENEMY)
		{
			vector <Hero*> heroTeam = cm->getHeroesTeam();

			while (true)
			{
				int heroe = game_->getRandGen()->nextInt(0, int(heroTeam.size()));

				if (!heroTeam[heroe]->isDead())
				{
					cm->throwHability(heroTeam[heroe], hab);
					break;
				}
			}
		}

		else
		{
			vector <Enemy*> enemyTeam = cm->getEnemiesTeam();

			while (true)
			{
				int enemigo = game_->getRandGen()->nextInt(0, int(enemyTeam.size()));

				if (!enemyTeam[enemigo]->isDead())
				{
					cm->throwHability(enemyTeam[enemigo], hab);
					break;
				}
			}
		}
	}


	cm->changeState(END_TURN);
}

#pragma endregion