#include "AnimationManager.h"

AnimationManager::AnimationManager():Component(ecs::AnimationManager)
{
	gold = 0;
	manaPotions = 0;
	healthPotions = 0;
	exp = 0;
	
}

void AnimationManager::update()
{
	if (reward)
	{
		rewardPos.setY(rewardPos.getY() + 5);
		if (rewardPos.getY() >= 400) reward = false;
	}

	if (vibAnimation)
	{

		Uint32 frameTime = game_->getTime() - startVibTime;
		if (frameTime > 10000)
			vibracion = !vibracion;
	}
	

}

void AnimationManager::draw()
{
	if (vibracion)		renderVibration();
	if (reward)			renderReward();
	if (habilidad)		renderHabilidad();
	if (turno > -1)		renderTurno();
}

void AnimationManager::renderVibration()
{
	double _x = game_->setHorizontalScale(70);
	double _y = game_->setVerticalScale(70);
	double _w = game_->setHorizontalScale(1340);
	double _h = game_->setVerticalScale(620);
	SDL_Rect dest = RECT(_x, _y, _w, _h);
	game_->instance()->getTextureMngr()->getTexture(Resources::vibration)->render(dest);
}

void AnimationManager::renderReward()
{
}

void AnimationManager::renderHabilidad()
{
}

void AnimationManager::renderTurno()
{
}
