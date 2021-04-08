#pragma once
#include "Component.h"
#include "Transform.h"
#include "Entity.h"
#include "InputHandler.h"
#include "Laberinto.h"

class PlayerViewer : public Component
{
public:
	PlayerViewer():Component(ecs::PlayerViewer), //
		pos(nullptr),lab(nullptr)//
	{

	}

	PlayerViewer(Laberinto* lab_) :Component(ecs::PlayerViewer), //
		pos(nullptr) ,lab(lab_) //
	{

	}

	virtual ~PlayerViewer() {
		
	}
	void init() override
	{
		pos = GETCMP1_(MazePos);
	}
	void update() override
	{
		int x = int(pos->getPos().getX());
		int y = int(pos->getPos().getY());
		sentido = pos->getLook();
		casillaActual = lab->getCasillaInfo(x,y)->checkCell();
	}

	virtual void draw()
	{
		SDL_Rect dest = { 0, 0, 800, 600 };
		Texture* texturaCasilla;
		Texture* texturaIzquierda;
		Texture* texturaDerecha;

		int izquierda;
		if (sentido == Norte) izquierda = Oeste;
		else izquierda = sentido-1;

		int derecha;
		if (sentido == Oeste) derecha = Norte;
		else derecha = sentido+1;

		auto manager = game_->getTextureMngr();
		if (casillaActual[sentido]) // <-^->
			texturaCasilla = manager->getTexture(Resources::camino_del);
		else
			texturaCasilla = manager->getTexture(Resources::muro_del);
		texturaCasilla->render(dest);
		if (casillaActual[izquierda])
			texturaIzquierda = manager->getTexture(Resources::camino_izq);
		else
			texturaIzquierda = manager->getTexture(Resources::muro_izq);
		texturaCasilla->render(dest);
		if (casillaActual[derecha]) // <-
			texturaDerecha = manager->getTexture(Resources::camino_der);
		else
			texturaDerecha = manager->getTexture(Resources::muro_der);

		texturaCasilla->render(dest);
		texturaIzquierda->render(dest);
		texturaDerecha->render(dest);
	}
private:
	MazePos* pos;
	Laberinto* lab;
	vector<bool> casillaActual;
	int sentido = Norte;
};

