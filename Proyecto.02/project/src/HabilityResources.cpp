#include "HabilityResources.h"
#include "Character.h"


#pragma region HABILITY

void Fireball::throwHability(Character* obj, bool critical) const
{
	int damage = throwDice(8 + 8 * critical, 6, true);

	damage = obj->savingThrow(10 + _caster->getMod(_mod), DEX) ? damage / 2 : damage;

	obj->recieveDamage(damage, _damageType);
}


void LightAttack::throwHability(Character* obj, bool critical) const
{
	Weapon* w = static_cast<Hero*>(_caster)->getWeapon();

	int damage = throwDice(w->getNDice(), w->getDamage(), true);

	obj->recieveDamage(damage, w->getDamageType());
}


void SingleTargetAttackExample::throwHability(Character* obj, bool critical) const
{
	int damage = throwDice(1 + critical, 5, true);

	obj->recieveDamage(damage, _damageType);

	obj->addCondition<EjemploDañoPorTurno>(_caster);
}

void SingleTargetHealxample::throwHability(Character* obj, bool critical) const
{
	int healing = throwDice(2 + (2 * critical), 5, true);

	obj->recieveHealing(healing);
}

void AllyTeamHealExample::throwHability(Character* obj, bool critical) const
{
	int healing = throwDice(1 + critical, 5, true);

	obj->recieveHealing(healing);
}

void SelfHealExample::throwHability(Character* obj, bool critical) const
{
	int healing = throwDice(1 + critical, 8, true);

	obj->recieveHealing(healing);
}

void AllyTeamAttackExample::throwHability(Character* obj, bool critical) const
{
	int damage = throwDice(2 + 2 * critical, 4, true);

	obj->recieveDamage(damage, _damageType);
}


void WindBurst::throwHability(Character* obj, bool critical) const
{
	int damage = throwDice(8 + 8 * critical, 6, true);

	damage = obj->savingThrow(10 + _caster->getMod(_mod), DEX) ? damage / 2 : damage;

	obj->recieveDamage(damage, _damageType);
}

void RockPillar::throwHability(Character* obj, bool critical) const
{
	int damage = throwDice(8 + 8 * critical, 6, true);

	damage = obj->savingThrow(10 + _caster->getMod(_mod), DEX) ? damage / 2 : damage;

	obj->recieveDamage(damage, _damageType);
}

void ToxicShadow::throwHability(Character* obj, bool critical) const
{
	int damage = throwDice(8 + 8 * critical, 6, true);

	damage = obj->savingThrow(10 + _caster->getMod(_mod), DEX) ? damage / 2 : damage;

	obj->recieveDamage(damage, _damageType);
}

void WindSlash::throwHability(Character* obj, bool critical) const
{
	int damage = throwDice(8 + 8 * critical, 6, true);

	damage = obj->savingThrow(10 + _caster->getMod(_mod), DEX) ? damage / 2 : damage;

	obj->recieveDamage(damage, _damageType);
}

void Tsunami::throwHability(Character* obj, bool critical) const
{
	int damage = throwDice(8 + 8 * critical, 6, true);

	damage = obj->savingThrow(10 + _caster->getMod(_mod), DEX) ? damage / 2 : damage;

	obj->recieveDamage(damage, _damageType);
}

void DivineProtection::throwHability(Character* obj, bool critical) const
{
	mainStat buffedStat = CON;
	int buff = throwDice(1 + critical, 8, true);

	obj->recieveBuff(buff, CON);
}

void Flash::throwHability(Character* obj, bool critical) const
{
	int damage = throwDice(8 + 8 * critical, 6, true);

	damage = obj->savingThrow(10 + _caster->getMod(_mod), DEX) ? damage / 2 : damage;

	obj->recieveDamage(damage, _damageType);
}

void Freeze::throwHability(Character* obj, bool critical) const //hay que mirar que hacer con el debuff y ajustar el ataque
{
	int damage = throwDice(1 + critical, 8, true);

	damage = obj->savingThrow(10 + _caster->getMod(_mod), DEX) ? damage / 2 : damage;

	obj->recieveDamage(damage, _damageType);
	obj->recieveBuff(-3, DEX);
}

#pragma endregion

#pragma region CONDITION

void EjemploDañoPorTurno::init()
{
	cout << _objective->name() << " tiene sangrado!!!" << endl;
	_objective->recieveDamage(throwDice(1, 3, true), PIERCE);
}

bool EjemploDañoPorTurno::onTurnStarted()
{
	cout << "Sangrado: ";
	_objective->recieveDamage(throwDice(_stack, 3, true), PIERCE);
	if (!--_turnsLeft) {
		cout << "SE ACABO EL DAÑO" << endl;
		return false;
	}
	cout << "TURNOS RESTANTES: " << _turnsLeft << endl;
	return true;
}

#pragma endregion


