// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
//

#include "acedpol_pacman.h"
#include "objectsMotor.h"
#include "logic_pacman.h"
#include "windowAPP.h"
#include <iostream>

#pragma region METODOS_ACEDPOL_PACMAN

acedpol_pacman::acedpol_pacman()
{
	int lvl = 1;
	do {
		cout << "Elige un nivel: ";
		cin >> lvl;
	} while (lvl < 0 || lvl > 5);
	acedLogPacman().load(lvl);
}

void acedpol_pacman::run()
{
	acedObjsMot().run();
}


















// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
#pragma endregion