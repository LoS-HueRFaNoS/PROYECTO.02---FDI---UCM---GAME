#ifndef _CHARACTER_
#define _CHARACTER_
#include "Component.h"
#include "RPGLogic.h"
#include "json/json.h"

class Character : public Component
{
public:

	struct Ataque {
		int daño;
		int dados;
		RpgLogic::damageType type;
		RpgLogic::modStat mod;
	};

	struct  Stat
	{
		int value;

		int getMod() {
			return (value - 10) / 2;
		}
	};

	struct Weaknesses {
		// Daños físicos
		float blunt;
		float piercing;
		float slash;
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

    //Nombre (Clase del heroe o tipo de criatura) 
    string name;

    //Caracteristicas 
	Stat strength;
	Stat dexterity;
	Stat constitution;
	Stat inteligence;
    
	//Salud
	int hitPoints;
	//Mana
	int manaPoints;
	//Clase de armadura
	int armorClass;
    
	//Debilidades
	Weaknesses weaknesses;

public:



};






#endif
