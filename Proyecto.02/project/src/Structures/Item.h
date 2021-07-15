#include "../ecs/Component.h"
#include "../Utilities/jute.h"
#include "../Templates/RPGLogic.h"
#include <list>
class ItemManager;
#pragma once

const int PRICE_OF_POTION = 5;

enum PotionType {
	HEALTH,
	MANA
};

enum ItemType
{
	WEAPON,
	ARMOR
};

class Item
{
protected:

	int sellValue = 0;
	int buyValue = 0;

	std::string _name = "DefaultName";
	std::string _description = "DefaultDescription";

	ItemType _ItemType = ItemType(0);
	rpgLogic::Weaknesses _elementalAfinity;

	void elementalAfinity();

public:

	Item() {};
	~Item() {};

	int getSellValue() { return sellValue; }
	int getBuyValue() { return buyValue; }
	std::string getName() { return _name; }
	std::string getDescription() { return _description; }
	ItemType getItemType() { return _ItemType; }
	rpgLogic::Weaknesses getElementalAfinity() { return _elementalAfinity; }
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
		_ItemType = ItemType::WEAPON;
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
	rpgLogic::armorId armId;

public:

	Armor() {
		_ItemType = ItemType::ARMOR;
	}
	rpgLogic::mainStat getStatNeeded() { return _statNeeded; }

	int getMinStatNeeded() { return minStatNeeded; }

	void loadArmorTemplate(jute::jValue v, rpgLogic::armorId t);

	rpgLogic::armorId getArmorId() { return armId; }
};

class Chest
{
private:
	int gold;
	list<Item*> items;
public:
	Chest()
	{
		gold = 100;
	}
	Chest(int gold_, std::list<Item*> items_) : gold(gold_), items(items_) {
		
	};
	list<Item*> getItems() { return items; }
	int getGold() { return gold; }
	void oroRecogido() { gold = 0; }
	void takeItem(Item* item)
	{
		list<Item*>::iterator it = items.begin();
		bool encontrado = false;
		while (it != items.end() && !encontrado)
		{
			if (it._Ptr->_Myval == item) encontrado = true;
			else it++;
		}
		items.erase(it);
	}
};
