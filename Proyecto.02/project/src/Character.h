#ifndef _CHARACTER_
#define _CHARACTER_
#include "Component.h"
#include "RPGLogic.h"

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
		float _blunt;
		float _piercing;
		float _slash;
		// Daños elementales
		float _fire;
		float _water;
		float _ice;
		float _earth;
		float _wind;
		float _light;
		float _dark;

		Weaknesses() {
			_blunt = 0;
			_piercing = 0;
			_slash = 0;
			_fire = 0;
			_water = 0;
			_ice = 0;
			_earth = 0;
			_wind = 0;
			_light = 0;
			_dark = 0;
		}

		Weaknesses(float blunt, float piercing, float slash,
			float fire, float water, float ice, float earth,
			float wind, float light, float dark) {
			_blunt = blunt;
			_piercing = piercing;
			_slash = slash;
			_fire = fire;
			_water = water;
			_ice = ice;
			_earth = earth;
			_wind = wind;
			_light = light;
			_dark = dark;
		}

		float getWeakness(RpgLogic::damageType type) {	// Devolver la resistencia en función de tipo o parametro
			switch (type)
			{
			case RpgLogic::BLUNT:
				return _blunt;
				break;
			case RpgLogic::PIERCE:
				return _piercing;
				break;
			case RpgLogic::SLASH:
				return _slash;
				break;
			case RpgLogic::FIRE:
				return _fire;
				break;
			case RpgLogic::WATER:
				return _water;
				break;
			case RpgLogic::ICE:
				return _ice;
				break;
			case RpgLogic::EARTH:
				return _earth;
				break;
			case RpgLogic::WIND:
				return _wind;
				break;
			case RpgLogic::LIGHT:
				return _light;
				break;
			case RpgLogic::DARK:
				return _dark;
				break;
			default:
				break;
			}
		}
	};

private:

    //Nombre (Clase del heroe o tipo de criatura) 
    string name = "DefaultClass";

    //Caracteristicas 
	Stat strength = { 10 };
	Stat dexterity = { 10 };
	Stat constitution = { 10 };
	Stat inteligence = { 10 };
    
	//Salud
	int hitPoints = 10;
	//Mana
	int manaPoints = 10;
	//Clase de armadura
	int armorClass = 10;
    
	//Debilidades
	Weaknesses weaknesses;

public:

	Character() :Component(ecs::Character),
	weaknesses(){
	}

	void loadFromJson(RpgLogic::characterTemplate t);
};
#endif
