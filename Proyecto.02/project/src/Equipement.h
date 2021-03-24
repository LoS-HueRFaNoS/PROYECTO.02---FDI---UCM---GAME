#include "Entity.h"
#include "HabilityResources.h"
#pragma once

class Equipement : public Component
{
	struct Weapon
	{
		string name = "Default";
		damageType _damageType;
		bool marcial;
		int damage;
		int diceNumber;
	};

	struct Armor
	{
		string name = "Default";
	};

protected:

	virtual void loadFromJson(string json, int t) {}

public:

	void loadWeaponTemplate(weaponsId t);
	void loadArmorTemplate(weaponsId t);

	int getDamage(int danyo) {
		return danyo;
	}
};

