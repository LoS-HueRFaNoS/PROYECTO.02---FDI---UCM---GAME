#pragma once

#include <vector>
#include "RPGLogic.h"
#include <string>
#include <assert.h>

using namespace rpgLogic;

class Character;

#pragma region HABILITY

enum Hability_Id {
	LIGHTATTACK, //0
	FIREBALL, //1
	BLOODYSTRIKE, //2
	HEALINGWORD, //3
	ALLYTEAMHEALEXAMPLE, //4
	SELFHEALEXAMPLE, //5
	ALLYTEAMATTACKEXAMPLE, //6
	WINDBURST, //7
	WINDSLASH, //8
	ROCKPILLAR, //9
	TOXICSHADOW, //10
	TSUNAMI, //11
	DIVINEPROTECTION, //12
	FLASH, //13
	FREEZE, //14
	WHIRLPOOL, //15
	LIGHTBEAM, //16
	DARKVORTEX, //17
	FIREARROW, //18
	MEDITATE, //19
	LIGHTEN, //20
	STRENGTHEN, //21
	TOUGHEN, //22
	BLOODTHIRST, //23
	SACRIFICE, //24
	DOUBLESHOT, //25
	THROWINGAXES, //26
	MORPH, //27
	REVERSEMORPH, //28
	HEAVYSTRIKE, //29
	SMOKEARROW,	//30
	RAINOFDAGGERS,	//31
	ROCKPROJECTILES, //32
	TRICKSHOT, //33
	GLADIATORBALLAD, //34
	WINDSONG, //35
	DETERMINATION, //36
	_lasHabilityId_
};

enum ObjectiveType
{
	SINGLEALLY,
	SINGLEENEMY,
	ALLYTEAM,
	ENEMYTEAM,
	CASTER
};

enum HabilityType {
	ATTACK,
	DEBUFF,
	HEAL,
	BUFF
};


class Hability {
protected:
	int level = 0;
	int _mana = 0;
	std::string _name = "DefaultName";
	std::string _description = "DefaultDescription";

	damageType _damageType = damageType(0);
	mainStat _mod = _LastStatId_;
	ObjectiveType _obj = CASTER;

	HabilityType _habilityType = ATTACK;

	Character* _caster;

public:

	static Hability_Id id() {
		return _lasHabilityId_;;
	}

	Hability() :_caster(nullptr) {}

	Hability(Character* caster) :_caster(caster) {}

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
	LightAttack(Character* caster = nullptr) :Hability(caster) {
		level = 0;
		_mana = 0;
		_name = "Light Attack";
		_description = "Golpe to guapo con el arma, a terminar";

		_habilityType = ATTACK;
		_mod = STR;
		_obj = SINGLEENEMY;
	}

	static Hability_Id id() { return LIGHTATTACK; }

	virtual void throwHability(Character* obj, bool critical)const;
};

class Fireball : public Hability {
public:
	Fireball(Character* caster = nullptr) :Hability(caster) {

		level = 4;
		_mana = 0;
		_name = "Fireball";
		_description = "Bola de fuego to guapa, a hace 8d6 a todos los enemigos frente a salvacion DEX";

		_damageType = FIRE;
		_habilityType = ATTACK;
		_mod = INT;
		_obj = ENEMYTEAM;
	}

	static Hability_Id id() { return FIREBALL; }

	virtual void throwHability(Character* obj, bool critical)const;
};


class BloodyStrike : public Hability {
public:
	BloodyStrike(Character* caster = nullptr) :Hability(caster) {

		level = 0;
		_mana = 0;
		_name = "BloodyStrike";
		_description = "Esto es un ejemplo, hace 1d5 de daño";

		_damageType = ICE;
		_habilityType = ATTACK;
		_mod = INT;
		_obj = SINGLEENEMY;
	}

	static Hability_Id id() { return BLOODYSTRIKE; }

	virtual void throwHability(Character* obj, bool critical)const;
};



class HealingWord : public Hability {
public:
	HealingWord(Character* caster = nullptr) :Hability(caster) {

		level = 0;
		_mana = 0;
		_name = "HealingWord";
		_description = "Esto es un ejemplo, cura 2d5 de vida a un aliado";

		_damageType = LIGHT;
		_habilityType = HEAL;
		_mod = INT;
		_obj = SINGLEALLY;
	}

	static Hability_Id id() { return HEALINGWORD; }

	virtual void throwHability(Character* obj, bool critical)const;
};


class AllyTeamHealExample : public Hability {
public:
	AllyTeamHealExample(Character* caster = nullptr) :Hability(caster) {

		level = 0;
		_mana = 0;
		_name = "AllyTeamHealExample";
		_description = "Esto es un ejemplo, cura a todo tu equipo 1d5";

		_damageType = LIGHT;
		_habilityType = HEAL;
		_mod = INT;
		_obj = ALLYTEAM;
	}

	static Hability_Id id() { return ALLYTEAMHEALEXAMPLE; }

	virtual void throwHability(Character* obj, bool critical)const;
};


class SelfHealExample : public Hability {
public:
	SelfHealExample(Character* caster = nullptr) :Hability(caster) {

		level = 0;
		_mana = 0;
		_name = "SelfHealExample";
		_description = "Esto es un ejemplo, te cura 1d8";

		_damageType = LIGHT;
		_habilityType = HEAL;
		_mod = INT;
		_obj = CASTER;
	}

	static Hability_Id id() { return SELFHEALEXAMPLE; }

	virtual void throwHability(Character* obj, bool critical)const;
};


class AllyTeamAttackExample : public Hability {
public:
	AllyTeamAttackExample(Character* caster = nullptr) :Hability(caster) {

		level = 0;
		_mana = 0;
		_name = "AllyTeamAttackExample";
		_description = "Esto es un ejemplo, se te va la cabeza y haces 2d4 de daño a tu equipo";

		_damageType = DARK;
		_habilityType = ATTACK;
		_mod = INT;
		_obj = ALLYTEAM;
	}

	static Hability_Id id() { return ALLYTEAMATTACKEXAMPLE; }

	virtual void throwHability(Character* obj, bool critical)const;
};

//-----------------------------------------------------------------------------

class WindBurst : public Hability {
public:
	WindBurst(Character* caster = nullptr) :Hability(caster) {

		level = 4;
		_mana = 0;
		_name = "WindBurst";
		_description = "Sal a que te de el aire, hace 8d6 a todos los enemigos frente a salvacion DEX (reduce DEX)";

		_damageType = WIND;
		_habilityType = ATTACK;
		_mod = INT;
		_obj = ENEMYTEAM;
	}

	static Hability_Id id() { return WINDBURST; }

	virtual void throwHability(Character* obj, bool critical)const;
};

class WindSlash : public Hability {
public:
	WindSlash(Character* caster = nullptr) :Hability(caster) {

		level = 4;
		_mana = 0;
		_name = "Wind Slash";
		_description = "Menuda brisa, a hace 1d8 a un enemigo frente a salvacion DEX";

		_damageType = WIND;
		_habilityType = ATTACK;
		_mod = INT;
		_obj = SINGLEENEMY;
	}

	static Hability_Id id() { return WINDSLASH; }

	virtual void throwHability(Character* obj, bool critical)const;
};

class RockPillar : public Hability {
public:
	RockPillar(Character* caster = nullptr) :Hability(caster) {

		level = 4;
		_mana = 0;
		_name = "Rock Pillar";
		_description = "Mejorando la estructura, a hace 1d8 a un enemigo frente a salvacion DEX (reduce CON)";

		_damageType = WIND;
		_habilityType = ATTACK;
		_mod = INT;
		_obj = SINGLEENEMY;
	}

	static Hability_Id id() { return ROCKPILLAR; }

	virtual void throwHability(Character* obj, bool critical)const;
};

class ToxicShadow : public Hability {
public:
	ToxicShadow(Character* caster = nullptr) :Hability(caster) {

		level = 4;
		_mana = 0;
		_name = "Toxic Shadow";
		_description = "Sientes cosquillas, a hace 1d8 a un enemigo frente a salvacion DEX (puede causar envenenamiento)";

		_damageType = WIND;
		_habilityType = ATTACK;
		_mod = INT;
		_obj = SINGLEENEMY;
	}

	static Hability_Id id() { return TOXICSHADOW; }

	virtual void throwHability(Character* obj, bool critical)const;
};

class Tsunami : public Hability {
public:
	Tsunami(Character* caster = nullptr) :Hability(caster) {

		level = 4;
		_mana = 0;
		_name = "Tsunami";
		_description = "Avisaron de bandera roja, a hace 8d6 a todos los enemigos frente a salvacion DEX (y reduce STR)";

		_damageType = WATER;
		_habilityType = ATTACK;
		_mod = INT;
		_obj = ENEMYTEAM;
	}

	static Hability_Id id() { return TSUNAMI; }

	virtual void throwHability(Character* obj, bool critical)const;
};

class DivineProtection : public Hability {
public:
	DivineProtection(Character* caster = nullptr) :Hability(caster) {

		level = 4;
		_mana = 0;
		_name = "Divine protection";
		_description = "Reduce el daño recibido en el proximo ataque";

		_damageType = LIGHT;
		_habilityType = BUFF;
		_mod = INT;
		_obj = CASTER;
	}

	static Hability_Id id() { return DIVINEPROTECTION; }

	virtual void throwHability(Character* obj, bool critical)const;
};

class Flash : public Hability {
public:
	Flash(Character* caster = nullptr) :Hability(caster) {

		level = 4;
		_mana = 0;
		_name = "Flash";
		_description = "Sonrie, a hace 1d8 a un enemigo frente a salvacion DEX(reduce DEX)";

		_damageType = LIGHT;
		_habilityType = ATTACK;
		_mod = INT;
		_obj = SINGLEENEMY;
	}

	static Hability_Id id() { return FLASH; }

	virtual void throwHability(Character* obj, bool critical)const;
};

class Freeze : public Hability {
public:
	Freeze(Character* caster = nullptr) :Hability(caster) {

		level = 4;
		_mana = 0;
		_name = "Freeze";
		_description = "Winter is coming FOR THEM, a hace 1d8 a un enemigo frente a salvacion DEX (y reduce DEX)";

		_damageType = ICE;
		_habilityType = ATTACK;
		_mod = INT;
		_obj = SINGLEENEMY;
	}

	static Hability_Id id() { return FREEZE; }

	virtual void throwHability(Character* obj, bool critical)const;
};
class Whirlpool : public Hability {
public:
	Whirlpool(Character* caster = nullptr) :Hability(caster) {

		level = 4;
		_mana = 0;
		_name = "Whirlpool";
		_description = "Mas agua, a hace 1d8 a un enemigo frente a salvacion DEX (y reduce DEX)";

		_damageType = WATER;
		_habilityType = ATTACK;
		_mod = INT;
		_obj = SINGLEENEMY;
	}

	static Hability_Id id() { return WHIRLPOOL; }

	virtual void throwHability(Character* obj, bool critical)const;
};
class LightBeam : public Hability {
public:
	LightBeam(Character* caster = nullptr) :Hability(caster) {

		level = 4;
		_mana = 0;
		_name = "Light Beam";
		_description = "Muy bonito, pero doloroso, a hace 1d8 a un enemigo frente a salvacion DEX (y reduce DEX)";

		_damageType = LIGHT;
		_habilityType = ATTACK;
		_mod = INT;
		_obj = SINGLEENEMY;
	}

	static Hability_Id id() { return LIGHTBEAM; }

	virtual void throwHability(Character* obj, bool critical)const;
};
class DarkVortex : public Hability {
public:
	DarkVortex(Character* caster = nullptr) :Hability(caster) {

		level = 4;
		_mana = 0;
		_name = "Dark Vortex";
		_description = "No veo, a hace 1d8 a un enemigo frente a salvacion DEX (y reduce DEX)";

		_damageType = DARK;
		_habilityType = ATTACK;
		_mod = INT;
		_obj = SINGLEENEMY;
	}

	static Hability_Id id() { return DARKVORTEX; }

	virtual void throwHability(Character* obj, bool critical)const;
};

class FireArrow : public Hability {
public:
	FireArrow(Character* caster = nullptr) :Hability(caster) {

		level = 4;
		_mana = 0;
		_name = "Fire Arrow";
		_description = "Quema, a hace 1d8 a un enemigo frente a salvacion DEX (y reduce DEX)";

		_damageType = FIRE;
		_habilityType = ATTACK;
		_mod = DEX;
		_obj = SINGLEENEMY;
	}

	static Hability_Id id() { return FIREARROW; }

	virtual void throwHability(Character* obj, bool critical)const;
};


class Lighten : public Hability {
public:
	Lighten(Character* caster = nullptr) :Hability(caster) {

		level = 4;
		_mana = 0;
		_name = "Lighten";
		_description = "Aumenta la destreza";

		_damageType = LIGHT;
		_habilityType = BUFF;
		_mod = INT;
		_obj = CASTER;
	}

	static Hability_Id id() { return LIGHTEN; }

	virtual void throwHability(Character* obj, bool critical)const;
};
class Strengthen : public Hability {
public:
	Strengthen(Character* caster = nullptr) :Hability(caster) {

		level = 4;
		_mana = 0;
		_name = "Strengthen";
		_description = "Aumenta la fuerza";

		_damageType = LIGHT;
		_habilityType = BUFF;
		_mod = INT;
		_obj = CASTER;
	}

	static Hability_Id id() { return STRENGTHEN; }

	virtual void throwHability(Character* obj, bool critical)const;
};
class Toughen : public Hability {
public:
	Toughen(Character* caster = nullptr) :Hability(caster) {

		level = 4;
		_mana = 0;
		_name = "Toughen";
		_description = "Aumenta la constitucion";

		_damageType = LIGHT;
		_habilityType = BUFF;
		_mod = INT;
		_obj = CASTER;
	}

	static Hability_Id id() { return TOUGHEN; }

	virtual void throwHability(Character* obj, bool critical)const;
};
class Meditate : public Hability {
public:
	Meditate(Character* caster = nullptr) :Hability(caster) {

		level = 4;
		_mana = 0;
		_name = "Meditate";
		_description = "Aumenta la inteligencia";

		_damageType = LIGHT;
		_habilityType = BUFF;
		_mod = INT;
		_obj = CASTER;
	}

	static Hability_Id id() { return MEDITATE; }

	virtual void throwHability(Character* obj, bool critical)const;
};

class BloodThirst : public Hability {
public:
	BloodThirst(Character* caster = nullptr) :Hability(caster) {

		level = 4;
		_mana = 0;
		_name = "Blood Thirst";
		_description = "Dame tu vida, a hace 1d8 a un enemigo frente a salvacion DEX y cura al usuario";

		_damageType = LIGHT;
		_habilityType = ATTACK;
		_mod = INT;
		_obj = SINGLEENEMY;
	}

	static Hability_Id id() { return BLOODTHIRST; }

	virtual void throwHability(Character* obj, bool critical)const;
};

class Sacrifice : public Hability {
public:
	Sacrifice(Character* caster = nullptr) :Hability(caster) {

		level = 4;
		_mana = 0;
		_name = "Sacrifice";
		_description = "Dame tu vida, a hace 1d8 a un enemigo frente a salvacion DEX x1.5 ,pero recibe daño de retroceso";

		_damageType = LIGHT;
		_habilityType = ATTACK;
		_mod = INT;
		_obj = SINGLEENEMY;
	}

	static Hability_Id id() { return SACRIFICE; }

	virtual void throwHability(Character* obj, bool critical)const;
};

class DoubleShot : public Hability {
public:
	DoubleShot(Character* caster = nullptr) :Hability(caster) {

		level = 4;
		_mana = 0;
		_name = "Double Shot";
		_description = "Dispara 2 flechas a la vez, la segunda flecha hace la mitad de daño de la primera";

		_damageType = LIGHT;
		_habilityType = ATTACK;
		_mod = DEX;
		_obj = SINGLEENEMY;
	}

	static Hability_Id id() { return DOUBLESHOT; }

	virtual void throwHability(Character* obj, bool critical)const;
};

class ThrowingAxes : public Hability { //revisar los modificadores
public:
	ThrowingAxes(Character* caster = nullptr) :Hability(caster) {

		level = 4;
		_mana = 0;
		_name = "Throwing Axes";
		_description = "Lanza 3 hachas";

		_damageType = LIGHT;
		_habilityType = ATTACK;
		_mod = DEX;
		_obj = SINGLEENEMY;
	}

	static Hability_Id id() { return THROWINGAXES; }

	virtual void throwHability(Character* obj, bool critical)const;
};



class HeavyStrike : public Hability { //modificar la descripcion cuando lo ajustemos, pero de momento solo hace +3 de daño el ataque
public:
	HeavyStrike(Character* caster = nullptr) :Hability(caster) {

		level = 4;
		_mana = 0;
		_name = "Heavy Strike";
		_description = "El ataque hace el doble de daño con una gran probabilidad de fallar";

		_damageType = LIGHT;
		_habilityType = ATTACK;
		_mod = STR;
		_obj = SINGLEENEMY;
	}

	static Hability_Id id() { return HEAVYSTRIKE; }

	virtual void throwHability(Character* obj, bool critical)const;
};

class SmokeArrow : public Hability {
public:
	SmokeArrow(Character* caster = nullptr) :Hability(caster) {

		level = 4;
		_mana = 0;
		_name = "Smoke arrow";
		_description = "Dispara una flecha de humo que desorienta a los enemigos y les reduce la destreza durante 3 turnos";

		_damageType = DARK;
		_habilityType = BUFF;
		_mod = INT;
		_obj = ENEMYTEAM;
	}

	static Hability_Id id() { return SMOKEARROW; }

	virtual void throwHability(Character* obj, bool critical)const;
};

class Morph : public Hability {
public:
	Morph(Character* caster = nullptr) :Hability(caster) {

		level = 4;
		_mana = 0;
		_name = "Morph";
		_description = "Conviertete en una bestia alterando las estadisticas";

		_damageType = DARK;
		_habilityType = BUFF;
		_mod = INT;
		_obj = CASTER;
	}

	static Hability_Id id() { return MORPH; }

	virtual void throwHability(Character* obj, bool critical)const;
};
class ReverseMorph : public Hability {
public:
	ReverseMorph(Character* caster = nullptr) :Hability(caster) {

		level = 4;
		_mana = 0;
		_name = "Reverse Morph";
		_description = "Vuelve al estado anterior";

		_damageType = DARK;
		_habilityType = BUFF;
		_mod = INT;
		_obj = CASTER;
	}

	static Hability_Id id() { return REVERSEMORPH; }

	virtual void throwHability(Character* obj, bool critical)const;
};

class RainOfDaggers : public Hability { //revisar los modificadores
public:
	RainOfDaggers(Character* caster = nullptr) :Hability(caster) {

		level = 4;
		_mana = 0;
		_name = "Rain of Daggers";
		_description = "Lanza un numero aleatorio de dagas entre 1 y 10 que hacen cada una un 20% del daño del personaje";

		_damageType = LIGHT;
		_habilityType = ATTACK;
		_mod = DEX;
		_obj = SINGLEENEMY;
	}

	static Hability_Id id() { return RAINOFDAGGERS; }

	virtual void throwHability(Character* obj, bool critical)const;
};

class RockProjectiles : public Hability {
public:
	RockProjectiles(Character* caster = nullptr) :Hability(caster) {

		level = 4;
		_mana = 0;
		_name = "Rock Projectiles";
		_description = "Dispara tres rocas que tiene cada una su propia probabilidad de fallar";

		_damageType = EARTH;
		_habilityType = ATTACK;
		_mod = INT;
		_obj = SINGLEENEMY;
	}

	static Hability_Id id() { return ROCKPROJECTILES; }

	virtual void throwHability(Character* obj, bool critical)const;
};

class TrickShot : public Hability {
public:
	TrickShot(Character* caster = nullptr) :Hability(caster) { //cambiar la descripcion si al final se hace lo de hacer 2 tiradas de ataque para confirmar que acierta

		level = 4;
		_mana = 0;
		_name = "Trick Shot";
		_description = "Dispara una flecha que hace el triple de daño";

		_damageType = LIGHT;
		_habilityType = ATTACK;
		_mod = DEX;
		_obj = SINGLEENEMY;
	}

	static Hability_Id id() { return TRICKSHOT; }

	virtual void throwHability(Character* obj, bool critical)const;
};

class GladiatorBallad : public Hability {
public:
	GladiatorBallad(Character* caster = nullptr) :Hability(caster) {

		level = 0;
		_mana = 0;
		_name = "Gladiator's Ballad";
		_description = "Aumenta la fuerza del equipo durante 3 turnos";

		_damageType = LIGHT;
		_habilityType = BUFF;
		_mod = INT;
		_obj = ALLYTEAM;
	}

	static Hability_Id id() { return GLADIATORBALLAD; }

	virtual void throwHability(Character* obj, bool critical)const;
};

class WindSong : public Hability {
public:
	WindSong(Character* caster = nullptr) :Hability(caster) {

		level = 0;
		_mana = 0;
		_name = "Wind Song";
		_description = "Aumenta la velocidad del equipo durante 3 turnos";

		_damageType = LIGHT;
		_habilityType = BUFF;
		_mod = INT;
		_obj = ALLYTEAM;
	}

	static Hability_Id id() { return WINDSONG; }

	virtual void throwHability(Character* obj, bool critical)const;
};

class Determination : public Hability {
public:
	Determination(Character* caster = nullptr) :Hability(caster) {

		level = 0;
		_mana = 0;
		_name = "Determination";
		_description = "El proximo golpe letal que reciba el personaje le dejara con 1 de vida en vez de matarle";

		_damageType = LIGHT;
		_habilityType = BUFF;
		_mod = CON;
		_obj = CASTER;
	}

	static Hability_Id id() { return DETERMINATION; }

	virtual void throwHability(Character* obj, bool critical)const;
};

#pragma endregion

#pragma region CONDITION

enum Conditions_Id {
	BLEEDING,
	EJEMPLOCURACIONFINALTURNO,
	EJEMPLOREDUCCIONATAQUE,
	EJEMPLOREVIVIRMUERTE,
	BUFFSTATS,
	DETERMINATIONCOND,
	_lastConditionId_
};


enum ConditionType {
	ON_TURN_STARTED,
	ON_TURN_ENDED,
	ON_ATTACK_RECIEVED,
	ON_DEATH,
	_lastConditionType_
};

class Condition {
protected:
	std::string _name = "DefaultName";
	std::string _description = "DefaultDescription";

	int _counter = 0;
	int _turns = 0;
	int _stack = 1;

	ConditionType _type;
	Conditions_Id _id;

	Character* _objective;

	bool _positive;

public:

	Condition() :_objective(nullptr) {}

	Condition(Character* objective) :_objective(objective) {
	}

	virtual void init() = 0;

	virtual bool onTurnStarted() { return false; };

	virtual bool onTurnEnd() { return false; };

	virtual bool onAttackRecieved(int& damage) { return false; };

	virtual bool onDeath() { return false; };

	bool isPositive() { return _positive; }

	int getTurnsLeft() { return _counter; }

	void resetTurns() { _counter = _turns; }

	void addStack() { _stack++; }

	Conditions_Id getId() { return _id; }

	ConditionType getType() { return _type; }

	static Conditions_Id id() { return _lastConditionId_; }
};

class Bleeding : public Condition {
public:
	Bleeding(Character* objective) : Condition(objective) {
		_name = "Ejemplo de daño cada turno";
		_description = "Hace 1d3 de daño cada turno, durante 3 turnos";
		_turns = 3;
		_type = ON_TURN_STARTED;
		_id = BLEEDING;
		resetTurns();
	}

	virtual void init();

	virtual bool onTurnStarted();

	static Conditions_Id id() { return BLEEDING; }
};


class EjemploCuracionFinalTurno : public Condition {
public:

	EjemploCuracionFinalTurno(Character* objective) : Condition(objective) {
		_name = "Ejemplo de daño cada turno";
		_description = "Cura 1d3 cada final de turno, durante 3 turnos";
		_turns = 3;
		_type = ON_TURN_ENDED;
		_id = EJEMPLOCURACIONFINALTURNO;
		resetTurns();
	}

	virtual void init();

	virtual bool onTurnEnd();

	static Conditions_Id id() { return EJEMPLOCURACIONFINALTURNO; }
};

class EjemploReduccionAtaque : public Condition {
public:

	EjemploReduccionAtaque(Character* objective) : Condition(objective) {
		_name = "Ejemplo de daño cada turno";
		_description = "Reduce el daño el siguiente ataque a la mitad";
		_type = ON_ATTACK_RECIEVED;
		_id = EJEMPLOREDUCCIONATAQUE;
		resetTurns();
	}

	virtual void init();

	virtual bool onAttackRecieved(int& damage);

	static Conditions_Id id() { return EJEMPLOREDUCCIONATAQUE; }
};


class EjemploRevivirMuerte : public Condition {
public:

	EjemploRevivirMuerte(Character* objective) : Condition(objective) {
		_name = "Ejemplo de daño cada turno";
		_description = "Revivira con 5 de vida al morir";
		_type = ON_DEATH;
		_id = EJEMPLOREVIVIRMUERTE;
		resetTurns();
	}

	virtual void init();

	virtual bool onDeath();

	static Conditions_Id id() { return EJEMPLOREVIVIRMUERTE; }
};


//obj->addCondition<BuffoX>(mainStat x, string name, string description);


class BuffStats : public Condition {
public:

	BuffStats(Character* objective, int val, mainStat stat, std::string name, std::string description) :statMod(stat), value(val), Condition(objective) {
		_name = name;
		_description = description;
		_type = ON_TURN_STARTED;
		_id = BUFFSTATS;
		(val > 0) ? _positive = true : _positive = false;

		resetTurns();
	}

	virtual void init();

	virtual bool onTurnStarted();

	static Conditions_Id id() { return BUFFSTATS; }

private:
	int value;
	mainStat statMod;
};


class DeterminationCond : public Condition {
public:

	DeterminationCond(Character* objective) : Condition(objective) {
		_name = "Determination condition";
		_description = "Cuando muera el personaje este revivira con 1 punto de vida";
		_type = ON_DEATH;
		_id = DETERMINATIONCOND;
		resetTurns();
	}

	virtual void init();

	virtual bool onDeath();

	static Conditions_Id id() { return DETERMINATIONCOND; }
};

#pragma endregion
