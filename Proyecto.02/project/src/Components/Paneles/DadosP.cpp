#include "DadosP.h"
#include "../../Structures/Panel.h"
#include "../../Managers/game/InterfazManager.h"

DadosP::DadosP(SDLGame* game, Panel* pan, InterfazManager* iM,
	Vector2D pos, Vector2D off, std::vector<Hero*>* her)
	: Component(ecs::DadosP, game), pan_(pan), iM_(iM),
	pos_(pos), offset_(off), heroes_(her)
{
}

DadosP::~DadosP()
{

}

void DadosP::init()
{
	int hs = heroes_->size();
	for (int i = 0; i < hs; i++)
	{
		Hero* h = heroes_->at(i);
		// si no esta ya muerto y aun no ha muerto en este combate...
		if (h != nullptr && !h->getDeathGate())
		{
			for (int j = 0; j < 3; j++)
			{
				SDL_Rect rect =
				{
					pos_.getX() + offset_.getX() * i + SIZE * j,
					pos_.getY() + offset_.getY() * i,
					SIZE, SIZE
				};
				pan_->addButton(iM_->addButton<SDL_Object>(rect, src::DiceGreen));

				rect.y += SIZE;
				pan_->addButton(iM_->addButton<SDL_Object>(rect, src::DiceRed));
			}
		}
	}
}

void DadosP::update()
{
	
}