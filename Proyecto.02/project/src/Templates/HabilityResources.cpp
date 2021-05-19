#include "HabilityResources.h"
#include "../GameObjects/Character.h"



#pragma region HABILITY

void Fireball::throwHability(Character* obj, bool critical) const
{
	int damage = throwDice(8 + 8 * critical, 6, true);

	damage = obj->savingThrow(10 + _caster->getMod(_mod), ms::DEX) ? damage / 2 : damage;

	obj->recieveDamage(damage, _damageType, _caster);
}


void LightAttack::throwHability(Character* obj, bool critical) const
{
	Weapon* w = _caster->getWeapon();

	int damage = throwDice(w->getNDice(), w->getDamage(), true);

	obj->recieveDamage(damage, w->getDamageType(), _caster);
}


void BloodyStrike::throwHability(Character* obj, bool critical) const
{
	int damage = throwDice(1 + critical, 5, true);

	obj->recieveDamage(damage, _damageType, _caster);

	obj->addCondition<Bleeding>(_caster);
}

void HealingWord::throwHability(Character* obj, bool critical) const
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

void WindBurst::throwHability(Character* obj, bool critical) const
{
	int damage = throwDice(8 + 8 * critical, 6, true);

	damage = obj->savingThrow(10 + _caster->getMod(_mod), ms::DEX) ? damage / 2 : damage;

	obj->recieveDamage(damage, _damageType, _caster);
}

void RockPillar::throwHability(Character* obj, bool critical) const
{
	int damage = throwDice(8 + 8 * critical, 6, true);

	damage = obj->savingThrow(10 + _caster->getMod(_mod), ms::DEX) ? damage / 2 : damage;

	obj->recieveDamage(damage, _damageType, _caster);
}

void ToxicShadow::throwHability(Character* obj, bool critical) const
{
	int damage = throwDice(8 + 8 * critical, 6, true);

	damage = obj->savingThrow(10 + _caster->getMod(_mod), ms::DEX) ? damage / 2 : damage;

	obj->recieveDamage(damage, _damageType, _caster);
}

void WindSlash::throwHability(Character* obj, bool critical) const
{
	int damage = throwDice(8 + 8 * critical, 6, true);

	damage = obj->savingThrow(10 + _caster->getMod(_mod), ms::DEX) ? damage / 2 : damage;

	obj->recieveDamage(damage, _damageType, _caster);
}

void Tsunami::throwHability(Character* obj, bool critical) const
{
	int damage = throwDice(8 + 8 * critical, 6, true);

	damage = obj->savingThrow(10 + _caster->getMod(_mod), ms::DEX) ? damage / 2 : damage;

	obj->recieveDamage(damage, _damageType, _caster);
	obj->addCondition<BuffStats>(_caster ,-3, ms::STR, _name, _description);
}

void DivineProtection::throwHability(Character* obj, bool critical) const
{
	mainStat buffedStat = ms::CON;
	int buff = throwDice(1 + critical, 8, true);

	obj->addCondition<BuffStats>(_caster,buff, ms::CON, _name, _description);
}

void Flash::throwHability(Character* obj, bool critical) const
{
	int damage = throwDice(8 + 8 * critical, 6, true);

	damage = obj->savingThrow(10 + _caster->getMod(_mod), ms::DEX) ? damage / 2 : damage;

	obj->recieveDamage(damage, _damageType, _caster);
}

void Freeze::throwHability(Character* obj, bool critical) const //hay que mirar que hacer con el debuff y ajustar el ataque
{
	int damage = throwDice(1 + critical, 8, true);

	damage = obj->savingThrow(10 + _caster->getMod(_mod), ms::DEX) ? damage / 2 : damage;

	obj->recieveDamage(damage, _damageType, _caster);
	obj->addCondition<BuffStats>(_caster ,-3, ms::DEX, _name, _description);
}

void Whirlpool::throwHability(Character* obj, bool critical) const //hay que mirar que hacer con el debuff y ajustar el ataque
{
	int damage = throwDice(1 + critical, 8, true);

	damage = obj->savingThrow(10 + _caster->getMod(_mod), ms::DEX) ? damage / 2 : damage;

	obj->recieveDamage(damage, _damageType, _caster);

	obj->addCondition<BuffStats>(_caster ,-3, ms::STR, _name, _description);						// ESTO COMO UN ESTADO
}

void LightBeam::throwHability(Character* obj, bool critical) const //hay que mirar que hacer con el debuff y ajustar el ataque
{
	int damage = throwDice(1 + critical, 8, true);

	damage = obj->savingThrow(10 + _caster->getMod(_mod), ms::DEX) ? damage / 2 : damage;

	obj->recieveDamage(damage, _damageType, _caster);

	obj->addCondition<BuffStats>(_caster ,-3, ms::DEX, _name, _description);						// ESTO COMO UN ESTADO
}

void DarkVortex::throwHability(Character* obj, bool critical) const //hay que mirar que hacer con el debuff y ajustar el ataque
{
	int damage = throwDice(1 + critical, 8, true);

	damage = obj->savingThrow(10 + _caster->getMod(_mod), ms::DEX) ? damage / 2 : damage;

	obj->recieveDamage(damage, _damageType, _caster);

	obj->addCondition<BuffStats>(_caster, -3, ms::DEX, _name, _description);						// ESTO COMO UN ESTADO
}

void FireArrow::throwHability(Character* obj, bool critical) const
{
	int damage = throwDice(1 + critical, 8, true);
	damage = obj->savingThrow(10 + _caster->getMod(_mod), ms::DEX) ? damage / 2 : damage;
	obj->recieveDamage(damage, _damageType);
	obj->addCondition<BuffStats>(_caster, -3, ms::DEX, _name, _description);
}

void Lighten::throwHability(Character* obj, bool critical) const
{
	obj->addCondition<BuffStats>(_caster,2, ms::DEX, _name, _description);

}

void Strengthen::throwHability(Character* obj, bool critical) const
{
	obj->addCondition<BuffStats>(_caster,2, ms::STR, _name, _description);
}

void Toughen::throwHability(Character* obj, bool critical) const
{
	obj->addCondition<BuffStats>(_caster,2, ms::CON, _name, _description);
}

void Meditate::throwHability(Character* obj, bool critical) const
{
	obj->addCondition<BuffStats>(_caster,2, ms::INT, _name, _description);
}

void BloodThirst::throwHability(Character* obj, bool critical) const //hay que mirar que hacer con el debuff y ajustar el ataque
{
	Weapon* w = _caster->getWeapon();

	int damage = throwDice(w->getNDice(), w->getDamage(), true);

	damage = obj->savingThrow(10 + _caster->getMod(_mod), ms::DEX) ? damage / 2 : damage;

	obj->recieveDamage(damage, _damageType, _caster);

	//obj =_caster;									NO BORREIS LA REFERENCIA AL OBJETIVO USAD DIRECTAMENTE EL CASTER

	_caster->recieveHealing(damage / 3);
}

void Sacrifice::throwHability(Character* obj, bool critical) const //hay que mirar que hacer con el debuff y ajustar el ataque
{
	Weapon* w = _caster->getWeapon();

	int damage = throwDice(w->getNDice(), w->getDamage(), true);

	damage = obj->savingThrow(10 + _caster->getMod(_mod), ms::DEX) ? damage / 2 : damage;

	obj->recieveDamage(int(damage * 1.5), _damageType, _caster);

	//obj =_caster;									NO BORREIS LA REFERENCIA AL OBJETIVO USAD DIRECTAMENTE EL CASTER

	_caster->recieveDamage(damage / 5, _damageType, _caster);
}

void DoubleShot::throwHability(Character* obj, bool critical) const
{
	Weapon* w =_caster->getWeapon();

	int damage = throwDice(w->getNDice(), w->getDamage(), true);

	damage = obj->savingThrow(10 + _caster->getMod(_mod), ms::DEX) ? damage / 2 : damage;

	obj->recieveDamage(damage, _damageType, _caster);

	obj->recieveDamage(damage / 2, _damageType, _caster);
}

void ThrowingAxes::throwHability(Character* obj, bool critical) const //revisar que se tiran el numero correcto de dados
{
	Weapon* w = _caster->getWeapon();

	int damage = throwDice(3, w->getDamage(), true);

	damage = obj->savingThrow(10 + _caster->getMod(_mod), ms::DEX) ? damage / 2 : damage;

	obj->recieveDamage(damage, _damageType, _caster);

}

void HeavyStrike::throwHability(Character* obj, bool critical) const
{
	Weapon* w = _caster->getWeapon();

	int damage = throwDice(w->getNDice(), w->getDamage(), true) * 2;

	if (obj->savingThrow(5 + _caster->getMod(_mod), ms::DEX))
		cout << "You missed your heavy hit" << endl;
	else
		obj->recieveDamage(damage, _damageType, _caster);

}

void SmokeArrow::throwHability(Character* obj, bool critical) const //hay que testear si es adecuado el defuff 
																	//y si dura el numero correcto de turnos
{
	int buff = throwDice(1 + critical, 6, true);

	buff = obj->savingThrow(10 + _caster->getMod(_mod), ms::DEX) ? buff / 2 : buff;

	//obj->recieveDamage(damage, _damageType);
	obj->addCondition<BuffStats>(_caster,buff, ms::DEX, _name, _description);
}

void Morph::throwHability(Character* obj, bool critical) const //hay que testear si es adecuado el defuff 
																	//y si dura el numero correcto de turnos
{
	obj->recieveBuff(15, ms::STR);
	obj->recieveBuff(-5, ms::STR);
	obj->recieveBuff(5, ms::STR);
	obj->recieveBuff(-15, ms::STR);
}

void ReverseMorph::throwHability(Character* obj, bool critical) const //hay que testear si es adecuado el defuff 
																	//y si dura el numero correcto de turnos
{
	obj->recieveBuff(-15, ms::STR);
	obj->recieveBuff(5, ms::STR);
	obj->recieveBuff(-5, ms::STR);
	obj->recieveBuff(15, ms::STR);
}

void RainOfDaggers::throwHability(Character* obj, bool critical) const //testear si esta bien el daño
{
	Weapon* w = _caster->getWeapon();

	int numDaggers = throwDice(1, 10, true);

	int damage = throwDice(w->getNDice(), w->getDamage(), true);

	damage = obj->savingThrow(10 + _caster->getMod(_mod), ms::DEX) ? damage / 2 : damage;

	obj->recieveDamage((damage * numDaggers) / 5, _damageType, _caster);

}

void RockProjectiles::throwHability(Character* obj, bool critical) const //testear si funcionan correctamente los 3 proyectiles
{
	Weapon* w = _caster->getWeapon();

	int damage = throwDice(w->getNDice(), w->getDamage(), true);
	for (int i = 0; i < 3; i++) {
		damage = obj->savingThrow(10 + _caster->getMod(_mod), ms::DEX) ? damage / 2 : damage;

		obj->recieveDamage(damage, _damageType, _caster);
	}
}

void TrickShot::throwHability(Character* obj, bool critical) const //cambiarlo si al final hacemos lo de comprobar 2 tiradas de ataque para que acierte
{
	Weapon* w = _caster->getWeapon();

	int damage = throwDice(w->getNDice(), w->getDamage(), true);

	damage = obj->savingThrow(10 + _caster->getMod(_mod), ms::DEX) ? damage / 2 : damage;

	obj->recieveDamage(damage * 3, _damageType, _caster);

}

void GladiatorBallad::throwHability(Character* obj, bool critical) const
{
	int strUp = 3;


	obj->addCondition<BuffStats>(_caster,strUp, ms::STR, _name, _description);
}

void WindSong::throwHability(Character* obj, bool critical) const
{
	int velUp = 3;

	obj->addCondition<BuffStats>(_caster,velUp, ms::DEX, _name, _description);
}

void Determination::throwHability(Character* obj, bool critical) const
{
	obj->addCondition<DeterminationCond>(_caster);
}

void Blessing::throwHability(Character* obj, bool critical) const {
	obj->removeBadConditions();
}

#pragma endregion

#pragma region CONDITION

void Bleeding::init()
{
	cout << _objective->name() << " tiene sangrado!!!" << endl;
	_objective->recieveDamage(throwDice(1, 3, true), damTy::PIERCE);
}

bool Bleeding::onTurnStarted()
{
	cout << "Sangrado: ";
	_objective->recieveDamage(throwDice(_stack, 3, true), damTy::PIERCE);
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

bool EjemploReduccionAtaque::onAttackRecieved(int& damage, Character* attacker)
{
	damage = damage / 2;
	return false;
}

void EjemploRevivirMuerte::init()
{
	cout << _objective->name() << " revivira con 5 de vida al morir" << endl;
}

bool EjemploRevivirMuerte::onDeath(Character* attacker)
{
	cout << _objective->name() << "revives!!" << endl;
	_objective->recieveHealing(5);
	return false;
}

void BuffStats::init()
{
	//cout << _objective->name() << "aumenta la fuerza 3 puntos durante 3 turnos a todos" << endl;
	_objective->recieveBuff(value, statMod);
}

bool BuffStats::onTurnStarted()
{
	cout << "Buffo activo: ";

	if (!--_counter) {
		cout << "Se acabó el bufo" << endl;
		_objective->recieveBuff(-value, statMod);
		return false;
	}
	cout << "TURNOS RESTANTES: " << _counter << endl;
	return true;
}

void DeterminationCond::init()
{
	cout << _objective->name() << " revivira con 1 de vida al morir" << endl;
}

bool DeterminationCond::onDeath(Character* attacker)
{
	cout << _objective->name() << " revives!!" << endl;
	_objective->recieveHealing(1);
	return false;
}

#pragma endregion

