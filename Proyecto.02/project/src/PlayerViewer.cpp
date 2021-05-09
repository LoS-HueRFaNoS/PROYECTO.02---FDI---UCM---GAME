#include "PlayerViewer.h"
#include "StateBar.h"

void PlayerViewer::renderEnemyActual()
{

	if (!cas->getEnemy()->empty())
	{
		auto enemyVector = *cas->getEnemy();
		int tam = enemyVector.size();
		if (tam == 1)
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

void PlayerViewer::enemyViewer(enemyTemplate temp, int x, int y, int w, int h)
{
	Texture* enemigo;
	auto manager = game_->getTextureMngr();
	//enemigo = manager->getTexture(Resources::Placas+temp);
	enemigo = manager->getTexture(Resources::Monster);
	SDL_Rect dest = { x, y, w, h };
	enemigo->render(dest);

}
