#include "ItemManager.h"

void ItemManager::init()
{
	loadJson(Resources::jsons_[Resources::Weapons].filename, weaponJson);
	loadJson(Resources::jsons_[Resources::Armors].filename, armorJson);
}

void ItemManager::loadJson(string json, jute::jValue& j)
{
	ifstream in(json);

	if (in.is_open()) {
		// Guardamos todo lo que se puede leer del archivo en un string
		string str = "";
		string tmp;
		while (getline(in, tmp)) str += tmp;

		in.close();

		// El parser lo transforma de string a un Jvalue del que podremos sacar la informaci�n
		j = jute::parser::parse(str);
	}
	else
		;	// HACER EL THROW
}
