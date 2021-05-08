#include "Component.h"
#include "jute.h"
#include "RPGLogic.h"
#pragma once

enum ItemType
{
	WEAPON,
	ARMOR,
	POTION,
	TREASURE
};

class Item
{
protected:

	int sellValue = 0;
	int buyValue = 0;

	bool equipment;

	std::string _name = "DefaultName";
	std::string _description = "DefaultDescription";

	ItemType _ItemType = ItemType(0);

public:

	Item() {};
	~Item() {};

	int getSellValue() { return sellValue; }
	int getBuyValue() { return buyValue; }
	bool isEquipment() { return equipment; }
	std::string getName() { return _name; }
	std::string getDescription() { return _description; }
	ItemType getItemType() { return _ItemType; }
};

class Weapon : public Item
{
private:

	rpgLogic::damageType _damageType;
	bool marcial;
	int damage;
	int diceNumber;
	int hands;
	rpgLogic::weaponId weapId;
public:

	Weapon() {

		equipment = true;
		_ItemType = WEAPON;
		sellValue = rand() % 100;
		buyValue = rand() % 100;
	}

	int getDamage() { return damage; }

	int getNDice() { return diceNumber; }

	rpgLogic::damageType getDamageType() { return _damageType; }

	bool isMarcial() { return marcial; }

	void loadWeaponTemplate(jute::jValue v, rpgLogic::weaponId t);

	rpgLogic::weaponId getWeaponId() { return weapId; }
};

class Armor : public Item
{
private:

	rpgLogic::mainStat _statNeeded;
	int minStatNeeded;
	rpgLogic::Weaknesses _weaknesses;
	rpgLogic::armorId armId;

public:

	Armor() {
		equipment = true;
		_ItemType = ARMOR;
		sellValue = rand() % 100;
		buyValue = rand() % 100;
	}

	rpgLogic::Weaknesses getWeaknesses() { return _weaknesses; }

	rpgLogic::mainStat getStatNeeded() { return _statNeeded; }

	int getMinStatNeeded() { return minStatNeeded; }

	void loadArmorTemplate(jute::jValue v, rpgLogic::armorId t);

	rpgLogic::armorId getArmorId() { return armId; }
};

class HealthPotion : public Item
{
public:

	HealthPotion() {
		_name = "Pocion de salud";
		_description = "Pocion que te cura 10 puntos de vida";
		sellValue = 10;
		buyValue = 20;
		equipment = false;
		_ItemType = POTION;
	}
};

class ManaPotion : public Item
{
public:

	ManaPotion() {
		_name = "Pocion de mana";
		_description = "Pocion que te cura 8 puntos de mana";
		sellValue = 10;
		buyValue = 20;
		equipment = false;
		_ItemType = POTION;
	}
};

class RevivePotion : public Item
{
public:

	RevivePotion() {
		_name = "Pocion de resurrección";
		_description = "Pocion que revive a un aliado";
		sellValue = 50;
		buyValue = 100;
		equipment = false;
		_ItemType = POTION;
	}
};

class Runes : public Item
{
public:

	Runes() {
		_name = "Runas";
		_description = "Objeto intercambiable por objetos";
		sellValue = NULL;
		buyValue = NULL;
		equipment = false;
		_ItemType = TREASURE;
	}
};






class Chest
{
private:
	ItemType item;
	int itemId;
public:
	Chest(ItemType it, int value) : item(it), itemId(value){}
	ItemType getType() { return item; }
	int getIdValue() { return itemId; }

};
