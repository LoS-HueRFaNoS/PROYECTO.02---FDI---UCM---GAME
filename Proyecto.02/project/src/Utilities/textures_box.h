#pragma once
#include "../Templates/Resources.h"
#include "../GameObjects/Character.h"
#include "../Structures/Item.h"

typedef unsigned int uint;

namespace textures_box {
	// characters
	src::txtID getCharacterTxt(Character* character);
	// heroes
	src::txtID getHeroTxt(Hero* hero);
	src::txtID getHeroTxt(uint number);
	// enemigos
	src::txtID getEnemyTxt(Enemy* enemy);
	src::txtID getEnemyTxt(uint number);
	// iconos enemigos
	src::txtID getEnemyIconTxt(Enemy* enemy);
	src::txtID getEnemyIconTxt(uint number);
	// iconos items
	src::txtID getItemTxt(Item* item);
	src::txtID getItemTxt(uint number);
	// armas y armaduras
	src::txtID getWeaponTxt(Weapon* weapon);
	src::txtID getArmorTxt(Armor* armor);
	// iconos habilidades
	src::txtID getHabilityTxt(Hero* hero, uint number);
	src::txtID getHabilityTxt(uint hero, uint number);
	src::txtID getHabilityTxt(Hability* hability);
};