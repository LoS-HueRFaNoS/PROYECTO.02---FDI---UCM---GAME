#include "HabilityResources.h"
#include "Character.h"



void Hability::castHability(Character* caster, Character* obj)
{
	if (canCast()) {
		_nextCast = _cd;
		if (obj->checkHit(throwDice(1, 20) + caster->getMod(_mod)))
			throwHability(caster, obj);
		else
			cout << "Fallo - HabilityResources.cpp linea 13" << endl;
	}
	else
		cout << "Aun no puede castear quedan " << _nextCast << " turnos - HabilityResources.cpp linea 13" << endl;
}

// ---------------- EJEMPLO CON UNA BOLA DE FUEGO -----------------------

void Fireball::throwHability(Character* caster, Character* obj)
{
	int damage = throwDice(8, 6);

	damage = obj->savingThrow(10 + caster->getMod(_mod), DEX) ? damage / 2 : damage;

	obj->recieveDamage(damage, _type);
}

// ----------------------------------------------------------------------
