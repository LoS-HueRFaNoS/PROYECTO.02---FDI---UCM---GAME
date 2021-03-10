#include <iostream>
#include "json.hpp"

using json = nlohmann::json;

json hero = {

	{"warrior", {

	//Stats
	{"strength Min", 15},
	{"strength Max", 21},

	{"constitution Min", 5},
	{"constitution Max", 11},

	{"dexterity Min", 10},
	{"dexterity Max", 16},

	{ "intelligence Min", 1 },
	{ "intelligence Max", 6 },

	//Puntos de salud
    { "hitPoints", 10 },
    //Puntos de mana
    { "manaPoints", 8 },

    //Debilidades
    /*{"weaknesses",
	{"blunt", 0},
	{"piercing", 0},
	{"slash", 0},
	{"fire", 0},
	{"water", 0},
	{"ice", 0},
	{"earth", 0},
	{"wind", 0},
	{"light", 0},
	{"dark", 0}},*/

	//Listado de armas y armaduras 
	//que puede usar
}},

	{ "wizard", {

	//Stats
	{"strength Min", 1},
	{"strength Max", 6},

	{"constitution Min", 10},
	{"constitution Max", 16},

	{"dexterity Min", 5},
	{"dexterity Max", 11},

	{"intelligence Min", 15},
	{"intelligence Max", 21},

	//Puntos de salud
	{"hitPoints", 6},
	//Puntos de mana
	{"manaPoints", 12},

	//Debilidades
	/*{"weaknesses",
		{"blunt", 0},
		{"piercing", 0},
		{"slash", 0},
		{"fire", 0},
		{"water", 0},
		{"ice", 0},
		{"earth", 0},
		{"wind", 0},
		{"light", 0},
		{"dark", 0}},*/

		//Listado de armas y armaduras 
		//que puede usar
}},

    {"ranger", {

	//Stats
	{"strength Min", 10},
	{"strength Max", 16},

	{"constitution Min", 1},
	{"constitution Max", 6},

	{"dexterity Min", 15},
	{"dexterity Max", 21},

	{"intelligence Min", 5},
	{"intelligence Max", 11},

	//Puntos de salud
	{"hitPoints", 8},
	//Puntos de mana
	{"manaPoints", 10},

	//Debilidades
	/*{"weaknesses",
		{"blunt", 0},
		{"piercing", 0},
		{"slash", 0},
		{"fire", 0},
		{"water", 0},
		{"ice", 0},
		{"earth", 0},
		{"wind", 0},
		{"light", 0},
		{"dark", 0}},*/

		//Listado de armas y armaduras 
		//que puede usar
}}
};
