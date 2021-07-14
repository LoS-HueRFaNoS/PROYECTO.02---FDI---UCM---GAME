#include "Casilla.h"
#include "../Utilities/SDL_macros.h"

Casilla::Casilla(SDLGame* game):esSalida(false)
{
	game_ = game;
	direcciones.resize(4);
	direcciones[Norte] = 0;
	direcciones[Este] = 0;
	direcciones[Sur] = 0;
	direcciones[Oeste] = 0;
	visib = noVisitado;
	
}

Casilla::Casilla(SDLGame* game, bool _N, bool _E, bool _S, bool _O ) :esSalida(false)
{
	game_= game;
	direcciones.resize(4);
	direcciones[Norte] = _N;
	direcciones[Este] = _E;
	direcciones[Sur] = _S;
	direcciones[Oeste] = _O;
	visib = noVisitado;
	
}

Casilla::~Casilla()
{

}

vector<bool> Casilla::checkCell()
{
	return direcciones;
}
void Casilla::casillaRender(int x, int y, double w, double h)
{
	SDL_Rect dest = RECT( x, y, w, h );
	Texture* texturaSuelo;
	Texture* texturaPosActual;
	//Texture* texturaSalida;
	Texture* texturaPared = nullptr;
	auto manager = game_->getTextureMngr();

	if (visib == noVisitado)
	{
		texturaSuelo = manager->getTexture(Resources::no_visitado);
		texturaSuelo->render(dest);
	}
	else if (visib == noEntrado)
	{
		texturaSuelo = manager->getTexture(Resources::no_entrado);
		texturaSuelo->render(dest);
	}
	else if (visib == visitado)
	{
		if (isExit())
		{
			texturaSuelo = manager->getTexture(Resources::salidaMiniMap);
		}
		else if (hasChest()) texturaSuelo = manager->getTexture(Resources::cofreMiniMap);
		else texturaSuelo = manager->getTexture(Resources::visitado);
		texturaSuelo->render(dest);
		
		for (int i = 0; i < direcciones.size(); ++i)
		{
			if (!direcciones[i])
			{
				switch (i)
				{
				case Norte:
					texturaPared = manager->getTexture(Resources::pared_N);
					break;
				case Este:
					texturaPared = manager->getTexture(Resources::pared_E);
					break;
				case Sur:
					texturaPared = manager->getTexture(Resources::pared_S);
					break;
				case Oeste:
					texturaPared = manager->getTexture(Resources::pared_O);
					break;
				}
				if (texturaPared != nullptr)
					texturaPared->render(dest);
					
			}

		}

	}
	if (esPosActual)
	{
		
		texturaPosActual = manager->getTexture(Resources::posMiniMap);
		texturaPosActual->render(dest,angulo);

	}
}

void Casilla::setSalida()
{
	esSalida = true;
	vector<Look> paredes;
	for (int i = 0; i < 4; i++)
	{
		if (!direcciones[i]) paredes.push_back((Look)i);
	}
	if (paredes.size() == 0) direccionSalida = (Look)-1;
	else
	{
		int dir = game_->getRandGen()->nextInt(0, paredes.size());
		direccionSalida = paredes[dir];
	}
}
void Casilla::addChest(Chest* cofre)
{
	hayCofre = true;
	// meter en chest el cofre
	chest = new ObjectChest(game_, cofre);
	/*vector<Look> paredes;
	for (int i = 0; i < 4; i++)
	{
		paredes.push_back((Look)i);
	}
	int dir = game_->getRandGen()->nextInt(0, paredes.size());
	direccionCofre = paredes[dir];*/
}