#pragma once

#include <vector>
#include "RPGLogic.h"
#include <string>
#include <assert.h>

using namespace rpgLogic;

class Character;

#pragma region HABILITY

enum class Hability_Id {
	LIGHTATTACK, //0
	FIREBALL, //1
	BLOODYSTRIKE, //2
	HEALINGWORD, //3
	ALLYTEAMHEALEXAMPLE, //4
	SELFHEALEXAMPLE, //5
	WINDBURST, //6
	WINDSLASH, //7
	ROCKPILLAR, //8
	TOXICSHADOW, //9
	TSUNAMI, //10
	DIVINEPROTECTION, //11
	FLASH, //12
	FREEZE, //13
	WHIRLPOOL, //14
	LIGHTBEAM, //15
	DARKVORTEX, //16
	FIREARROW, //17
	MEDITATE, //18
	LIGHTEN, //19
	STRENGTHEN, //20
	TOUGHEN, //21
	BLOODTHIRST, //22
	SACRIFICE, //23
	DOUBLESHOT, //24
	THROWINGAXES, //25
	MORPH, //26
	REVERSEMORPH, //27
	HEAVYSTRIKE, //28
	SMOKEARROW,	//29
	RAINOFDAGGERS,	//30
	ROCKPROJECTILES, //31
	TRICKSHOT, //32
	GLADIATORBALLAD, //33
	WINDSONG, //34
	DETERMINATION, //35
	BLESSING, //36
	_lastHabilityId_
}; using habID = Hability_Id;

enum class ObjectiveType
{
	SINGLEALLY,
	SINGLEENEMY,
	ALLYTEAM,
	ENEMYTEAM,
	CASTER
}; using objTy = ObjectiveType;

enum class HabilityType {
	ATTACK,
	DEBUFF,
	HEAL,
	BUFF
}; using habTy = HabilityType;

class Hability {
protected:
	int level = 0;
	int _mana = 0;
	std::string _name = "DefaultName";
	std::string _description = "DefaultDescription";

	Hability_Id _id = habID::_lastHabilityId_;
	damageType _damageType = damTy(0);
	mainStat _mod = ms::_lastStatId_;
	ObjectiveType _obj = objTy::CASTER;

	HabilityType _habilityType = habTy::ATTACK;

	Character* _caster;

public:

	virtual Hability_Id getID() {
		return _id;
	}
	static Hability_Id id() { return habID::_lastHabilityId_; }

	Hability() : _caster(nullptr) {}

	Hability(Character* caster) : _caster(caster) {}

	~Hability() {}

	virtual void init() {}

	int getMana() { return _mana; }

	Character* getCaster() { return _caster; }

	virtual void throwHability(Character* obj, bool critical)const = 0;

	std::string name() { return _name; }

	std::string description() { return _description; }

	mainStat getMod() { return _mod; }

	ObjectiveType getObjectiveType() { return _obj; }

	HabilityType getHabilityType() { return _habilityType; }

	void setCaster(Character* caster) {
		_caster = caster;
	}
};

class LightAttack : public Hability {
public:
	LightAttack(Character* caster = nullptr) : Hability(caster) {
		level = 0;
		_mana = 0;
		_name = "Light Attack";
		//_description = "Golpe to guapo con el arma, a terminar";
		_description = "Ataque basico con el arma del heroe";

		_id = habID::LIGHTATTACK;
		_habilityType = habTy::ATTACK;
		_mod = ms::STR;
		_obj = objTy::SINGLEENEMY;
	}

	static Hability_Id id() { return habID::LIGHTATTACK; }

	virtual void throwHability(Character* obj, bool critical)const;
};

class Fireball : public Hability {
public:
	Fireball(Character* caster = nullptr) : Hability(caster) {

		level = 4;
		_mana = 4;
		_name = "Fireball";
		_description = "Bola de fuego to guapa, a hace 8d6 a todos los enemigos frente a salvacion DEX";

		_id = habID::FIREBALL;
		_damageType = damTy::FIRE;
		_habilityType = habTy::ATTACK;
		_mod = ms::INT;
		_obj = objTy::ENEMYTEAM;
	}

	static Hability_Id id() { return habID::FIREBALL; }

	virtual void throwHability(Character* obj, bool critical)const;
};


class BloodyStrike : public Hability {
public:
	BloodyStrike(Character* caster = nullptr) : Hability(caster) {

		level = 0;
		_mana = 0;
		_name = "BloodyStrike";
		//_description = "Esto es un ejemplo, hace 1d5 de daño";
		_description = "Ataque que hace 1d5 de daño a un enemigo y aplica sangrado";

		_id = habID::BLOODYSTRIKE;
		_damageType = damTy::SLASH;
		_habilityType = habTy::ATTACK;
		_mod = ms::INT;
		_obj = objTy::SINGLEENEMY;
	}

	static Hability_Id id() { return habID::BLOODYSTRIKE; }

	virtual void throwHability(Character* obj, bool critical)const;
};



class HealingWord : public Hability {
public:
	HealingWord(Character* caster = nullptr) : Hability(caster) {

		level = 0;
		_mana = 0;
		_name = "HealingWord";
		_description = "Esto es un ejemplo, cura 2d5 de vida a un aliado";

		_id = habID::HEALINGWORD;
		_damageType = damTy::LIGHT;
		_habilityType = habTy::HEAL;
		_mod = ms::INT;
		_obj = objTy::SINGLEALLY;
	}

	static Hability_Id id() { return habID::HEALINGWORD; }

	virtual void throwHability(Character* obj, bool critical)const;
};


class AllyTeamHealExample : public Hability {
public:
	AllyTeamHealExample(Character* caster = nullptr) : Hability(caster) {

		level = 0;
		_mana = 0;
		_name = "AllyTeamHealExample";
		_description = "Esto es un ejemplo, cura a todo tu equipo 1d5";

		_id = habID::ALLYTEAMHEALEXAMPLE;
		_damageType = damTy::LIGHT;
		_habilityType = habTy::HEAL;
		_mod = ms::INT;
		_obj = objTy::ALLYTEAM;
	}

	static Hability_Id id() { return habID::ALLYTEAMHEALEXAMPLE; }

	virtual void throwHability(Character* obj, bool critical)const;
};


class SelfHealExample : public Hability {
public:
	SelfHealExample(Character* caster = nullptr) : Hability(caster) {

		level = 0;
		_mana = 0;
		_name = "SelfHealExample";
		_description = "Esto es un ejemplo, te cura 1d8";

		_id = habID::SELFHEALEXAMPLE;
		_damageType = damTy::LIGHT;
		_habilityType = habTy::HEAL;
		_mod = ms::INT;
		_obj = objTy::CASTER;
	}

	static Hability_Id id() { return habID::SELFHEALEXAMPLE; }

	virtual void throwHability(Character* obj, bool critical)const;
};



class WindBurst : public Hability {
public:
	WindBurst(Character* caster = nullptr) : Hability(caster) {

		level = 4;
		_mana = 3;
		_name = "WindBurst";
		_description = "Sal a que te de el aire, hace 8d6 a todos los enemigos frente a salvacion DEX (reduce DEX)";

		_id = habID::WINDBURST;
		_damageType = damTy::WIND;
		_habilityType = habTy::ATTACK;
		_mod = ms::INT;
		_obj = objTy::ENEMYTEAM;
	}

	static Hability_Id id() { return habID::WINDBURST; }

	virtual void throwHability(Character* obj, bool critical)const;
};

class WindSlash : public Hability {
public:
	WindSlash(Character* caster = nullptr) : Hability(caster) {

		level = 2;
		_mana = 2;
		_name = "Wind Slash";
		_description = "Menuda brisa, a hace 1d8 a un enemigo frente a salvacion DEX";

		_id = habID::WINDSLASH;
		_damageType = damTy::WIND;
		_habilityType = habTy::ATTACK;
		_mod = ms::INT;
		_obj = objTy::SINGLEENEMY;
	}

	static Hability_Id id() { return habID::WINDSLASH; }

	virtual void throwHability(Character* obj, bool critical)const;
};

class RockPillar : public Hability {
public:
	RockPillar(Character* caster = nullptr) : Hability(caster) {

		level = 3;
		_mana = 3;
		_name = "Rock Pillar";
		_description = "Mejorando la estructura, hace 1d8 a un enemigo frente a salvacion DEX (reduce CON)";

		_id = habID::ROCKPILLAR;
		_damageType = damTy::EARTH;
		_habilityType = habTy::ATTACK;
		_mod = ms::INT;
		_obj = objTy::SINGLEENEMY;
	}

	static Hability_Id id() { return habID::ROCKPILLAR; }

	virtual void throwHability(Character* obj, bool critical)const;
};

class ToxicShadow : public Hability {
public:
	ToxicShadow(Character* caster = nullptr) : Hability(caster) {

		level = 3;
		_mana = 3;
		_name = "Toxic Shadow";
		_description = "Sientes cosquillas, a hace 1d8 a un enemigo frente a salvacion DEX (puede causar envenenamiento)";

		_id = habID::TOXICSHADOW;
		_damageType = damTy::WIND;
		_habilityType = habTy::ATTACK;
		_mod = ms::INT;
		_obj = objTy::SINGLEENEMY;
	}

	static Hability_Id id() { return habID::TOXICSHADOW; }

	virtual void throwHability(Character* obj, bool critical)const;
};

class Tsunami : public Hability {
public:
	Tsunami(Character* caster = nullptr) : Hability(caster) {

		level = 4;
		_mana = 4;
		_name = "Tsunami";
		_description = "Avisaron de bandera roja, a hace 8d6 a todos los enemigos frente a salvacion DEX (y reduce STR)";

		_id = habID::TSUNAMI;
		_damageType = damTy::WATER;
		_habilityType = habTy::ATTACK;
		_mod = ms::INT;
		_obj = objTy::ENEMYTEAM;
	}

	static Hability_Id id() { return habID::TSUNAMI; }

	virtual void throwHability(Character* obj, bool critical)const;
};

class DivineProtection : public Hability {
public:
	DivineProtection(Character* caster = nullptr) : Hability(caster) {

		level = 3;
		_mana = 2;
		_name = "Divine protection";
		_description = "Reduce el daño recibido en el proximo ataque";

		_id = habID::DIVINEPROTECTION;
		_damageType = damTy::LIGHT;
		_habilityType = habTy::BUFF;
		_mod = ms::INT;
		_obj = objTy::CASTER;
	}

	static Hability_Id id() { return habID::DIVINEPROTECTION; }

	virtual void throwHability(Character* obj, bool critical)const;
};

class Flash : public Hability {
public:
	Flash(Character* caster = nullptr) : Hability(caster) {

		level = 2;
		_mana = 2;
		_name = "Flash";
		_description = "Sonrie, a hace 1d8 a un enemigo frente a salvacion DEX(reduce DEX)";

		_id = habID::FLASH;
		_damageType = damTy::LIGHT;
		_habilityType = habTy::ATTACK;
		_mod = ms::INT;
		_obj = objTy::SINGLEENEMY;
	}

	static Hability_Id id() { return habID::FLASH; }

	virtual void throwHability(Character* obj, bool critical)const;
};

class Freeze : public Hability {
public:
	Freeze(Character* caster = nullptr) : Hability(caster) {

		level = 3;
		_mana = 3;
		_name = "Freeze";
		_description = "Winter is coming FOR THEM, a hace 1d8 a un enemigo frente a salvacion DEX (y reduce DEX)";

		_id = habID::FREEZE;
		_damageType = damTy::ICE;
		_habilityType = habTy::ATTACK;
		_mod = ms::INT;
		_obj = objTy::SINGLEENEMY;
	}

	static Hability_Id id() { return habID::FREEZE; }

	virtual void throwHability(Character* obj, bool critical)const;
};
class Whirlpool : public Hability {
public:
	Whirlpool(Character* caster = nullptr) : Hability(caster) {

		level = 1;
		_mana = 2;
		_name = "Whirlpool";
		_description = "Mas agua, a hace 1d8 a un enemigo frente a salvacion DEX (y reduce STR)";

		_id = habID::WHIRLPOOL;
		_damageType = damTy::WATER;
		_habilityType = habTy::ATTACK;
		_mod = ms::INT;
		_obj = objTy::SINGLEENEMY;
	}

	static Hability_Id id() { return habID::WHIRLPOOL; }

	virtual void throwHability(Character* obj, bool critical)const;
};
class LightBeam : public Hability {
public:
	LightBeam(Character* caster = nullptr) : Hability(caster) {

		level = 3;
		_mana = 3;
		_name = "Light Beam";
		_description = "Muy bonito, pero doloroso, a hace 1d8 a un enemigo frente a salvacion DEX (y reduce DEX)";

		_id = habID::LIGHTBEAM;
		_damageType = damTy::LIGHT;
		_habilityType = habTy::ATTACK;
		_mod = ms::INT;
		_obj = objTy::SINGLEENEMY;
	}

	static Hability_Id id() { return habID::LIGHTBEAM; }

	virtual void throwHability(Character* obj, bool critical)const;
};
class DarkVortex : public Hability {
public:
	DarkVortex(Character* caster = nullptr) : Hability(caster) {

		level = 1;
		_mana = 2;
		_name = "Dark Vortex";
		_description = "No veo, a hace 1d8 a un enemigo frente a salvacion DEX (y reduce DEX)";

		_id = habID::DARKVORTEX;
		_damageType = damTy::DARK;
		_habilityType = habTy::ATTACK;
		_mod = ms::INT;
		_obj = objTy::SINGLEENEMY;
	}

	static Hability_Id id() { return habID::DARKVORTEX; }

	virtual void throwHability(Character* obj, bool critical)const;
};

class FireArrow : public Hability {
public:
	FireArrow(Character* caster = nullptr) : Hability(caster) {

		level = 1;
		_mana = 3;
		_name = "Fire Arrow";
		_description = "Quema, a hace 1d8 a un enemigo frente a salvacion DEX (y reduce DEX)";

		_id = habID::FIREARROW;
		_damageType = damTy::FIRE;
		_habilityType = habTy::ATTACK;
		_mod = ms::DEX;
		_obj = objTy::SINGLEENEMY;
	}

	static Hability_Id id() { return habID::FIREARROW; }

	virtual void throwHability(Character* obj, bool critical)const;
};


class Lighten : public Hability {
public:
	Lighten(Character* caster = nullptr) : Hability(caster) {

		level = 1;
		_mana = 1;
		_name = "Lighten";
		_description = "Aumenta la destreza";

		_id = habID::LIGHTEN;
		_damageType = damTy::LIGHT;
		_habilityType = habTy::BUFF;
		_mod = ms::INT;
		_obj = objTy::CASTER;
	}

	static Hability_Id id() { return habID::LIGHTEN; }

	virtual void throwHability(Character* obj, bool critical)const;
};
class Strengthen : public Hability {
public:
	Strengthen(Character* caster = nullptr) : Hability(caster) {

		level = 1;
		_mana = 1;
		_name = "Strengthen";
		_description = "Aumenta la fuerza";

		_id = habID::STRENGTHEN;
		_damageType = damTy::LIGHT;
		_habilityType = habTy::BUFF;
		_mod = ms::INT;
		_obj = objTy::CASTER;
	}

	static Hability_Id id() { return habID::STRENGTHEN; }

	virtual void throwHability(Character* obj, bool critical)const;
};
class Toughen : public Hability {
public:
	Toughen(Character* caster = nullptr) : Hability(caster) {

		level = 1;
		_mana = 1;
		_name = "Toughen";
		_description = "Aumenta la constitucion";

		_id = habID::TOUGHEN;
		_damageType = damTy::LIGHT;
		_habilityType = habTy::BUFF;
		_mod = ms::INT;
		_obj = objTy::CASTER;
	}

	static Hability_Id id() { return habID::TOUGHEN; }

	virtual void throwHability(Character* obj, bool critical)const;
};
class Meditate : public Hability {
public:
	Meditate(Character* caster = nullptr) : Hability(caster) {

		level = 1;
		_mana = 1;
		_name = "Meditate";
		_description = "Aumenta la inteligencia";

		_id = habID::MEDITATE;
		_damageType = damTy::LIGHT;
		_habilityType = habTy::BUFF;
		_mod = ms::INT;
		_obj = objTy::CASTER;
	}

	static Hability_Id id() { return habID::MEDITATE; }

	virtual void throwHability(Character* obj, bool critical)const;
};

class BloodThirst : public Hability {
public:
	BloodThirst(Character* caster = nullptr) : Hability(caster) {

		level = 2;
		_mana = 3;
		_name = "Blood Thirst";
		_description = "Dame tu vida, a hace 1d8 a un enemigo frente a salvacion DEX y cura al usuario";

		_id = habID::BLOODTHIRST;
		_damageType = damTy::LIGHT;
		_habilityType = habTy::ATTACK;
		_mod = ms::INT;
		_obj = objTy::SINGLEENEMY;
	}

	static Hability_Id id() { return habID::BLOODTHIRST; }

	virtual void throwHability(Character* obj, bool critical)const;
};

class Sacrifice : public Hability {
public:
	Sacrifice(Character* caster = nullptr) : Hability(caster) {

		level = 2;
		_mana = 2;
		_name = "Sacrifice";
		_description = "Dame tu vida, a hace 1d8 a un enemigo frente a salvacion DEX x1.5 ,pero recibe daño de retroceso";

		_id = habID::SACRIFICE;
		_damageType = damTy::LIGHT;
		_habilityType = habTy::ATTACK;
		_mod = ms::INT;
		_obj = objTy::SINGLEENEMY;
	}

	static Hability_Id id() { return habID::SACRIFICE; }

	virtual void throwHability(Character* obj, bool critical)const;
};

class DoubleShot : public Hability {
public:
	DoubleShot(Character* caster = nullptr) : Hability(caster) {

		level = 2;
		_mana = 2;
		_name = "Double Shot";
		_description = "Dispara 2 flechas a la vez, la segunda flecha hace la mitad de daño de la primera";

		_id = habID::DOUBLESHOT;
		_damageType = damTy::LIGHT;
		_habilityType = habTy::ATTACK;
		_mod = ms::DEX;
		_obj = objTy::SINGLEENEMY;
	}

	static Hability_Id id() { return habID::DOUBLESHOT; }

	virtual void throwHability(Character* obj, bool critical)const;
};

class ThrowingAxes : public Hability { //revisar los modificadores
public:
	ThrowingAxes(Character* caster = nullptr) : Hability(caster) {

		level = 4;
		_mana = 3;
		_name = "Throwing Axes";
		_description = "Lanza 3 hachas";

		_id = habID::THROWINGAXES;
		_damageType = damTy::LIGHT;
		_habilityType = habTy::ATTACK;
		_mod = ms::DEX;
		_obj = objTy::SINGLEENEMY;
	}

	static Hability_Id id() { return habID::THROWINGAXES; }

	virtual void throwHability(Character* obj, bool critical)const;
};



class HeavyStrike : public Hability { //modificar la descripcion cuando lo ajustemos, pero de momento solo hace +3 de daño el ataque
public:
	HeavyStrike(Character* caster = nullptr) : Hability(caster) {

		level = 3;
		_mana = 3;
		_name = "Heavy Strike";
		_description = "El ataque hace el doble de daño con una gran probabilidad de fallar";

		_id = habID::HEAVYSTRIKE;
		_damageType = damTy::LIGHT;
		_habilityType = habTy::ATTACK;
		_mod = ms::STR;
		_obj = objTy::SINGLEENEMY;
	}

	static Hability_Id id() { return habID::HEAVYSTRIKE; }

	virtual void throwHability(Character* obj, bool critical)const;
};

class SmokeArrow : public Hability {
public:
	SmokeArrow(Character* caster = nullptr) : Hability(caster) {

		level = 2;
		_mana = 2;
		_name = "Smoke arrow";
		_description = "Dispara una flecha de humo que desorienta a los enemigos y les reduce la destreza durante 3 turnos";

		_id = habID::SMOKEARROW;
		_damageType = damTy::DARK;
		_habilityType = habTy::BUFF;
		_mod = ms::INT;
		_obj = objTy::ENEMYTEAM;
	}

	static Hability_Id id() { return habID::SMOKEARROW; }

	virtual void throwHability(Character* obj, bool critical)const;
};

class Morph : public Hability {
public:
	Morph(Character* caster = nullptr) : Hability(caster) {

		level = 0;
		_mana = 4;
		_name = "Morph";
		_description = "Conviertete en una bestia alterando las estadisticas";

		_id = habID::MORPH;
		_damageType = damTy::DARK;
		_habilityType = habTy::BUFF;
		_mod = ms::INT;
		_obj = objTy::CASTER;
	}

	static Hability_Id id() { return habID::MORPH; }

	virtual void throwHability(Character* obj, bool critical)const;
};
class ReverseMorph : public Hability {
public:
	ReverseMorph(Character* caster = nullptr) : Hability(caster) {

		level = 0;
		_mana = 0;
		_name = "Reverse Morph";
		_description = "Vuelve al estado anterior";

		_id = habID::REVERSEMORPH;
		_damageType = damTy::DARK;
		_habilityType = habTy::BUFF;
		_mod = ms::INT;
		_obj = objTy::CASTER;
	}

	static Hability_Id id() { return habID::REVERSEMORPH; }

	virtual void throwHability(Character* obj, bool critical)const;
};

class RainOfDaggers : public Hability { //revisar los modificadores
public:
	RainOfDaggers(Character* caster = nullptr) : Hability(caster) {

		level = 3;
		_mana = 4;
		_name = "Rain of Daggers";
		_description = "Lanza un numero aleatorio de dagas entre 1 y 10 que hacen cada una un 20% del daño del personaje";

		_id = habID::RAINOFDAGGERS;
		_damageType = damTy::LIGHT;
		_habilityType = habTy::ATTACK;
		_mod = ms::DEX;
		_obj = objTy::SINGLEENEMY;
	}

	static Hability_Id id() { return habID::RAINOFDAGGERS; }

	virtual void throwHability(Character* obj, bool critical)const;
};

class RockProjectiles : public Hability {
public:
	RockProjectiles(Character* caster = nullptr) : Hability(caster) {

		level = 3;
		_mana = 3;
		_name = "Rock Projectiles";
		_description = "Dispara tres rocas que tiene cada una su propia probabilidad de fallar";

		_id = habID::ROCKPROJECTILES;
		_damageType = damTy::EARTH;
		_habilityType = habTy::ATTACK;
		_mod = ms::INT;
		_obj = objTy::SINGLEENEMY;
	}

	static Hability_Id id() { return habID::ROCKPROJECTILES; }

	virtual void throwHability(Character* obj, bool critical)const;
};

class TrickShot : public Hability {
public:
	TrickShot(Character* caster = nullptr) : Hability(caster) { //cambiar la descripcion si al final se hace lo de hacer 2 tiradas de ataque para confirmar que acierta

		level = 4;
		_mana = 3;
		_name = "Trick Shot";
		_description = "Dispara una flecha que hace el triple de daño";

		_id = habID::TRICKSHOT;
		_damageType = damTy::LIGHT;
		_habilityType = habTy::ATTACK;
		_mod = ms::DEX;
		_obj = objTy::SINGLEENEMY;
	}

	static Hability_Id id() { return habID::TRICKSHOT; }

	virtual void throwHability(Character* obj, bool critical)const;
};

class GladiatorBallad : public Hability {
public:
	GladiatorBallad(Character* caster = nullptr) : Hability(caster) {

		level = 0;
		_mana = 3;
		_name = "Gladiator's Ballad";
		_description = "Aumenta la fuerza del equipo durante 3 turnos";

		_id = habID::GLADIATORBALLAD;
		_damageType = damTy::LIGHT;
		_habilityType = habTy::BUFF;
		_mod = ms::INT;
		_obj = objTy::ALLYTEAM;
	}

	static Hability_Id id() { return habID::GLADIATORBALLAD; }

	virtual void throwHability(Character* obj, bool critical)const;
};

class WindSong : public Hability {
public:
	WindSong(Character* caster = nullptr) : Hability(caster) {

		level = 0;
		_mana = 3;
		_name = "Wind Song";
		_description = "Aumenta la velocidad del equipo durante 3 turnos";

		_id = habID::WINDSONG;
		_damageType = damTy::LIGHT;
		_habilityType = habTy::BUFF;
		_mod = ms::INT;
		_obj = objTy::ALLYTEAM;
	}

	static Hability_Id id() { return habID::WINDSONG; }

	virtual void throwHability(Character* obj, bool critical)const;
};

class Determination : public Hability {
public:
	Determination(Character* caster = nullptr) : Hability(caster) {

		level = 3;
		_mana = 4;
		_name = "Determination";
		_description = "El proximo golpe letal que reciba el personaje le dejara con 1 de vida en vez de matarle";

		_id = habID::DETERMINATION;
		_damageType = damTy::LIGHT;
		_habilityType = habTy::BUFF;
		_mod = ms::CON;
		_obj = objTy::CASTER;
	}

	static Hability_Id id() { return habID::DETERMINATION; }

	virtual void throwHability(Character* obj, bool critical)const;
};

class Blessing : public Hability {
public:
	Blessing(Character* caster = nullptr) : Hability(caster) {

		level = 1;
		_mana = 9;
		_name = "Blessing";
		_description = "Quita los efectos negativos a todos los miembros del equipo";

		_id = habID::BLESSING;
		_damageType = damTy::LIGHT;
		_habilityType = habTy::BUFF;
		_mod = ms::INT;
		_obj = objTy::ALLYTEAM;
	}

	static Hability_Id id() { return habID::BLESSING; }

	virtual void throwHability(Character* obj, bool critical)const;
};

#pragma endregion

#pragma region CONDITION

enum class Conditions_Id {
	BLEEDING,
	EJEMPLOCURACIONFINALTURNO,
	EJEMPLOREDUCCIONATAQUE,
	EJEMPLOREVIVIRMUERTE,
	BUFFSTATS,
	DETERMINATIONCOND,
	_lastConditionId_
};
using condID = Conditions_Id;

class Condition {
protected:
	std::string _name = "DefaultName";
	std::string _description = "DefaultDescription";

	int _counter = 0;
	int _turns = 0;
	int _stack = 1;

	Conditions_Id _id;

	Character* _caster;

	Character* _objective;

	bool _positive;

public:

	Condition() : _objective(nullptr), _caster(nullptr), _id(), _positive() {}

	Condition(Character* objective, Character* caster) :_objective(objective), _caster(caster), _id(), _positive() {
	}

	virtual void init() = 0;

	virtual bool onTurnStarted() { return true; };

	virtual bool onTurnEnd() { return true; };

	virtual bool onAttackRecieved(int& damage, Character* attacker) { return true; };

	virtual bool onDeath(Character* attacker) { return true; };

	bool isPositive() { return _positive; }

	int getTurnsLeft() { return _counter; }

	void resetTurns() { _counter = _turns; }

	void addStack() { _stack++; }

	virtual Conditions_Id getID() { return _id; }

	static Conditions_Id id() { return condID::_lastConditionId_; }
};

class Bleeding : public Condition {
public:
	Bleeding(Character* objective, Character* caster) : Condition(objective, caster) {
		_name = "Ejemplo de daño cada turno";
		_description = "Hace 1d3 de daño cada turno, durante 3 turnos";
		_turns = 3;
		_id = condID::BLEEDING;
		resetTurns();
	}

	virtual void init();

	virtual bool onTurnStarted();

	static Conditions_Id id() { return condID::BLEEDING; }
};


class EjemploCuracionFinalTurno : public Condition {
public:

	EjemploCuracionFinalTurno(Character* objective, Character* caster) : Condition(objective, caster) {
		_name = "Ejemplo de daño cada turno";
		_description = "Cura 1d3 cada final de turno, durante 3 turnos";
		_turns = 3;
		_id = condID::EJEMPLOCURACIONFINALTURNO;
		resetTurns();
	}

	virtual void init();

	virtual bool onTurnEnd();

	static Conditions_Id id() { return condID::EJEMPLOCURACIONFINALTURNO; }
};

class EjemploReduccionAtaque : public Condition {
public:

	EjemploReduccionAtaque(Character* objective, Character* caster) : Condition(objective, caster) {
		_name = "Ejemplo de daño cada turno";
		_description = "Reduce el daño el siguiente ataque a la mitad";
		_id = condID::EJEMPLOREDUCCIONATAQUE;
		resetTurns();
	}

	virtual void init();

	virtual bool onAttackRecieved(int& damage, Character* attacker);

	static Conditions_Id id() { return condID::EJEMPLOREDUCCIONATAQUE; }
};


class EjemploRevivirMuerte : public Condition {
public:

	EjemploRevivirMuerte(Character* objective, Character* caster) : Condition(objective, caster) {
		_name = "Ejemplo de daño cada turno";
		_description = "Revivira con 5 de vida al morir";
		_id = condID::EJEMPLOREVIVIRMUERTE;
		resetTurns();
	}

	virtual void init();

	virtual bool onDeath(Character* attacker);

	static Conditions_Id id() { return condID::EJEMPLOREVIVIRMUERTE; }
};


//obj->addCondition<BuffoX>(mainStat x, string name, string description);


class BuffStats : public Condition {
public:

	BuffStats(Character* objective, Character* caster, int val, mainStat stat, std::string name, std::string description) :statMod(stat), value(val), Condition(objective, caster) {
		_name = name;
		_description = description;
		_id = condID::BUFFSTATS;
		(val > 0) ? _positive = true : _positive = false;

		resetTurns();
	}

	virtual void init();

	virtual bool onTurnStarted();

	static Conditions_Id id() { return condID::BUFFSTATS; }

private:
	int value;
	mainStat statMod;
};


class DeterminationCond : public Condition {
public:

	DeterminationCond(Character* objective, Character* caster) : Condition(objective, caster) {
		_name = "Determination condition";
		_description = "Cuando muera el personaje este revivira con 1 punto de vida";
		_id = condID::DETERMINATIONCOND;
		resetTurns();
	}

	virtual void init();

	virtual bool onDeath(Character* attacker);

	static Conditions_Id id() { return condID::DETERMINATIONCOND; }
};

#pragma endregion
