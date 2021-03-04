// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
//

#pragma once
#ifndef TEXTURE_MACHINE_H_
#define TEXTURE_MACHINE_H_

#include "checkML.h"

#include "Texture.h"
#include "Error.h"
#include <list>
// inherits
#include "Singleton.h"

// palabras claves:
enum TextureName { WallTxt, CharactersTxt, FoodTxt, BurguerTxt, DoorTxt, CursorTxt, RetroFontTxt };
const string texturesFile = "../resources/data/textures.dat";

class textureMachine : public Singleton<textureMachine>
{
	friend Singleton<textureMachine>;
	textureMachine();						// constructor
private:
	Texture** textures;											// array dinámico de dinámicos
	uint cont, capacity;
	void load(ifstream& file);
public:
	~textureMachine();											// destructor

	Texture* getTexture(TextureName name) { return textures[name]; };
};

inline textureMachine& acedTxtMot() {
	return *textureMachine::instance();
}














// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
#endif