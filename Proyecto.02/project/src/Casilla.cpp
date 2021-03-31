#include "Casilla.h"

Casilla::Casilla():esSalida(false)
{
	direcciones.resize(4);
	direcciones[Norte] = 0;
	direcciones[Este] = 0;
	direcciones[Sur] = 0;
	direcciones[Oeste] = 0;
	visib = noVisitado;
}

Casilla::Casilla(bool _N, bool _E, bool _S, bool _O ) :esSalida(false)
{
	direcciones.resize(4);
	direcciones[Norte] = _N;
	direcciones[Este] = _E;
	direcciones[Sur] = _S;
	direcciones[Oeste] = _O;
	visib = noVisitado;
	
}

Casilla::~Casilla()
{

}

vector<bool> Casilla::checkCell()
{
	return direcciones;
}