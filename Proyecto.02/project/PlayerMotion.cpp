#include "src/PlayerMotion.h"
#include "src/InputHandler.h"


PlayerMotion::PlayerMotion(SDL_KeyCode avanzar, SDL_KeyCode izq, SDL_KeyCode der, Laberinto* lab_):Component(ecs::PlayerMotion), //
	pos(nullptr), avance(avanzar), giraIzq(izq), giraDer(der), lab(lab_) //
{

}

PlayerMotion::PlayerMotion() :Component(ecs::PlayerMotion), //
pos(nullptr), avance(SDLK_UP), giraIzq(SDLK_LEFT), giraDer(SDLK_DOWN), lab(nullptr) //
{

}

void PlayerMotion::init()
{
	pos = GETCMP1_(MazePos);
	debugear();

}

void PlayerMotion::update()
{
	InputHandler* ih = InputHandler::instance();
	if (ih->isKeyDown(avance)) { avanzar();	}
	else if (ih->isKeyDown(giraIzq)) { rotarIzquierda(); }
	else if (ih->isKeyDown(giraDer)) { rotarDerecha(); 	}
}

void PlayerMotion::rotarDerecha()
{
	x = int(pos->getPos().getX());
	y = int(pos->getPos().getY());
	casillaActual = lab->getCasillaInfo(x, y)->checkCell();

	sent = pos->getLook();
	if (sent == Oeste)
		sent = Norte;
	else
		sent++;

	pos->setLook(sent);

	switch (pos->getLook())
	{
	case Norte:
		cout << "Estas mirando hacia el norte" << endl;
		break;
	case Este:
		cout << "Estas mirando hacia el este" << endl;
		break;
	case Sur:
		cout << "Estas mirando hacia el sur" << endl;
		break;
	case Oeste:
		cout << "Estas mirando hacia el oeste" << endl;
		break;
	}
}

void PlayerMotion::rotarIzquierda()
{
	x = int(pos->getPos().getX());
	y = int(pos->getPos().getY());
	casillaActual = lab->getCasillaInfo(x, y)->checkCell();

	auto sent = pos->getLook();
	if (sent == Norte)
		sent = Oeste;
	else
		sent--;
	pos->setLook(sent);

	switch (pos->getLook())
	{
	case Norte:
		cout << "Estas mirando hacia el norte" << endl;
		break;
	case Este:
		cout << "Estas mirando hacia el este" << endl;
		break;
	case Sur:
		cout << "Estas mirando hacia el sur" << endl;
		break;
	case Oeste:
		cout << "Estas mirando hacia el oeste" << endl;
		break;
	}
}

void PlayerMotion::avanzar()
{
	x = int(pos->getPos().getX());
	y = int(pos->getPos().getY());
	casillaActual = lab->getCasillaInfo(x, y)->checkCell();

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
		/*cout << "Estas en la casilla " << pos->getPos() << ".	\n";

		vector<Enemy*> enemigo = lab->getCasillaInfo(pos->getPos().getX(), pos->getPos().getY())->getEnemy();

		for (int i = 0; i < enemigo.size(); i++)
		{
			cout <<"Encuentras con el enemigo "<< enemigo[i]->name() << endl;
		}*/
		debugear();
		
	}
}

void PlayerMotion::debugear()
{
	cout << "Estas en la casilla " << pos->getPos() << ".	\n";

	vector<Enemy*> enemigo = lab->getCasillaInfo(pos->getPos().getX(), pos->getPos().getY())->getEnemy();

	for (int i = 0; i < enemigo.size(); i++)
	{
		cout << "Encuentras con el enemigo " << enemigo[i]->name() << endl;
	}
}
