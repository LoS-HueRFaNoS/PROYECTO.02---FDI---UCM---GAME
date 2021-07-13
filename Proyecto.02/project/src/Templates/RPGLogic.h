#pragma once

#include <vector>
#include <string>
#include "../Utilities/jute.h"

namespace rpgLogic {

	enum class characterType {
		HERO,
		ENEMY
	}; using charTy = characterType;

	enum class damageType {
		// Daños físicos
		BLUNT,
		PIERCE,
		SLASH,
		// Daños Elementales
		FIRE,
		WATER,
		ICE,
		EARTH,
		WIND,
		LIGHT,
		DARK,
		_lastDamageTypeId_
	}; using damTy = damageType;

	enum class mainStat {
		STR, // fuerza = strength
		CON, // constitucion
		DEX, // detreza = dexterity
		INT, // inteligencia = intelect
		_lastStatId_
	}; using ms = mainStat;

	enum class heroTemplate {
		WARRIOR,
		WIZARD,
		RANGER,
		BARD,
		CLERIC,
		PALADIN,
		BARBARIAN,
		ROGUE,
		DRUID,
		_lastHeroTemplateId_
	}; using heroTem = heroTemplate;

	enum class weaponId
	{
		DESARMADO,
		BASTON,
		DAGA,
		CLAVA,
		HACHAPEQUENA,
		HOZ,
		LANZA,
		MARTILLOPEQUENO,
		MAZA,
		ARCOPEQUENO,
		BALLESTALIGERA,
		//Armas Marciales
		ALABARDA,
		ATARRAGA,
		ESPADACORTA,
		ESPADALARGA,
		ESPADON,
		ESPADAROPERA,
		HACHADEBATALLA,
		GUJA,
		LATIGO,
		LUCERODELALBA,
		MARTILLODEGUERRA,
		PICA,
		TRIDENTE,
		ARCOLARGO,
		BALLESTAPESADA,
		_lastWeaponId_
	}; using wID = weaponId;

	enum class armorId
	{
		ACOLCHADA,
		CUEROTACHONADO,
		COTADEESCAMAS,
		CORAZA,
		SEMIPLACAS,
		COTADEMALLA,
		BANDAS,
		PLACAS,
		_lastArmorId_
	}; using aID = armorId;

	enum class enemyTemplate {
		//Nivel 0
		GOBLIN,
		PIXIE,
		ZOMBIE,
		//Nivel 1
		SKELETON,
		SPECTER,
		TROLL,
		//Nivel 2
		HELLHOUND,
		MIMIC,
		GHOUL,
		GIANTWORM,
		BANSHEE,
		//Minibosses
		DEATHKNIGHT, 
		DRACOLICH, 
		//Boss
		LICH,
		// Escribir encima de estecomentario
		_lastEnemyTemplateId_
	}; using eTem = enemyTemplate;

	static std::string toString(enemyTemplate type)
	{ 
		switch (type)
		{
		case rpgLogic::enemyTemplate::GOBLIN:
			return "GOBLIN";
			break;
		case rpgLogic::enemyTemplate::PIXIE:
			return "PIXIE";
			break;
		case rpgLogic::enemyTemplate::ZOMBIE:
			return "ZOMBIE";
			break;
		case rpgLogic::enemyTemplate::SKELETON:
			return "SKELETON";
			break;
		case rpgLogic::enemyTemplate::SPECTER:
			return "SPECTER";
			break;
		case rpgLogic::enemyTemplate::TROLL:
			return "TROLL";
			break;
		case rpgLogic::enemyTemplate::HELLHOUND:
			return "HELLHOUND";
			break;
		case rpgLogic::enemyTemplate::MIMIC:
			return "MIMIC";
			break;
		case rpgLogic::enemyTemplate::GHOUL:
			return "GHOUL";
			break;
		case rpgLogic::enemyTemplate::GIANTWORM:
			return "GIANTWORM";
			break;
		case rpgLogic::enemyTemplate::BANSHEE:
			return "BANSHEE";
			break;
		case rpgLogic::enemyTemplate::DEATHKNIGHT:
			return "DEATHKNIGHT";
			break;
		case rpgLogic::enemyTemplate::DRACOLICH:
			return "DRACOLICH";
			break;
		case rpgLogic::enemyTemplate::_lastEnemyTemplateId_:
			return "_lastEnemyTemplateId_";
			break;
		default:
			return "NULL";
			break;
		}
	};

	struct  Stat
	{
		Stat(int v) {
			value = v;
		}
		int value;

		int getMod() {
			return (value - 10) / 2;
		}
	};


	struct Weaknesses {

		std::vector<float> _weaknesses;

		Weaknesses() {
			_weaknesses = std::vector<float>(size_t(damTy::_lastDamageTypeId_), 0);
		}

		Weaknesses(std::vector<float> in) {
			_weaknesses = in;
		}

		void setWeakness(damageType type, float set) {
			_weaknesses[size_t(type)] = set;
		}

		void changeWeakness(damageType type, float change) {
			_weaknesses[size_t(type)] += change;
		}

		float getWeakness(damageType type) {	// Devolver la resistencia en función de tipo o parametro
			return _weaknesses[size_t(type)];
		}
	};

	/*enum SpellId {
		Fireball,
		_LastSpellId_
	};*/

	int throwDice(int n, int dice, bool text = false);

	enemyTemplate getRandomEnemy();

	heroTemplate getRandomHero();

	weaponId getRandomWeapon();

	armorId getRandomArmor();

}