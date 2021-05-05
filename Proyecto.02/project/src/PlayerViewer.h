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
		casillaSig = cas->checkCell();
		if (casillaActual[sentido])
		{
			switch (sentido)
			{
			case Norte:
				y -= 1;
				if (y != 0)
					casSigSig = lab->getCasillaInfo(x, y - 1);
				break;
			case Este:
				x += 1;
				if (x != lab->mazeWidth()-1)
					casSigSig = lab->getCasillaInfo(x + 1, y);
				break;
			case Sur:
				y += 1;
				if (y != lab->mazeHeigh()-1)
					casSigSig = lab->getCasillaInfo(x, y + 1);
				break;
			case Oeste:
				x -= 1;
				if (x != 0)
					casSigSig = lab->getCasillaInfo(x - 1, y);
				break;
			}
			casSig = lab->getCasillaInfo(x, y);
			casillaSig = casSig->checkCell();
			casillaSigSig = casSigSig->checkCell();
		}
		else casillaSigSig = cas->checkCell();
	}

	virtual void draw()
	{
		double _x = game_->setHorizontalScale(70);
		double _y = game_->setVerticalScale(70);
		double _w = game_->setHorizontalScale(1340);
		double _h = game_->setVerticalScale(620);
		SDL_Rect dest = { _x, _y, _w, _h };
		/*Texture* texturaCasilla;
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
			if (!casillaSigSig[sentido])
			{
				manager->getTexture(Resources::muro_fondo_fr)->render(dest);
				
			}

			if (casillaSigSig[izquierda])
			{
				manager->getTexture(Resources::camino_fondo_izq)->render(dest);
				manager->getTexture(Resources::muro_fondo_fr_izq)->render(dest);
			}
			else manager->getTexture(Resources::muro_fondo_izq)->render(dest);
	
			if (casillaSigSig[derecha]) // <-
			{
				manager->getTexture(Resources::camino_fondo_der)->render(dest);
				manager->getTexture(Resources::muro_fondo_fr_der)->render(dest);
			}
			else manager->getTexture(Resources::muro_fondo_der)->render(dest);
			manager->getTexture(Resources::camino_fr)->render(dest);
			if (casillaSig[izquierda]) // <- Si hay un camino a la izquierda
			{
				manager->getTexture(Resources::camino_izq)->render(dest);
				manager->getTexture(Resources::muro_fr_izq)->render(dest);
			}

			else manager->getTexture(Resources::muro_izq)->render(dest);

			if (casillaSig[derecha]) // -> Si hay un camino a la derecha
			{
				manager->getTexture(Resources::camino_der)->render(dest);
				manager->getTexture(Resources::muro_fr_der)->render(dest);
			}
			else manager->getTexture(Resources::muro_der)->render(dest);

			if (casillaSig[sentido])
			{
				manager->getTexture(Resources::camino_fr)->render(dest);
				//renderEnemySig();
				
			}
			else manager->getTexture(Resources::muro_fr)->render(dest);
			

			
		}
		else manager->getTexture(Resources::muro_del)->render(dest);

		renderEnemyActual();
	}


private:
	MazePos* pos;
	Laberinto* lab;
	vector<bool> casillaActual;
	vector<bool> casillaSig;
	vector<bool> casillaSigSig;
	int sentido = Norte;
	Casilla* cas;
	Casilla* casSig;
	Casilla* casSigSig;
	TexturesManager* manager;

	void renderEnemyActual()
	{
		
		if (!cas->getEnemy()->empty())
		{
			auto enemyVector = *cas->getEnemy();
			int tam = enemyVector.size();
			if ( tam == 1)
			{
				enemyViewer(enemyVector[0], 100 + 200, 200, 250, 250);
			}
			else
			{

				for (int i = 0; i < tam; i++)
				{
					enemyViewer(enemyVector[i], 100 + i * 200, 200, 250, 250);
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
			enemigo = manager->getTexture(Resources::Desconocido);
			SDL_Rect dest = { 300 , 100, 300, 300 };
			enemigo->render(dest);
		}
	}
	void enemyViewer(enemyTemplate temp, int x, int y , int w, int h)
	{
		Texture* enemigo;
		auto manager = game_->getTextureMngr();
		//enemigo = manager->getTexture(Resources::Placas+temp);
		enemigo = manager->getTexture(Resources::Monster);
		SDL_Rect dest = { x, y, w, h };
		enemigo->render(dest);

	}
};

