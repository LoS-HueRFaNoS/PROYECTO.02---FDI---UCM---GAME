#include "Character.h"
#include <fstream>
#include <iostream>
#include "jute.h"

void Character::loadFromJson(characterTemplate t)
{
	// Cargamos el archivo de tipo json ( la ruta empieza a buscar desde la carpeta del vcxproj)
	ifstream in("pruebas.json");


	// Guardamos todo lo que se puede leer del archivo en un string
	string str = "";
	string tmp;
	while (getline(in, tmp)) str += tmp;


	// El parser lo transforma de string a un Jvalue del que podremos sacar la información
	jute::jValue v = jute::parser::parse(str);

	// Buscamos las stats en el json dentro de nuestro heroe "t" y asignamos un valor aleatorio entre los valores dados
	for (int i = 0; i < _LastStatId_; i++) {
		int min = v["Heroes"][t]["Stats"][i]["Min"].as_int();
		int max = v["Heroes"][t]["Stats"][i]["Max"].as_int();
		_stats[i].value = game_->getRandGen()->nextInt(min, max + 1);
	}

	// Igual con la vida y el mana
	hitPoints = v["Heroes"][t]["HitPoints"].as_int();
	manaPoints = v["Heroes"][t]["HitPoints"].as_int();

	// Guardamos las debilidades en un vector para luego inicializarlas
	vector<float> weak = vector<float>();
	for (int i = 0; i < _LastTypeId_; i++) {
		weak.push_back((float)v["Heroes"][t]["Weaknesses"][i]["Value"].as_double());
	}
	weaknesses = Weaknesses(weak);

}
