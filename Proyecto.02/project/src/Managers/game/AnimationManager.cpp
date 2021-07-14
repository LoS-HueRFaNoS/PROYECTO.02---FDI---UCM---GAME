#include "AnimationManager.h"
#include <vector>
#include "../../Utilities/checkML.h"
#include "../../ecs/ecs.h"
#include "CombatManager.h"
#include "../../Structures/Vector2D.h"
#include "../../Components/Rectangle.h"
#include "../TheElementalMaze.h"
#include "../../Utilities/SDL_macros.h"
#include <string>


void AnimationManager::init()
{
	expTex = new Texture();
	goldTex = new Texture();
	manaTex = game_->instance()->getTextureMngr()->getTexture(Resources::PocionMana);
	manaNumTex = new Texture();
	healthTex = new Texture();
	healthTex = game_->instance()->getTextureMngr()->getTexture(Resources::PocionVida);
	healthNumTex = new Texture();
	transiTex = game_->instance()->getTextureMngr()->getTexture(Resources::fade);
	keyTex = new Texture();
	keyTex = game_->instance()->getTextureMngr()->getTexture(Resources::LlaveCofre);
	keyNumTex = new Texture();
}

void AnimationManager::update()
{
	if (TheElementalMaze::instance()->gameState() != GameState::COMBAT)
	{
		vibAnimation = false; vibracion = false;
	}
	if (reward)
	{
		rewardPosY -= 1;
		if (rewardPosY < 200) reward = false;
	}

	if (vibAnimation)
	{

		Uint32 frameTime = game_->getTime() - startVibTime;
		if (frameTime > 500)
		{
			vibracion = !vibracion;
			startVibTime = game_->getTime();
		}
	}
	if (transicion)
	{
		Uint32 frameTime = game_->getTime() - startTransitTime;
		if (frameTime > totalTransitTime)
		{
			frame++;
			startTransitTime = game_->getTime();
		}
		if (frame ==12)
		{
			transicion = false;
		}
	}
	

}

void AnimationManager::draw()
{

	if (vibracion)		
		renderVibration();
	if (reward)			renderReward();
	if (transicion)  
		renderTransicion();
}

void AnimationManager::animVib(rpgLogic::characterType current, rpgLogic::characterType next)
{
	if (current == characterType::ENEMY)
	{
		vibAnimation= false;
		vibracion = true;
	}
	else if (next == characterType::ENEMY)
	{
		vibAnimation = true;
		startVibTime=  game_->getTime();
	}
	else
	{
		vibAnimation =false;
		vibracion =false;
	}
}

void AnimationManager::showReward(int exp_, int gold_, int mana_, int health_, bool key_)
{
	exp = exp_;
	gold = gold_;
	manaPotions = mana_;
	healthPotions = health_;
	key = key_;

	reward = true;
	rewardPosY = game_->setVerticalScale(500);

	string text;
	SDL_Color color;

	text = "+ " + to_string(exp) + " Exp";
	color = { 0,255,0,225 };
	expTex->loadFromText(game_->getRenderer(), text, game_->getFontMngr()->getFont(Resources::FontId::Beaulieux), color);

	text = "+ " + to_string(gold) + " Coins";
	color = { 255,255,0,225 };
	goldTex->loadFromText(game_->getRenderer(), text, game_->getFontMngr()->getFont(Resources::FontId::Beaulieux), color);

	text = "x " + to_string(manaPotions);
	color = { 0,0,255,225 };
	manaNumTex->loadFromText(game_->getRenderer(), text, game_->getFontMngr()->getFont(Resources::FontId::Beaulieux), color);

	text = "x " + to_string(healthPotions);
	color = { 0,255,0,225 };
	healthNumTex->loadFromText(game_->getRenderer(), text, game_->getFontMngr()->getFont(Resources::FontId::Beaulieux), color);

	if (key) {
		text = "x1";
		color = { 255,255,255,225 };
		keyNumTex->loadFromText(game_->getRenderer(), text, game_->getFontMngr()->getFont(Resources::FontId::Beaulieux), color);
	}
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
	
	int pos = game_->setHorizontalScale(300);
	int width = 100;
	SDL_Rect dest;
	if (exp > 99)
		width = 110;

	//Experiencia
	dest = RECT(pos,rewardPosY, width,50);  	expTex->render(dest);		pos += width+20;
	
	width = 120;
	if (gold > 99)
		width = 130;

	//Coins
	dest = RECT(pos, rewardPosY, width, 50);	goldTex->render(dest);		pos += width+20;

	width = 50;

	//Mana
	if (manaPotions > 0) {
		dest = RECT(pos, rewardPosY, width, 50);	manaTex->render(dest);		pos += width+20;
		dest = RECT(pos, rewardPosY, width, 50);	manaNumTex->render(dest);		pos += width+20;
	}

	//health
	if (healthPotions > 0) {
		dest = RECT(pos, rewardPosY, width, 50);	healthTex->render(dest);		pos += width+20;
		dest = RECT(pos, rewardPosY, width, 50);	healthNumTex->render(dest);		pos += width+20;
	}

	//Key
	if (key) {
		dest = RECT(pos, rewardPosY, width, 50);	keyTex->render(dest);		pos += width + 20;
		dest = RECT(pos, rewardPosY, width, 50);	keyNumTex->render(dest);		pos += width + 20;
	}
}


void AnimationManager::addtransicion(Uint32 transTime)
{
	transicion = true;
	totalTransitTime = transTime/12;
	startTransitTime = game_->getTime();
	frame = 0;

}

void AnimationManager::renderTransicion()
{
	double _w = game_->getWindowWidth();
	double _h = game_->getWindowHeight();
	SDL_Rect dest,clip;
	dest = RECT(0, 0, _w, _h);
	double clipw = transiTex->getWidth() / 12;
	double cliph = transiTex->getHeight();
	clip = RECT(frame * clipw, 0, clipw, cliph);
	transiTex->render(dest, clip);
	
}

