#include "Casilla.h"

Casilla::Casilla()
{
	x = 0;
	y = 0;
	direcciones.resize(4);
	direcciones[Norte] = 0;
	direcciones[Este] = 0;
	direcciones[Sur] = 0;
	direcciones[Oeste] = 0;
}
Casilla::Casilla(int x_,int y_, bool _N, bool _E, bool _S, bool _O)
{
	x = x_;
	y = y_;
	direcciones.resize(4);
	direcciones[Norte] = _N;
	direcciones[Este] = _E;
	direcciones[Sur] = _S;
	direcciones[Oeste] = _O;
}

Casilla::~Casilla()
{

}

vector<bool>* Casilla::checkCell()
{
	return &direcciones;
}