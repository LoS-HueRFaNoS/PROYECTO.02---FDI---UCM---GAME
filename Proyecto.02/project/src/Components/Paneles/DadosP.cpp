#include "DadosP.h"
#include "../../Structures/Panel.h"
#include "../../Managers/game/InterfazManager.h"

DadosP::DadosP(SDLGame* game, Panel* pan, InterfazManager* iM,
	Vector2D pos, Vector2D off, std::vector<Hero*> her)
	: Component(ecs::DadosP, game), pan_(pan), iM_(iM),
	pos_(pos), offset_(off), heroes_(her)
{
}

DadosP::~DadosP()
{
}

void DadosP::init()
{
	int hs = heroes_.size();
	assert(hs > 0 && hs <5);
	for (int i = 0; i < hs; i++)
	{
		Hero* h = heroes_[i];
		// si no esta ya muerto y aun no ha muerto en este combate...
		if (h != nullptr && !h->getDeathGate())
		{
			std::pair<vector<VoidButton*>, vector<VoidButton*>> pair;

			for (int j = 0; j < 3; j++) // el 3 depende del límite (que no se recoge en constante)
			{
				SDL_Rect rect =
				{
					pos_.getX() + offset_.getX() * i + SIZE * j,
					pos_.getY() + offset_.getY() * i,
					SIZE, SIZE
				};
				VoidButton* buttonG = iM_->addButton<VoidButton>(rect, src::DiceGreen);
				pair.first.emplace_back(buttonG);
				pan_->addButton(buttonG);
			}
			for (int j = 0; j < 3; j++) // el 3 depende del límite (que no se recoge en constante)
			{
				SDL_Rect rect =
				{
					pos_.getX() + offset_.getX() * i + SIZE * j,
					pos_.getY() + offset_.getY() * i + SIZE,
					SIZE, SIZE
				};
				VoidButton* buttonR = iM_->addButton<VoidButton>(rect, src::DiceRed);
				pair.second.emplace_back(buttonR);
				pan_->addButton(buttonR);
			}

			buttons_[i] = pair;
		}
	}
}

void DadosP::update()
{
	int hs = heroes_.size();
	assert(hs > 0 && hs < 5);
	for (int i = 0; i < hs; i++)
	{
		Hero* h = heroes_[i];
		// murio?
		if (h != nullptr)
		{
			// si esta muerto...
			if (h->getDeathGate())
			{
				if (buttons_[i].first.size() != 0) // cod. defensivo
				{
					for (int j = 0; j < buttons_[i].first.size(); j++)
					{
						buttons_[i].first[j]->toggleImage(Resources::Joker);
					}
				}

				if (buttons_[i].second.size() != 0) // cod. defensivo
				{
					for (int j = 0; j < buttons_[i].second.size(); j++)
					{
						buttons_[i].second[j]->toggleImage(Resources::Joker);
					}
				}
			}
			// si esta tirando...
			else if (h->isDead())
			{
				for (int j = 0; j < h->getSavingSuccess(); j++)
				{
					buttons_[i].first[j]->toggleImage(Resources::DiceGreen);
				}

				for (int j = 0; j < h->getSavingFailures(); j++)
				{
					buttons_[i].second[j]->toggleImage(Resources::DiceRed);
				}
			}
			else
			{
				for (int j = 0; j < buttons_[i].first.size(); j++)
				{
					buttons_[i].first[j]->toggleImage(Resources::Joker);
				}

				for (int j = 0; j < buttons_[i].second.size(); j++)
				{
					buttons_[i].second[j]->toggleImage(Resources::Joker);
				}
			}
		}
	}
}