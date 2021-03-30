#pragma once

namespace rpgLogic {

	enum characterType {
		HERO,
		ENEMY
	};

	enum damageType {
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
		_LastTypeId_
	};


	enum mainStat {
		STR,
		CON,
		DEX,
		INT,
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

	enum weaponsId
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
		ZOMBIE,
		// Escribir encima de estecomentario
		_LastEnemyTemplateId_
	};

	/*enum SpellId {
		Fireball,
		_LastSpellId_
	};*/

	int throwDice(int n, int dice, bool text);
}

