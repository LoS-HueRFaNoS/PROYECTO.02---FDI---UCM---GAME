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
		pos(nullptr),lab(nullptr),cas(nullptr), casSig(nullptr),manager(nullptr)//
	{

	}

	PlayerViewer(Laberinto* lab_) :Component(ecs::PlayerViewer), //
		pos(nullptr) ,lab(lab_), cas(nullptr), casSig(nullptr),manager(nullptr) //
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
		cas = lab->getCasillaInfo(x, y);
		casillaActual = cas->checkCell();
		if (casillaActual[sentido])
		{
			switch (sentido)
			{
			case Norte:
				y -= 1;
				if (y != 0)
					casSig = lab->getCasillaInfo(x, y - 1);
				break;
			case Este:
				x += 1;
				if (x != lab->mazeWidth())
					casSig = lab->getCasillaInfo(x + 1, y);
				break;
			case Sur:
				y += 1;
				if (y != lab->mazeHeigh())
					casSig = lab->getCasillaInfo(x, y + 1);
				break;
			case Oeste:
				x -= 1;
				if (x != 0)
					casSig = lab->getCasillaInfo(x - 1, y);
				break;
			}
			cas = lab->getCasillaInfo(x, y);
			casillaActual = cas->checkCell();
			casillaSig = casSig->checkCell();
		}
		else casillaSig = cas->checkCell();
	}

	virtual void draw()
	{
		SDL_Rect dest = { 0, 0, 800, 600 }; // Ventana del laberinto
		/*Texture* texturaCasilla;
		Texture* suelo;
		Texture* texturaIzquierda;
		Texture* texturaDerecha;
		Texture* texturaSigFr;
		Texture* texturaSigIzq;
		Texture* texturaSigDer;*/

		int izquierda; // Variable que guarda que direccion hay a la izquierda
		if (sentido == Norte) izquierda = Oeste;
		else izquierda = sentido-1;

		int derecha; // Variable que guarda que direccion hay a la derecha
		if (sentido == Oeste) derecha = Norte;
		else derecha = sentido+1;

		auto manager = game_->getTextureMngr(); // Manager de texturas
		if (casillaActual[sentido]) // <-^-> Si delante hay un camino, dibujaremos la informacion de la casilla siguiente
		{
			

			manager->getTexture(Resources::camino_fondo_fr)->render(dest);
			if (!casillaSig[sentido])manager->getTexture(Resources::muro_fondo_fr)->render(dest);

			if (casillaSig[izquierda])
			{
				manager->getTexture(Resources::camino_fondo_izq)->render(dest);
				manager->getTexture(Resources::muro_fondo_fr_izq)->render(dest);
			}
			else manager->getTexture(Resources::muro_fondo_izq)->render(dest);
	
			if (casillaSig[derecha]) // <-
			{
				manager->getTexture(Resources::camino_fondo_der)->render(dest);
				manager->getTexture(Resources::muro_fondo_fr_der)->render(dest);
			}
			else manager->getTexture(Resources::muro_fondo_der)->render(dest);
			manager->getTexture(Resources::camino_fr)->render(dest);
		}
		else manager->getTexture(Resources::muro_fr)->render(dest);

		if (casillaActual[izquierda]) // <- Si hay un camino a la izquierda
		{
			manager->getTexture(Resources::camino_izq)->render(dest);
			manager->getTexture(Resources::muro_fr_izq)->render(dest);
		}

		else manager->getTexture(Resources::muro_izq)->render(dest);

		if (casillaActual[derecha]) // -> Si hay un camino a la derecha
		{
			manager->getTexture(Resources::camino_der)->render(dest);
			manager->getTexture(Resources::muro_fr_der)->render(dest);
		}
		else manager->getTexture(Resources::muro_der)->render(dest);

		//renderEnemySig();
		manager->getTexture(Resources::camino_fr)->render(dest);
		//renderEnemyActual();

	}


private:
	MazePos* pos;
	Laberinto* lab;
	vector<bool> casillaActual;
	vector<bool> casillaSig;
	int sentido = Norte;
	Casilla* cas;
	Casilla* casSig;
	TexturesManager* manager;

	void renderEnemyActual()
	{
		
		if (!cas->getEnemy()->empty())
		{
			auto enemyVector = *cas->getEnemy();
			int tam = enemyVector.size();
			if ( tam == 1)
			{
				enemyViewer(enemyVector[0], 400 + 60, 400, 60, 60);
			}
			else
			{

				for (int i = 0; i < tam; i++)
				{
					enemyViewer(enemyVector[i], 400 + i * 60, 400, 60, 60);
				}
			}
			
		}
	}
	void renderEnemySig()
	{
		if (!casSig->getEnemy()->empty())
		{
			Texture* enemigo;
			auto manager = game_->getTextureMngr();
			//enemigo = manager->getTexture(Resources::EnemigoSombra);
			SDL_Rect dest = { 400 + 60, 100, 60, 60 };
			enemigo->render(dest);
		}
	}
	void enemyViewer(enemyTemplate temp, int x, int y , int w, int h)
	{
		Texture* enemigo;
		auto manager = game_->getTextureMngr();
		enemigo = manager->getTexture(Resources::Placas+temp);
		SDL_Rect dest = { x, y, w, h };
		enemigo->render(dest);

	}
};

