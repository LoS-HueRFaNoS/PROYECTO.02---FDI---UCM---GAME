#pragma once

#include <vector>
#include "RPGLogic.h"
#include <string>

using namespace rpgLogic;

class Character;

#pragma region HABILITY

enum Hability_Id {
	LIGHTATTACK,
	FIREBALL,
	SINGLETARGETATTACKEXAMPLE,
	SINGLETARGETHEALXAMPLE,
	ALLYTEAMHEALEXAMPLE,
	SELFHEALEXAMPLE,
	ALLYTEAMATTACKEXAMPLE,
	WINDBURST,
	WINDSLASH,
	ROCKPILLAR,
	TOXICSHADOW,
	TSUNAMI,
	DIVINEPROTECTION,
	FLASH,
	FREEZE,
	WHIRLPOOL,
	LIGHTBEAM,
	DARKVORTEX,
	FIREARROW,
	MEDITATE,
	LIGHTEN,
	STRENGTHEN,
	TOUGHEN,
	BLOODTHIRST,
	SACRIFICE,
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

	int getMana() { return _mana; }

	Character* getCaster() { return _caster; }

	virtual void throwHability(Character* obj, bool critical)const = 0;

	std::string name() { return _name; }

	std::string description() { return _description; }

	mainStat getMod() { return _mod; }

	ObjectiveType getObjectiveType() { return _obj; }

	HabilityType getHabilityType() { return _habilityType; }
};

class LightAttack : public Hability {
public:
	LightAttack(Character* caster) :Hability(caster) {
		level = 0;
		_mana = 0;
		_name = "Light Attack";
		_description = "Golpe to guapo con el arma, a terminar";

		_habilityType = ATTACK;
		_mod = STR;
		_obj = SINGLEENEMY;
	}

	void throwHability(Character* obj, bool critical)const override;
};

class Fireball : public Hability {
public:
	Fireball(Character* caster) :Hability(caster) {

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

	void throwHability(Character* obj, bool critical)const override;
};


class SingleTargetAttackExample : public Hability {
public:
	SingleTargetAttackExample(Character* caster) :Hability(caster) {

		level = 0;
		_mana = 0;
		_name = "SingleTargetAttackExample";
		_description = "Esto es un ejemplo, hace 1d5 de daño";

		_damageType = ICE;
		_habilityType = ATTACK;
		_mod = INT;
		_obj = SINGLEENEMY;
	}

	static Hability_Id id() { return SINGLETARGETATTACKEXAMPLE; }

	void throwHability(Character* obj, bool critical)const override;
};



class SingleTargetHealxample : public Hability {
public:
	SingleTargetHealxample(Character* caster) :Hability(caster) {

		level = 0;
		_mana = 0;
		_name = "SingleTargetHealxample";
		_description = "Esto es un ejemplo, cura 2d5 de vida a un aliado";

		_damageType = LIGHT;
		_habilityType = HEAL;
		_mod = INT;
		_obj = SINGLEALLY;
	}

	static Hability_Id id() { return SINGLETARGETHEALXAMPLE; }

	void throwHability(Character* obj, bool critical)const override;
};


class AllyTeamHealExample : public Hability {
public:
	AllyTeamHealExample(Character* caster) :Hability(caster) {

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

	void throwHability(Character* obj, bool critical)const override;
};


class SelfHealExample : public Hability {
public:
	SelfHealExample(Character* caster) :Hability(caster) {

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

	void throwHability(Character* obj, bool critical)const override;
};


class AllyTeamAttackExample : public Hability {
public:
	AllyTeamAttackExample(Character* caster) :Hability(caster) {

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

	void throwHability(Character* obj, bool critical)const override;
};

//-----------------------------------------------------------------------------

class WindBurst : public Hability {
public:
	WindBurst(Character* caster) :Hability(caster) {

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

	void throwHability(Character* obj, bool critical)const override;
};

class WindSlash : public Hability {
public:
	WindSlash(Character* caster) :Hability(caster) {

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

	void throwHability(Character* obj, bool critical)const override;
};

class RockPillar : public Hability {
public:
	RockPillar(Character* caster) :Hability(caster) {

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

	void throwHability(Character* obj, bool critical)const override;
};

class ToxicShadow : public Hability {
public:
	ToxicShadow(Character* caster) :Hability(caster) {

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

	void throwHability(Character* obj, bool critical)const override;
};

class Tsunami : public Hability {
public:
	Tsunami(Character* caster) :Hability(caster) {

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

	void throwHability(Character* obj, bool critical)const override;
};

class DivineProtection : public Hability {
public:
	DivineProtection(Character* caster) :Hability(caster) {

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

	void throwHability(Character* obj, bool critical)const override;
};

class Flash : public Hability {
public:
	Flash(Character* caster) :Hability(caster) {

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

	void throwHability(Character* obj, bool critical)const override;
};

class Freeze : public Hability {
public:
	Freeze(Character* caster) :Hability(caster) {

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

	void throwHability(Character* obj, bool critical)const override;
};
class Whirlpool : public Hability {
public:
	Whirlpool(Character* caster) :Hability(caster) {

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

	void throwHability(Character* obj, bool critical)const override;
};
class LightBeam : public Hability {
public:
	LightBeam(Character* caster) :Hability(caster) {

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

	void throwHability(Character* obj, bool critical)const override;
};
class DarkVortex : public Hability {
public:
	DarkVortex(Character* caster) :Hability(caster) {

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

	void throwHability(Character* obj, bool critical)const override;
};

class FireArrow : public Hability {
public:
	FireArrow(Character* caster) :Hability(caster) {

		level = 4;
		_mana = 0;
		_name = "Fire Arrow";
		_description = "Quema, a hace 1d8 a un enemigo frente a salvacion DEX (y reduce DEX)";

		_damageType = FIRE;
		_habilityType = ATTACK;
		_mod = INT;
		_obj = SINGLEENEMY;
	}

	static Hability_Id id() { return FIREARROW; }

	void throwHability(Character* obj, bool critical)const override;
};


class Lighten: public Hability {
public:
	Lighten(Character* caster) :Hability(caster) {

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

	void throwHability(Character* obj, bool critical)const override;
};
class Strengthen : public Hability {
public:
	Strengthen(Character* caster) :Hability(caster) {

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

	void throwHability(Character* obj, bool critical)const override;
};
class Toughen : public Hability {
public:
	Toughen(Character* caster) :Hability(caster) {

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

	void throwHability(Character* obj, bool critical)const override;
};
class Meditate: public Hability {
public:
	Meditate(Character* caster) :Hability(caster) {

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

	void throwHability(Character* obj, bool critical)const override;
};

class BloodThirst : public Hability {
public:
	BloodThirst(Character* caster) :Hability(caster) {

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

	void throwHability(Character* obj, bool critical)const override;
};

class Sacrifice : public Hability {
public:
	Sacrifice(Character* caster) :Hability(caster) {

		level = 4;
		_mana = 0;
		_name = "Sacrificio";
		_description = "Dame tu vida, a hace 1d8 a un enemigo frente a salvacion DEX x1.5 ,pero recibe daño de retroceso";

		_damageType = LIGHT;
		_habilityType = ATTACK;
		_mod = INT;
		_obj = SINGLEENEMY;
	}

	static Hability_Id id() { return SACRIFICE; }

	void throwHability(Character* obj, bool critical)const override;
};


#pragma endregion

#pragma region CONDITION

enum Conditions_Id {
	EJEMPLODAÑOPORTURNO,
	_lastConditionId_
};

class Condition {
protected:
	std::string _name = "DefaultName";
	std::string _description = "DefaultDescription";

	int _turnsLeft = 0;
	int _turns = 0;
	int _stack = 1;

	Character* _objective;
	Character* _caster;

public:

	Condition() :_caster(nullptr), _objective(nullptr) {}

	Condition(Character* caster, Character* objective) :_caster(caster), _objective(objective) {
	}

	virtual void init() = 0;

	virtual bool onTurnStarted() = 0;

	int getTurnsLeft() { return _turnsLeft; }

	void resetTurns() { _turnsLeft = _turns; }

	void addStack() { _stack++; }

	virtual Conditions_Id getId() { return id(); }

	static Conditions_Id id() { return _lastConditionId_; }
};


class EjemploDañoPorTurno : public Condition {
public:
	EjemploDañoPorTurno(Character* caster, Character* objective) :Condition(caster, objective) {
		_name = "Ejemplo de daño cada turno";
		_description = "Hace 1 de daño cada turno, durante 3 turnos";
		_turns = 3;
		resetTurns();
	}

	virtual void init();

	virtual bool onTurnStarted();

	virtual Conditions_Id getId() { return id(); }

	static Conditions_Id id() { return EJEMPLODAÑOPORTURNO; }
};

#pragma endregion