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
		manager = game_->getTextureMngr();
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
				break;
			case Este:
				x += 1;
				break;
			case Sur:
				y += 1;
				break;
			case Oeste:
				x -= 1;
				break;
			}
			casSig = lab->getCasillaInfo(x, y);
			casillaSig = casSig->checkCell();
		}
	}

	virtual void draw()
	{
		double _x = game_->setHorizontalScale(70);
		double _y = game_->setVerticalScale(70);
		double _w = game_->setHorizontalScale(1340);
		double _h = game_->setVerticalScale(620);
		SDL_Rect dest = { _x, _y, _w, _h };
		Texture* texturaCasilla;
		Texture* texturaIzquierda;
		Texture* texturaDerecha;
		/*Texture* texturaSigFr;
		Texture* texturaSigIzq;
		Texture* texturaSigDer;*/

		int izquierda;
		if (sentido == Norte) izquierda = Oeste;
		else izquierda = sentido-1;

		int derecha;
		if (sentido == Oeste) derecha = Norte;
		else derecha = sentido+1;

		

		if (casillaActual[sentido]) // <-^->
		{
			texturaCasilla = manager->getTexture(Resources::camino_fr);

			//if (casillaSig[sentido])
			//{
			//	texturaSigFr = manager->getTexture(Resources::sigcamino_fr);
			//}
			//else 
			//	texturaSigFr = manager->getTexture(Resources::sigmuro_fr);
			//if (casillaSig[izquierda])
			//	texturaSigIzq = manager->getTexture(Resources::sigcamino_izq);
			//else
			//	texturaSigIzq = manager->getTexture(Resources::sigmuro_izq);

			//if (casillaSig[derecha]) // <-
			//	texturaSigDer = manager->getTexture(Resources::sigcamino_der);
			//else
			//	texturaSigDer = manager->getTexture(Resources::sigmuro_der);

		}
		else
			texturaCasilla = manager->getTexture(Resources::muro_fr);

		if (casillaActual[izquierda])
			texturaIzquierda = manager->getTexture(Resources::camino_izq);
		else
			texturaIzquierda = manager->getTexture(Resources::muro_izq);

		if (casillaActual[derecha]) // <-
			texturaDerecha = manager->getTexture(Resources::camino_der);
		else
			texturaDerecha = manager->getTexture(Resources::muro_der);

		/*if (casillaActual[sentido])
		{
			texturaSigFr->render(dest);
			texturaSigIzq->render(dest);
			texturaSigDer->render(dest);

			renderEnemySig();
		}*/

		texturaCasilla->render(dest);
		texturaIzquierda->render(dest);
		texturaDerecha->render(dest);

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
			//enemigo = manager->getTexture(Resources::EnemigoSombra);
			SDL_Rect dest = { 400 + 60, 100, 60, 60 };
			enemigo->render(dest);
		}
	}
	void enemyViewer(enemyTemplate temp, int x, int y , int w, int h)
	{
		Texture* enemigo;
		enemigo = manager->getTexture(Resources::Placas+temp);
		SDL_Rect dest = { x, y, w, h };
		enemigo->render(dest);

	}
};

