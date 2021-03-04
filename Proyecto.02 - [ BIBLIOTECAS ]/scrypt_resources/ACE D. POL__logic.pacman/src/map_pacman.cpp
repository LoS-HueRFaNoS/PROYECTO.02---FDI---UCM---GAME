// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
//

#include "map_pacman.h"
#include "logic_pacman.h"

#pragma region METODOS_MAP

// :::::::::::::::::: MOTOR DEL MAPA ::::::::::::::::::::::

map_pacman::map_pacman(ifstream& file) : GameMap(file)
{
	for (int r = 0; r < rows; ++r) {
		for (int c = 0; c < cols; ++c) {
			int m;
			file >> m;
			if (m == 2) { acedLogPacman().addFood(); };
			cells[r][c] = MapCell(m);
		}
	}
}














// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
#pragma endregion