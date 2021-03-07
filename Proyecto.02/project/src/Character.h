#pragma once
#include "Component.h"





class Character : public Component
{
public:

	struct  Stat
	{
		int value;

		int getMod() {
			return (value - 10) / 2;
		}
	};
	struct Weaknesses {
		// Daños físicos
		float contundente;
		float perforante;
		float cortante;
		// Daños elementales
		float fire;
		float water;
		float ice;
		float earth;
		float wind;
		float light;
		float dark;

		float getWeakness() {	// Devolver la resistencia en función de tipo o parametro

		}
	};
private:
	Stat strength;
	Stat dexterity;
	Stat constitution;
	Stat inteligence;

	int hitPoints;
	int manaPoints;
	int armorClass;

	Weaknesses weaknesses;

};

