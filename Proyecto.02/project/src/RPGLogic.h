#pragma once

#include <vector>
#include <string>
#include "jute.h"

namespace rpgLogic {

	enum characterType {
		HERO,
		ENEMY
	};

	enum damageType {
		// Da�os f�sicos
		BLUNT,
		PIERCE,
		SLASH,
		// Da�os Elementales
		FIRE,
		WATER,
		ICE,
		EARTH,
		WIND,
		LIGHT,
		DARK,
		_LastTypeId_
	};


	enum mainStat {
		STR, // fuerza = strength
		CON, // constitucion
		DEX, // detreza = dexterity
		INT, // inteligencia = intelect
		_LastStatId_
	};

	enum heroTemplate {
		WARRIOR,
		WIZARD,
		RANGER,
		BARD,
		CLERIC,
		PALADIN,
		BARBARIAN,
		ROGUE,
		DRUID,
		_LastheroTemplateId_
	};

	enum weaponId
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
		_LastWeaponId_
	};

	enum armorId
	{
		ACOLCHADA,
		CUEROTACHONADO,
		COTADEESCAMAS,
		CORAZA,
		SEMIPLACAS,
		COTADEMALLA,
		BANDAS,
		PLACAS,
		_LastArmorId_
	};

	enum enemyTemplate {
		//Nivel 0
		GOBLIN,
		PIXIE,
		//Nivel 1
		ZOMBIE,
		SKELETON,
		SPECTER,
		TROLL,
		//Nivel 2
		HELLHOUND,
		MIMIC,
		GHOUL,
		GIANTWORM,
		BANSHEE,
		LICH,
		NECROFAGO,
		MONSTER,
		DESCONOCIDO,
		//Minibosses
		DEATHKNIGHT, 
		DRACOLICH, 
		// Escribir encima de estecomentario
		_LastEnemyTemplateId_
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
			_weaknesses = std::vector<float>(_LastTypeId_, 0);
		}

		Weaknesses(std::vector<float> in) {
			_weaknesses = in;
		}

		void setWeakness(damageType type, float set) {
			_weaknesses[type] = set;
		}

		void changeWeakness(damageType type, float change) {
			_weaknesses[type] += change;
		}

		float getWeakness(damageType type) {	// Devolver la resistencia en funci�n de tipo o parametro
			return _weaknesses[type];
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