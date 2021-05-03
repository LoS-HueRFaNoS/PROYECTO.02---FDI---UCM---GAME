#pragma once

#include "Item.h"
#include "jute.h"

class ItemManager {
public:
	ItemManager() {
		init();
	}

	Weapon* getWeaponFromId(rpgLogic::weaponId id) {
		Weapon* _weapon = new Weapon();
		_weapon->loadWeaponTemplate(weaponJson, id);
		return _weapon;
	};

	Weapon* getRandomWeapon() {
		Weapon* _weapon = new Weapon();
		_weapon->loadWeaponTemplate(weaponJson, rpgLogic::getRandomWeapon());
		return _weapon;
	};

	Armor* getArmorFromId(rpgLogic::armorId id) {
		Armor* _armor = new Armor();
		_armor->loadArmorTemplate(armorJson, id);
		return _armor;
	};

	Armor* getRandomArmor() {
		Armor* _armor = new Armor();
		_armor->loadArmorTemplate(armorJson, rpgLogic::getRandomArmor());
		return _armor;
	};

private:

	void init();

	void loadJson(string json, jute::jValue& j);

	jute::jValue weaponJson;
	jute::jValue armorJson;
};
