#pragma once

#include "Item.h"
#include "jute.h"

class ItemManager {
public:
	ItemManager() {
		init();
	}

	Weapon* giveWeaponFromId(weaponId id) {
		Weapon* _weapon = new Weapon();
		_weapon->loadWeaponTemplate(weaponJson,id);
		return _weapon;
	};

	Weapon* giveRandomWeapon() {
		Weapon* _weapon = new Weapon();
		_weapon->loadWeaponTemplate(weaponJson,getRandomWeapon());
		return _weapon;
	};

	Armor* giveArmorFromId(armorId id) {
		Armor* _armor = new Armor();
		_armor->loadArmorTemplate(armorJson,id);
		return _armor;
	};

	Armor* giveRandomArmor() {
		Armor* _armor = new Armor();
		_armor->loadArmorTemplate(armorJson,getRandomArmor());
		return _armor;
	};

private:

	void init();

	void loadJson(string json, jute::jValue& j);

	jute::jValue weaponJson;
	jute::jValue armorJson;
};
