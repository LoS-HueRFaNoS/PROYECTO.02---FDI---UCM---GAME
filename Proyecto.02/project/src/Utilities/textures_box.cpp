#include "textures_box.h"
#include "../Managers/game/CombatManager.h"
#include "../Managers/game/PartyManager.h"
#include "../Managers/TheElementalMaze.h"

//----------------------------------------------------------------------------

src::txtID textures_box::getCharacterTxt(Character* character)
{
	src::txtID id = src::txtID();

	charTy type = character->getType();

	if (type == charTy::HERO) id = getHeroTxt(static_cast<Hero*>(character));
	else if (type == charTy::ENEMY) id = getEnemyTxt(static_cast<Enemy*>(character));

	return id;
}

src::txtID textures_box::getCharacterTxt(string name)
{
	src::txtID id = src::txtID();
	if  (name =="Warrior")	id = Resources::TextureId::Guerrero;
	else if (name == "Wizard") id = Resources::TextureId::Brujo;
	else if (name == "Ranger") id = Resources::TextureId::Explorador;
	else if (name == "Bard") id = Resources::TextureId::Bardo;
	else if (name == "Cleric") id = Resources::TextureId::Clerigo;
	else if (name == "Paladin") id = Resources::TextureId::Paladin;
	else if (name == "Barbarian") id = Resources::TextureId::Barbaro;
	else if (name == "Rogue") id = Resources::TextureId::Picaro;
	else if (name == "Druid") id = Resources::TextureId::Druida;
	else if (name == "Bestia") id = Resources::TextureId::Bestia;
	else if (name == "GranArchimago") id = Resources::TextureId::GranArchimago;
	else if (name == "Goblin") id = Resources::TextureId::Goblin;
	else if (name == "Pixie") id = Resources::TextureId::Pixie;
	else if (name == "Zombie") id = Resources::TextureId::Zombie;
	else if (name == "Skeleton") id = Resources::TextureId::Skeleton;
	else if (name == "Specter") id = Resources::TextureId::Specter;
	else if (name == "Troll") id = Resources::TextureId::Troll;
	else if (name == "Hellhound") id = Resources::TextureId::Hellhound;
	else if (name == "Mimic") id = Resources::TextureId::Mimic;
	else if (name == "Ghoul") id = Resources::TextureId::Ghoul;
	else if (name == "Giant worm") id = Resources::TextureId::GiantWorm;
	else if (name == "Banshee") id = Resources::TextureId::Banshee;
	else if (name == "DeathKnight") id = Resources::TextureId::DeathKnight;
	else if (name == "Dracolich") id = Resources::TextureId::Dracolich;
	else if (name == "Lich") id = Resources::TextureId::Lich;

	return id;
}

//----------------------------------------------------------------------------

src::txtID textures_box::getHeroTxt(Hero* hero)
{
	heroTemplate tem = hero->getTemplate();

	uint pivot = src::_firstHeroRId_;

	src::txtID id = (src::txtID)(pivot + uint(tem) + 1);

	return id;
}

src::txtID textures_box::getHeroTxt(uint number, bool combat)
{
	std::vector<Hero*> heroes = combat ? 
		TheElementalMaze::instance()->getCombatManager()->getHeroesTeam(): 
		TheElementalMaze::instance()->getPartyManager()->getHeroes();

	return getHeroTxt(heroes[number]);
}

//----------------------------------------------------------------------------

src::txtID textures_box::getEnemyTxt(Enemy* enemy)
{
	enemyTemplate tem = enemy->getTemplate();
	
	uint pivot = src::_firstEnemyId_;

	src::txtID id = (src::txtID)(pivot + uint(tem) + 1);

	return id;
}

src::txtID textures_box::getEnemyTxt(uint number)
{
	CombatManager* c = TheElementalMaze::instance()->getCombatManager();
	std::vector<Enemy*> enemies = c->getEnemiesTeam();

	return getEnemyTxt(enemies[number]);
}

//----------------------------------------------------------------------------

src::txtID textures_box::getEnemyIconTxt(Enemy* enemy)
{
	return src::txtID();
}

src::txtID textures_box::getEnemyIconTxt(uint number)
{
	return src::txtID();
}

//----------------------------------------------------------------------------

src::txtID textures_box::getItemTxt(Item* item)
{
	src::txtID id = src::txtID();

	ItemType itemType = item->getItemType();

	if (itemType == ItemType::ARMOR) {
		Armor* armor = static_cast<Armor*>(item);
		id = getArmorTxt(armor);
	}

	else if (itemType == ItemType::WEAPON) {
		Weapon* weapon = static_cast<Weapon*>(item);
		id = getWeaponTxt(weapon);
	}

	return id;
}

src::txtID textures_box::getItemTxt(uint number)
{
	PartyManager* c = TheElementalMaze::instance()->getPartyManager();
	std::vector<Item*> items = c->getItems();

	return getItemTxt(items[number]);
}

//----------------------------------------------------------------------------

src::txtID textures_box::getWeaponTxt(Weapon* weapon)
{
	rpgLogic::weaponId wId = weapon->getWeaponId();

	uint pivot = src::_firstWeaponId_;

	return (src::txtID)(pivot + uint(wId) + 1);
}

src::txtID textures_box::getArmorTxt(Armor* armor)
{
	rpgLogic::armorId aId = armor->getArmorId();

	uint pivot = src::_firstArmorId_;

	return (src::txtID)(pivot + uint(aId) + 1);
}

//----------------------------------------------------------------------------

src::txtID textures_box::getHabilityTxt(Hero* hero, uint number)
{
	std::vector<Hability*> habilities = hero->getHabilities();

	return getHabilityTxt(habilities[number]);
}

src::txtID textures_box::getHabilityTxt(uint hero, uint number)
{
	PartyManager* c = TheElementalMaze::instance()->getPartyManager();
	std::vector<Hero*> heroes = c->getHeroes();

	return getHabilityTxt(heroes[hero], number);
}

src::txtID textures_box::getHabilityTxt(Hability* hability)
{
	uint pivot = src::_firstSkillId_;

	Hability_Id idHability = hability->getID();

	return (src::txtID)(pivot + size_t(idHability) + 1);
}

//----------------------------------------------------------------------------
