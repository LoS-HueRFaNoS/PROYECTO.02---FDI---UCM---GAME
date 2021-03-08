#ifndef _RPG_LOGIC
#define _RPG_LOGIC

class RpgLogic {
public:
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
	DARK
	};

	enum modStat{
		STR,
		DEX,
		CON,
		INT,
		NULLMOD
	};
};


#endif // !