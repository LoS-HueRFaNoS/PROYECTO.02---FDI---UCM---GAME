#pragma once
#include "../ecs/Component.h"
#include "../Utilities/checkML.h"
#include "Laberinto.h"
#include "MazePos.h"
class Interfaz;
class PlayerMotion : public Component
{
public:
	PlayerMotion(SDL_KeyCode avanzar, SDL_KeyCode izq, SDL_KeyCode der, Laberinto* lab_);
	PlayerMotion();
	virtual ~PlayerMotion() {}
	void init() override;
	void update() override;
	void rotarDerecha();
	void rotarIzquierda();
	void avanzar();
	void debugear();
	MazePos* getPos() { return pos; }
private:
	MazePos* pos;
	SDL_KeyCode avance, giraIzq, giraDer;
	vector<bool> casillaActual;
	Laberinto* lab;
	int sent=0 ,x=0,y=0;
};

