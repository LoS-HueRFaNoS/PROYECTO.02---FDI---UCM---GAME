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

	obj->addCondition<EjemploDañoPorTurnoBegin>(_caster);
}

void SingleTargetHealxample::throwHability(Character* obj, bool critical) const
{
	int healing = throwDice(2 + (2 * critical), 5, true);

	obj->recieveHealing(healing);

	obj->addCondition<EjemploRevivirMuerte>(_caster);
}

void AllyTeamHealExample::throwHability(Character* obj, bool critical) const
{
	int healing = throwDice(1 + critical, 5, true);

	obj->recieveHealing(healing);

	obj->addCondition<EjemploCuracionFinalTurno>(_caster);
}

void SelfHealExample::throwHability(Character* obj, bool critical) const
{
	int healing = throwDice(1 + critical, 8, true);

	obj->recieveHealing(healing);

	obj->addCondition<EjemploReduccionAtaque>(_caster);
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

void Whirlpool::throwHability(Character* obj, bool critical) const //hay que mirar que hacer con el debuff y ajustar el ataque
{
	int damage = throwDice(1 + critical, 8, true);

	damage = obj->savingThrow(10 + _caster->getMod(_mod), DEX) ? damage / 2 : damage;

	obj->recieveDamage(damage, _damageType);

	//obj->recieveBuff(-3, STR);						// ESTO COMO UN ESTADO
}

void LightBeam::throwHability(Character* obj, bool critical) const //hay que mirar que hacer con el debuff y ajustar el ataque
{
	int damage = throwDice(1 + critical, 8, true);

	damage = obj->savingThrow(10 + _caster->getMod(_mod), DEX) ? damage / 2 : damage;

	obj->recieveDamage(damage, _damageType);

	//obj->recieveBuff(-3, STR);						// ESTO COMO UN ESTADO
}

void DarkVortex::throwHability(Character* obj, bool critical) const //hay que mirar que hacer con el debuff y ajustar el ataque
{
	int damage = throwDice(1 + critical, 8, true);

	damage = obj->savingThrow(10 + _caster->getMod(_mod), DEX) ? damage / 2 : damage;

	obj->recieveDamage(damage, _damageType);

	//obj->recieveBuff(-3, STR);						// ESTO COMO UN ESTADO
}


void Lighten::throwHability(Character* obj, bool critical) const
{
	mainStat buffedStat = DEX;
	
	obj->recieveBuff(2, buffedStat);
}

void Strengthen::throwHability(Character* obj, bool critical) const
{
	mainStat buffedStat = STR;

	obj->recieveBuff(2, buffedStat);
}

void Toughen::throwHability(Character* obj, bool critical) const
{
	mainStat buffedStat = CON;

	obj->recieveBuff(2, buffedStat);
}

void Meditate::throwHability(Character* obj, bool critical) const
{
	mainStat buffedStat = INT;

	obj->recieveBuff(2, buffedStat);
}

void BloodThirst::throwHability(Character* obj, bool critical) const //hay que mirar que hacer con el debuff y ajustar el ataque
{
	Weapon* w = static_cast<Hero*>(_caster)->getWeapon();

	int damage = throwDice(w->getNDice(), w->getDamage(), true);

	damage = obj->savingThrow(10 + _caster->getMod(_mod), DEX) ? damage / 2 : damage;

	obj->recieveDamage(damage, _damageType);

	//obj =_caster;									NO BORREIS LA REFERENCIA AL OBJETIVO USAD DIRECTAMENTE EL CASTER

	_caster->recieveHealing(damage / 3);
}

void Sacrifice::throwHability(Character* obj, bool critical) const //hay que mirar que hacer con el debuff y ajustar el ataque
{
	Weapon* w = static_cast<Hero*>(_caster)->getWeapon();

	int damage = throwDice(w->getNDice(), w->getDamage(), true);

	damage = obj->savingThrow(10 + _caster->getMod(_mod), DEX) ? damage / 2 : damage;

	obj->recieveDamage(damage * 1.5, _damageType);

	//obj =_caster;									NO BORREIS LA REFERENCIA AL OBJETIVO USAD DIRECTAMENTE EL CASTER

	_caster->recieveDamage(damage / 5,_damageType);
}

void DoubleShot::throwHability(Character* obj, bool critical) const 
{
	Weapon* w = static_cast<Hero*>(_caster)->getWeapon();

	int damage = throwDice(w->getNDice(), w->getDamage(), true);

	damage = obj->savingThrow(10 + _caster->getMod(_mod), DEX) ? damage / 2 : damage;

	obj->recieveDamage(damage, _damageType);
	
	obj->recieveDamage(damage / 2, _damageType);
}

void ThrowingAxes::throwHability(Character* obj, bool critical) const //revisar que se tiran el numero correcto de dados
{
	Weapon* w = static_cast<Hero*>(_caster)->getWeapon();

	int damage = throwDice(3, w->getDamage(), true);

	damage = obj->savingThrow(10 + _caster->getMod(_mod), DEX) ? damage / 2 : damage;

	obj->recieveDamage(damage, _damageType);

}

void WindSong::throwHability(Character* obj, bool critical) const
{
	mainStat buffedStat = DEX;

	obj->recieveBuff(2, buffedStat);
}

void GladiatorBallad::throwHability(Character* obj, bool critical) const
{
	mainStat buffedStat = STR;

	obj->recieveBuff(2, buffedStat);
}

void HeavyStrike::throwHability(Character* obj, bool critical) const
{
	Weapon* w = static_cast<Hero*>(_caster)->getWeapon();

	int damage = throwDice(w->getNDice(), w->getDamage(), true);

	damage = obj->savingThrow(10 + _caster->getMod(_mod), DEX) ? damage / 2 : damage;

	obj->recieveDamage(damage + 3, _damageType);

}

void SmokeArrow::throwHability(Character* obj, bool critical) const //hay que testear si es adecuado el defuff 
																	//y si dura el numero correcto de turnos
{
	int buff = throwDice(1 + critical, 6, true);

	buff = obj->savingThrow(10 + _caster->getMod(_mod), DEX) ? buff / 2 : buff;

	//obj->recieveDamage(damage, _damageType);
	obj->recieveBuff(-buff, DEX);
}

#pragma endregion

#pragma region CONDITION

void EjemploDañoPorTurnoBegin::init()
{
	cout << _objective->name() << " tiene sangrado!!!" << endl;
	_objective->recieveDamage(throwDice(1, 3, true), PIERCE);
}

bool EjemploDañoPorTurnoBegin::onTurnStarted()
{
	cout << "Sangrado: ";
	_objective->recieveDamage(throwDice(_stack, 3, true), PIERCE);
	if (!--_counter) {
		cout << "SE ACABO EL DANYO" << endl;
		return false;
	}
	cout << "TURNOS RESTANTES: " << _counter << endl;
	return true;
}

void EjemploCuracionFinalTurno::init()
{
	cout << _objective->name() << " se curará cada final de turno!!!" << endl;
}

bool EjemploCuracionFinalTurno::onTurnEnd()
{
	cout << "Curación: ";
	_objective->recieveHealing(throwDice(_stack, 3, true));
	if (!--_counter) {
		cout << "SE ACABO LA CURASAO" << endl;
		return false;
	}
	cout << "TURNOS RESTANTES: " << _counter << endl;
	return true;
}

void EjemploReduccionAtaque::init()
{
	cout << _objective->name() << " recivirá la mitad del danyo el siguiente ataque" << endl;
}

bool EjemploReduccionAtaque::onAttackRecieved(int& damage)
{
	damage = damage / 2;
	return false;
}

void EjemploRevivirMuerte::init()
{
	cout << _objective->name() << " revivira con 5 de vida al morir" << endl;
}

bool EjemploRevivirMuerte::onDeath()
{
	cout << _objective->name() << "revives!!" << endl;
	_objective->recieveHealing(5);
	return false;
}

#pragma endregion