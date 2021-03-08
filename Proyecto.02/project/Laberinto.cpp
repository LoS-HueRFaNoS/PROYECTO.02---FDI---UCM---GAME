#include "Laberinto.h"
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>


using namespace std;
Laberinto::Laberinto()
{
	cin >> numLaberinto;
	string text = "Laberinto" + numLaberinto + ".txt"; // Archivo a cargar
	ifstream input; // Flujo de entrada
	input.open(text); // Se abre el archivo
	if (!input.is_open()) // Da error si no se puede abrir el archivo
	{
		throw std::string("Fichero no encontrado");
	}
	else
	{
		input >> h >> w; // Primero se leen el número de filas y de columnas
		laberinto.resize(h);
		for (int i = 0; i < h; ++i)
			laberinto[i].resize(w);
		bool norte, este, sur, oeste; // Variable donde se guarda el siguiente dato
		for (int i = 0; i < h; ++i) // Por cada fila  = Y
		{
			for (int j = 0; j < w; ++j) // Por cada columna  = X
			{
				input >> norte >> este >> sur >> oeste; // Se recoge el siguiente dato
				
				auto a = new Casilla(i,j,norte,este,sur,oeste);
				laberinto[j][i] = a;
			}
		}
		input.close();
	}
}


Laberinto::~Laberinto()
{
	
}