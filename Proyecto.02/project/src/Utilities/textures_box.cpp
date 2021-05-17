#include "textures_box.h"
#include "../Managers/game/CombatManager.h"
#include "../Managers/game/PartyManager.h"
#include "../Managers/TheElementalMaze.h"
using src = Resources;

Resources::TextureId textures_box::getHeroTxt(uint number)
{
	PartyManager* c = TheElementalMaze::instance()->getPartyManager();
	std::vector<Hero*> heroes = c->getHeroes();

	heroTemplate tem = heroes[number]->getTemplate();

	uint pivot = src::_firstHeroRId_;

	Resources::TextureId id = (Resources::TextureId)(pivot + uint(tem) + 1);

	return id;
}

Resources::TextureId textures_box::getEnemyTxt(uint number)
{
	CombatManager* c = TheElementalMaze::instance()->getCombatManager();
	std::vector<Enemy*> enemies = c->getEnemiesTeam();

	enemyTemplate tem = enemies[number]->getTemplate();

	uint pivot = src::_firstEnemyId_;

	Resources::TextureId id = (Resources::TextureId)(pivot + uint(tem) + 1);

	return id;
}

Resources::TextureId textures_box::getItemTxt(uint number)
{
	PartyManager* c = TheElementalMaze::instance()->getPartyManager();
	std::vector<Item*> items = c->getItems();

	Resources::TextureId id = Resources::TextureId();

	ItemType itemType = items[number]->getItemType();

	uint pivot;

	if (itemType == ItemType::ARMOR) {
		Armor* armor = static_cast<Armor*>(items[number]);
		rpgLogic::armorId aId = armor->getArmorId();

		pivot = src::_firstArmorId_;

		id = (Resources::TextureId)(pivot + uint(aId) + 1);
	}

	else if (itemType == ItemType::WEAPON) {
		Weapon* weapon = static_cast<Weapon*>(items[number]);
		rpgLogic::weaponId wId = weapon->getWeaponId();

		pivot = src::_firstWeaponId_;

		id = (Resources::TextureId)(pivot + uint(wId) + 1);

	}

	return id;
}

Resources::TextureId textures_box::getHabilityTxt(Hero* hero, uint number)
{
	PartyManager* c = TheElementalMaze::instance()->getPartyManager();
	//std::vector<Hero*> heroes = c->getHeroes();
	std::vector<Hability*> habilities = hero->getHabilities();

	uint pivot = src::_firstSkillId_;

	Hability_Id idHability = habilities[number]->getID();

	Resources::TextureId id = (Resources::TextureId)(pivot + size_t(idHability) + 1);

	return id;
}
