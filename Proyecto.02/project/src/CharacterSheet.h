#ifndef _CHARACTER_SHEET_
#define _CHARACTER_SHEET_
#include "Component.h"
#include "RPGLogic.h"

using namespace rpgLogic;

class CharacterSheet : public Component
{
public:

	struct  Stat
	{
		int value;

		int getMod() {
			return (value - 10) / 2;
		}
	};

	struct Weaknesses {

		vector<float> _weaknesses;

		Weaknesses() {
			_weaknesses = vector<float>(_LastTypeId_, 0);
		}

		Weaknesses(vector<float> in) {
			_weaknesses = in;
		}

		void setWeakness(damageType type, float set) {
			_weaknesses[type] = set;
		}

		void changeWeakness(damageType type, float change) {
			_weaknesses[type] += change;
		}

		float getWeakness(damageType type) {	// Devolver la resistencia en función de tipo o parametro
			return _weaknesses[type];
		}
	};

private:

	//Nombre (Clase del heroe o tipo de criatura) 
	string name = "DefaultClass";

	//Caracteristicas 
	vector<Stat> _stats;

	//Salud
	int hitPoints = 10;
	//Mana
	int manaPoints = 10;

	//Debilidades
	Weaknesses weaknesses;

	void loadFromJson(string json, int t);

public:

	CharacterSheet() :Component(ecs::CharacterSheet),
		weaknesses(), _stats(vector<Stat>(4, { 10 }))
	{
	}

	~CharacterSheet(){}

	void loadFromJson(characterTemplate t);
	void loadFromJson(enemyTemplate t);

	Stat getStat(mainStat st) {
		return _stats[st];
	}

	void changeStat(mainStat st, int change) {
		_stats[st].value += change;
	}

	bool recieveDamage(int damage, rpgLogic::damageType type);
	

};
#endif