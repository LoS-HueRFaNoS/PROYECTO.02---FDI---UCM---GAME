// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
//

#include "checkML.h"
#include "Error.h"
#include "acedpol_pacman.h"
#include <iostream>

#pragma region METODOS_PROJECT

int main(int argc, char* argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	try
	{
		cout << "EJECUTANDO APLICACION..." << endl;
		acedPac().run();
	}
	catch (Error& e) { cout << e.what() << endl; }
	cout << "SALIENDO DE LA APLICACION..." << endl;
	return 0;
}


















// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
#pragma endregion