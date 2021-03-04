// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
//

#include "textureMachine.h"
#include "windowAPP.h"
#include <fstream>
#include <iostream>

#pragma region METODOS_TEXTURE_MACHINE

textureMachine::~textureMachine()
{
	for (uint i = 0; i < cont; ++i) { delete textures[i]; };
	delete[] textures;
}

void textureMachine::load(ifstream& file)
{
	if (!file.is_open()) throw FileNotFoundError(texturesFile);
	else {
		// variables
		string path;
		string filename;
		int numRows;
		int numCols;
		// inicio
		capacity = cont = 0;
		file >> capacity; // num_textures
		textures = new Texture * [capacity];
		// bucle
		while (cont < capacity && !file.fail()) {
			file >> path;
			file >> filename;
			file >> numRows;
			file >> numCols;

			// anade cada textura
			try { textures[cont] = new Texture(acedWinApp().getRenderer(), path + filename, numRows, numCols); }
			catch (Error& e) { cout << e.what() << endl; }
			++cont;

		}
		file.close();
	}
}

textureMachine::textureMachine()
{
	ifstream file;
	file.open(texturesFile);
	SDL_Renderer* render = acedWinApp().getRenderer();
	load(file);
}

















// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
#pragma endregion