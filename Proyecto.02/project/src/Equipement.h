#ifndef _EQUIPEMENT_
#define _EQUIPEMENT_
#include "Component.h"
#include "HabilityResources.h"

class Equipement : public Component
{
public:
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

	Equipement() : Component(ecs::Equipement)
	{}

	~Equipement(){}

	void loadWeaponTemplate(weaponsId t);
	void loadArmorTemplate(weaponsId t);

	int getDamage(int danyo) {
		return danyo;
	}
};

#endif // !