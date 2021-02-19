#pragma once
#ifndef VECTOR2D_H_
#define VECTOR2D_H_

#include "checkML.h"

#include <math.h>
#include <array>
#include <iostream>
#include <fstream>

enum direction { N, S, E, O };

using namespace std;
typedef unsigned int uint;

class Vector2D 
{
private:
	double x_;  // first coordinate
	double y_;  // second coordinate	

public:
	//Constructores:
	Vector2D();
	Vector2D(const Vector2D &v);
	Vector2D(double x, double y);
	virtual ~Vector2D(); // Solo para memoria dinamica
	//Get / Set:
	inline double getX() const { return x_; };
	inline double getY() const { return y_; };
	inline void setX(double x) { x_ = x; };
	inline void setY(double y) { y_ = y; };
	inline void set(const Vector2D& v) { x_ = v.x_; y_ = v.y_; };	// Copiar vector
	inline void set(double x, double y) { x_ = x; y_ = y; };	// Copiar posiciones
	//Operators:
	inline Vector2D operator+(const Vector2D& v) const { return Vector2D(x_ + v.x_, y_ + v.y_); };	// Suma	
	inline Vector2D operator-(const Vector2D& v) const { return Vector2D(x_ - v.x_, y_ - v.y_); };	// Resta
	inline double operator*(const Vector2D& d) const { return d.x_ * x_ + d.y_ * y_; };	// Escalar de Vectores
	inline Vector2D operator*(double d) const { return Vector2D(x_ * d, y_ * d); };	// Vector por escalar
	inline bool operator==(const Vector2D& d) const { return (x_ == d.x_ && y_ == d.y_); };	// Igualdad
	inline bool operator!=(const Vector2D& d) const { return (x_ != d.x_ || y_ != d.y_); };	// Desigualdad
	//Imprimir:
	friend ostream& operator<<(ostream &os, const Vector2D &v); // Print consola
	friend istream& operator>>(istream &os, Vector2D& v); // Leer de teclado
	friend ofstream& operator<<(ofstream& file, const Vector2D &v); // Print file
	friend ifstream& operator>>(ifstream& file, Vector2D& v); // Leer de fichero

	// Función AUXILIAR define las direcciones:
	void dir(direction d);
		
};
using Point2D = Vector2D;		// alias Point2D

const int NUM_DIRS = 4;
const Vector2D DIRS[NUM_DIRS] =
{
	{Vector2D(0,-1)},	// N
	{Vector2D(0, 1)},	// S
	{Vector2D(1,0)},	// E
	{Vector2D(-1,0)}	// O
};

int dirInv(Vector2D dir);		// devuelve la dirección inversa (-1 = parado)
int contrario(int d);			// devuelve el número contrario (par|impar)
int act(Vector2D dir);			// devuelve la dirección actual (-1 = parado)















// developed by: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL)
#endif