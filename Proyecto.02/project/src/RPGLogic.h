#pragma once

namespace rpgLogic {
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
		// Escribir encima de estecomentario
		_LastTypeId_
	};


	enum mainStat {
		STR,
		CON,
		DEX,
		INT,
		// Escribir encima de estecomentario
		_LastStatId_
	};

	enum characterTemplate {
		WARRIOR,
		WIZARD,
		RANGER,
		BARD,
		CLERIC,
		PALADIN,
		BARBARIAN,
		ROGUE,
		DRUID,
		// Escribir encima de estecomentario
		_LastCharacterTemplateId_
	};

	enum enemyTemplate {
		ZOMBIE,
		// Escribir encima de estecomentario
		_LastEnemyTemplateId_
	};

	int throwDice(int n, int dice);
}

