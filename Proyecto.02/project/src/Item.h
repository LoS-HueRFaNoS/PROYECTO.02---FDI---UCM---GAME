#include "Component.h"
#include "jute.h"
#include "RPGLogic.h"
#pragma once

const int PRICE_OF_POTION = 5;

enum PotionType {
	HEALTH,
	MANA
};

enum ItemType
{
	WEAPON,
	ARMOR,
	RUNE
};

class Item
{
protected:

	int sellValue = 0;
	int buyValue = 0;

	std::string _name = "DefaultName";
	std::string _description = "DefaultDescription";

	ItemType _ItemType = ItemType(0);

public:

	Item() {};
	~Item() {};

	int getSellValue() { return sellValue; }
	int getBuyValue() { return buyValue; }
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

//class Runes : public Item
//{
//public:
//
//	Runes() {
//		_name = "Runas";
//		_description = "Objeto intercambiable por objetos";
//		sellValue = NULL;
//		buyValue = NULL;
//		equipanble_ = false;
//		_ItemType = RUNE;
//	}
//};
//
class Chest
{
private:
	ItemType item;
	int itemId;
	int manaPotions;
	int healthPotions;
	int gold; 
public:
	Chest(ItemType it, int value) : item(it), itemId(value) {}
	ItemType getType() { return item; }
	int getIdValue() { return itemId; }

};