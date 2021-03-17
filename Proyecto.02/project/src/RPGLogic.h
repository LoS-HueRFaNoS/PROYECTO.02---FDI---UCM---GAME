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
		CON,
		DEX,
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

	enum mainStat {
		STRENGTH,
		CONSTITUTION,
		DEXTERITY,
		INTELLIGENCE,
		// Escribir encima de estecomentario
		_LastStatId_
	};
}


class Hability {
private:
	int _mana;
	int _cd;
	int _nextCast;

	bool canCast() { return !_nextCast; }
public:
	void pastTurn() { if (_nextCast > 0) _nextCast--; }
	int getCD() { return _cd; }
	int nextCast() { return _nextCast; }
	virtual void castHability() = 0;
};