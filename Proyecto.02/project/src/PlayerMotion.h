#pragma once
#include "Component.h"
#include "Transform.h"
#include "Entity.h"
#include "InputHandler.h"
#include "Laberinto.h"
#include "MazePos.h"

class PlayerMotion : public Component
{
public:
	PlayerMotion(SDL_KeyCode avanzar, SDL_KeyCode izq, SDL_KeyCode der , Laberinto* lab_) :Component(ecs::PlayerMotion), //
		pos(nullptr), avance(avanzar), giraIzq(izq), giraDer(der),lab(lab_) //
	{

	}
	PlayerMotion() :Component(ecs::PlayerMotion), //
		pos(nullptr), avance(SDLK_UP), giraIzq(SDLK_LEFT), giraDer(SDLK_DOWN),lab(nullptr) //
	{

	}
	virtual ~PlayerMotion() {
		
	}
	void init() override
	{
		pos = GETCMP1_(MazePos);
	}
	void update() override
	{
		int x = pos->getPos().getX();
		int y = pos->getPos().getY();
		casillaActual = lab->getCasillaInfo(x,y)->checkCell();

		InputHandler* ih = InputHandler::instance();
		if (ih->isKeyDown(avance)) {
			if (casillaActual[pos->getLook()])
			{
				switch (pos->getLook())
				{
				case Norte:
					if (y - 1 >= 0)
					{
						pos->setPos(Vector2D(x, y - 1));
					}
					break;
				case Este:
					if (x + 1 < lab->mazeWidth())
					{
						pos->setPos(Vector2D(x + 1, y));
					}
					break;
				case Sur:
					if (y + 1 < lab->mazeHeigh())
					{
						pos->setPos(Vector2D(x, y + 1));
					}
					break;
				case Oeste:
					if (x - 1 >= 0)
					{
						pos->setPos(Vector2D(x - 1, y));
					}
					break;
				}
				switch (pos->getLook())
				{
				case Norte:
					cout << "Estas en la casilla " << pos->getPos() << ".	\n";
					break;
				case Este:
					cout << "Estas en la casilla " << pos->getPos() << ".	\n";
					break;
				case Sur:
					cout << "Estas en la casilla " << pos->getPos() << ".	\n";
					break;
				case Oeste:
					cout << "Estas en la casilla " << pos->getPos() << ".	\n";
					break;
				}
				
			}
		}
		else if (ih->isKeyDown(giraIzq)) {
			auto sent = pos->getLook();
			if (sent == Norte)
				sent = Oeste;
			else
				sent--;
			pos->setLook(sent);
			switch (pos->getLook())
			{
			case Norte:
				cout <<"Estas mirando hacia el norte" << endl;
				break;
			case Este:
				cout <<"Estas mirando hacia el este" << endl;
				break;
			case Sur:
				cout <<"Estas mirando hacia el sur" << endl;
				break;
			case Oeste:
				cout <<"Estas mirando hacia el oeste" << endl;
				break;
			}
		}
		else if (ih->isKeyDown(giraDer)) {
			int sent = pos->getLook();
			if (sent == Oeste)
				sent = Norte;
			else
				sent++;
			pos->setLook(sent);
			switch (pos->getLook())
			{
			case Norte:
				cout <<"Estas mirando hacia el norte" << endl;
				break;
			case Este:
				cout <<"Estas mirando hacia el este" << endl;
				break;
			case Sur:
				cout <<"Estas mirando hacia el sur" << endl;
				break;
			case Oeste:
				cout <<"Estas mirando hacia el oeste" << endl;
				break;
			}
		}
	}
	void rotarDerecha(){ cout << "rotas a dchas." << endl; }
	void rotarIzquierda(){ cout << "rotas a izdas." << endl; }
	void avanzar(){ cout << "avanzas" << endl; }

private:
	MazePos* pos;
	SDL_KeyCode avance, giraIzq, giraDer;
	vector<bool> casillaActual;
	Laberinto* lab;
	int sent=0;
};

