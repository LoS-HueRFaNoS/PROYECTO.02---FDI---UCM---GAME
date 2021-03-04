// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
//

#include "Vector2D.h"

// needed for visual studio
#ifndef M_PI
#define M_PI 3.14159265358979323846264338327950288
#endif

#pragma region METODOS_VECTOR2D

Vector2D::Vector2D() : x_(), y_() {}

Vector2D::Vector2D(const Vector2D &v) : x_(v.getX()), y_(v.getY()) {}

Vector2D::Vector2D(double x, double y) : x_(x), y_(y) {}

Vector2D::~Vector2D() {}

void Vector2D::dir(direction d)
{
	switch (d)
	{
	case 0: // Norte
		set(DIRS[N]);
		break;
	case 1: // Sur
		set(DIRS[S]);
		break;
	case 2: // Este
		set(DIRS[E]);
		break;
	case 3: // Oeste
		set(DIRS[O]);
		break;
	default: // Parado
		set(0, 0);
		break;
	}
}

int dirInv(Vector2D dir)
{
	int d = act(dir);
	d = contrario(d);
	return d;
}

int contrario(int d)
{
	if (d != -1)
	{
		if (d % 2 == 0)
		{
			d = d + 1;
		}
		else
		{
			d = d - 1;
		}
	}
	return d;
}

int act(Vector2D dir)
{
	int d = -1;
	if		(dir == DIRS[N]) { d = N; }
	else if (dir == DIRS[S]) { d = S; }
	else if (dir == DIRS[E]) { d = E; }
	else if (dir == DIRS[O]) { d = O; }
	return d;
}

ostream& operator<<(ostream &os, const Vector2D &v) 
{
	os << "[" << v.getX() << "," << v.getY() << "]";
	return os;
}

istream& operator>>(istream& in, Vector2D& v)
{
	int x, y;
	in >> x >> y;
	v.setX(x);
	v.setY(y);
	return in;
}

ofstream& operator<<(ofstream& file, const Vector2D& v)
{
	file << v.getX() << ' ' << v.getY();
	return file;
}

ifstream& operator>>(ifstream& file, Vector2D& v)
{
	int x, y;
	file >> x >> y;
	v.setX(x);
	v.setY(y);
	return file;
}














// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
#pragma endregion
