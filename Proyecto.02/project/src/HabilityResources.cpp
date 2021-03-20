#include "HabilityResources.h"
#include "Character.h"


// ---------------- EJEMPLO CON UNA BOLA DE FUEGO -----------------------

void Fireball::throwHability(Character* obj)
{
	int damage = throwDice(8, 6);

	damage = obj->savingThrow(10 + _caster->getMod(_mod), DEX) ? damage / 2 : damage;

	obj->recieveDamage(damage, _type);
}

// ----------------------------------------------------------------------
