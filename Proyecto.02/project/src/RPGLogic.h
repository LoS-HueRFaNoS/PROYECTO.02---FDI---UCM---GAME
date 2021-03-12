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


	enum modStat {
		STR,
		DEX,
		CON,
		INT,
		NULLMOD,
		// Escribir encima de estecomentario
		_LastModId_
	};

	enum characterTemplate {
		WARRIOR,
		WIZARD,
		RANGER,
		BARD,
		CLERIC,
		// Escribir encima de estecomentario
		_LastTemplateId_
	};

	enum mainStat {
		STRENGTH,
		CONSTITUTION,
		DEXTERITY,
		INTELLIGENCE,
		// Escribir encima de estecomentario
		_LastStatId_
	};
}