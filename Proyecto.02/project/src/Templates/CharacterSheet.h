#ifndef _CHARACTER_SHEET_
#define _CHARACTER_SHEET_
#include "RPGLogic.h"
#include "../Utilities/checkML.h"


class CharacterSheet
{
private:

	//Caracteristicas 
	std::vector<rpgLogic::Stat> _stats;

	//Salud
	int _hitPoints = 10;
	int _maxHitPoints = 10;
	//Mana
	int _manaPoints = 10;
	int _maxManaPoints = 10;

	std::string getResName(rpgLogic::damageType type);

public:

	//Debilidades
	rpgLogic::Weaknesses weaknesses;

	//Nombre del personaje ( o enemigo)
	std::string name = "DefaultClass";

	CharacterSheet():
		weaknesses(), 
		_stats(std::vector<rpgLogic::Stat>(4, { 10 }))
	{
	}

	~CharacterSheet(){}

	rpgLogic::Stat getStat(rpgLogic::mainStat st) {
		return (_stats[size_t(st)].value <= 0) ? rpgLogic::Stat(1) : _stats[size_t(st)];
	}

	float getResistance(rpgLogic::damageType type) {
		return weaknesses.getWeakness(type);
	}

	void setStat(rpgLogic::mainStat st, int set) {
		_stats[size_t(st)].value = set;
	}

	void setStat(int st, int set) {
		_stats[size_t(st)].value = set;
	}

	int getStatValue(int st)
	{
		return _stats[size_t(st)].value;
	}

	int maxHitPoints() {
		return _maxHitPoints;
	}

	int maxManaPoints() {
		return _maxManaPoints;
	}

	int hitPoints() {
		return _hitPoints;
	}

	int manaPoints() {
		return _manaPoints;
	}

	void setMaxHitPoints(int set) {
		_maxHitPoints = set;
	}

	void setMaxManaPoints(int set) {
		_maxManaPoints = set;
	}

	void setHitPoints(int set) {
		_hitPoints = set;
	}

	void setManaPoints(int set) {
		_manaPoints = set;
	}

	void changeStat(rpgLogic::mainStat st, int change) {
		_stats[size_t(st)].value += change;
	}

	bool recieveDamage(int damage, rpgLogic::damageType type);

	void recieveHealing(int healing);

	void recieveMana(int mana);

	//void recieveBuff(int buff,mainStat st);
};
#endif