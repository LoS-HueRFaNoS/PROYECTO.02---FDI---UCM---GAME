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
	keyLevelTex = new Texture();
	keyLevelTex = game_->instance()->getTextureMngr()->getTexture(Resources::LlaveNivel);
	keyNumTex = new Texture();
	noKeysTex = new Texture();
	noKeysTex = game_->instance()->getTextureMngr()->getTexture(Resources::LlaveVacia);
	heroTex = new Texture();
	damageTex = new Texture();
	missTex = new Texture();
	vsTex = new Texture();
	heroVsTex = new Texture();
	EnemyVsTex = new Texture();
	KillTex = game_->instance()->getTextureMngr()->getTexture(Resources::kill);
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
	if (receiveDamage)
	{
		Uint32 frameTime = game_->getTime() - startDamageTime;
		texSize =60- 2*frameTime / 100;
		if (frameTime > 1000)
		{

			receiveDamage = false;
		}

	}
	if (miss)
	{
		Uint32 frameTime = game_->getTime() - startMissTime;

		if (frameTime > 60)
		{
			misspos *= -1;
			startMissTime = game_->getTime();
			frame++;
		}
		if (frame == 15)
		{
			miss = false;
		}

	}
	if (vs)
	{
		Uint32 frameTime = game_->getTime() - startVsTime;
		if (frameTime > 1000 && !vsR)
		{
			vsR = true;
			killPosX = game_->setHorizontalScale(500);
			string text;
			SDL_Color color ;
			if (win)
			{
				color = { 0,255,0,255 };
				killPosX  += 250;
				 text = "Congratulations";
			}
			else
			{
				color = { 0,255,255,255 };
				 text = "Frustrations";
			}
			startVsTime = game_->getTime();
			
			

			vsTex->loadFromText(game_->getRenderer(), text, game_->getFontMngr()->getFont(Resources::FontId::Beaulieux), color);
		}
		else if (frameTime > 200 && vsR && frameKill <5)
		{
			frameKill++;
			startVsTime = game_->getTime();

		}
		else if (frameKill == 5 && frameTime > 500)
		{
			vs = false;
			vsR = false;

		}


	}
	

}

void AnimationManager::draw()
{

	if (vibracion)		
		renderVibration();
	if (reward)			renderReward();
	if (transicion)  	renderTransicion();
	if (receiveDamage) 	renderDamage();
	if (miss) 	renderMiss();
	if (vs) renderKillEnemy();
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

void AnimationManager::showDamage(int dama, Resources::TextureId heroTexId)
{

	receiveDamage = true;
	startDamageTime = game_->getTime();
	heroTex = game_->instance()->getTextureMngr()->getTexture(heroTexId);

	string text = "- " + to_string(dama) + " Bloods";;
	SDL_Color color = { 255,255,0,255 };
	damageTex->loadFromText(game_->getRenderer(), text, game_->getFontMngr()->getFont(Resources::FontId::Beaulieux), color);

}
void AnimationManager::showMiss(bool enemy)
{
	frame = 0;
	startMissTime = game_->getTime();
	miss = true;
	SDL_Color color;
	string text;
	if (enemy)
	{
		color = { 0,255,0,255 };
		text = "Miss!!";;
	}
	else
	{
		color = { 255, 200, 0, 255 };
		text = "  Miss  ";;
	}
	
	
	missTex->loadFromText(game_->getRenderer(), text, game_->getFontMngr()->getFont(Resources::FontId::Beaulieux), color);
}
void AnimationManager::showKillEnemy(Resources::TextureId hero, Resources::TextureId enemy, bool wi)
{
	heroVsTex = game_->instance()->getTextureMngr()->getTexture(hero);
	EnemyVsTex = game_->instance()->getTextureMngr()->getTexture(enemy);
	startVsTime = game_->getTime();
	vs = true;
	win = wi;
	frameKill = 0;
	SDL_Color color;
	if (enemy) color = { 0,0,255,255 };
	string text = "         VS         ";

	vsTex->loadFromText(game_->getRenderer(), text, game_->getFontMngr()->getFont(Resources::FontId::Beaulieux), color);
}
void AnimationManager::renderDamage()
{
	int posX = game_->setHorizontalScale(1100);
	int posY = game_->setVerticalScale(500);
	SDL_Rect dest;

	dest = RECT(posX, posY, texSize, texSize);	heroTex->render(dest);		posX +=(texSize+ 10);
	dest = RECT(posX, posY, 90+texSize, texSize);	damageTex->render(dest);		

	

	

}

void AnimationManager::renderMiss()
{
	int posX = game_->setHorizontalScale(1200);
	int posY = game_->setVerticalScale(100);
	SDL_Rect dest;

	dest = RECT(posX+misspos, posY+misspos, 140, 60);	missTex->render(dest);		
}

void AnimationManager::renderKillEnemy()
{
	int posX = game_->setHorizontalScale(500);
	int posY = game_->setVerticalScale(100);
	SDL_Rect dest;

	dest = RECT(posX, posY, 55, 55);	heroVsTex->render(dest); posX += 80;
	dest = RECT(posX, posY, 150, 50);	vsTex->render(dest); posX += 170;
	double clipw = EnemyVsTex->getWidth() / 4;
	double cliph = EnemyVsTex->getHeight();
	SDL_Rect clip = RECT(0, 0, clipw,cliph);
	dest = RECT(posX , posY , 70, 70);	EnemyVsTex->render(dest,clip);

	if (vsR)
	{
		clipw = KillTex->getWidth() / 6;
		cliph = KillTex->getHeight();
		clip = RECT(frameKill*clipw,0,  clipw,cliph);

		dest = RECT(killPosX, posY, 70, 70); 
		KillTex->render(dest, clip);
	}

}

void AnimationManager::showReward(int exp_, int gold_, int mana_, int health_, bool chestKey_)
{
	exp = exp_;
	gold = gold_;
	manaPotions = mana_;
	healthPotions = health_;
	chestKey = chestKey_;
	levelKey = false;
	noKeys = false;

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

	if (chestKey) {
		text = "x1";
		color = { 255,255,255,225 };
		keyNumTex->loadFromText(game_->getRenderer(), text, game_->getFontMngr()->getFont(Resources::FontId::Beaulieux), color);
	}


}

void AnimationManager::showLevelKey()
{
	exp = 0;
	gold = 0;
	manaPotions = 0;
	healthPotions = 0;
	chestKey = false;
	levelKey = true;
	noKeys = false;

	reward = true;
	rewardPosY = game_->setVerticalScale(500);

	string text;
	SDL_Color color;

	text = "x1";
	color = { 255,255,255,225 };
	keyNumTex->loadFromText(game_->getRenderer(), text, game_->getFontMngr()->getFont(Resources::FontId::Beaulieux), color);
}

void AnimationManager::showNoKeys()
{
	exp = 0;
	gold = 0;
	manaPotions = 0;
	healthPotions = 0;
	chestKey = false;
	levelKey = false;
	noKeys = true;

	reward = true;
	rewardPosY = game_->setVerticalScale(500);

	string text;
	SDL_Color color;

	text = "x0";
	color = { 0,0,0,225 };
	keyNumTex->loadFromText(game_->getRenderer(), text, game_->getFontMngr()->getFont(Resources::FontId::Beaulieux), color);
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
	if (exp > 0) { dest = RECT(pos, rewardPosY, width, 50);  	expTex->render(dest);		pos += width + 20; }
	
	
	width = 120;
	if (gold > 99)
		width = 130;

	//Coins
	if (gold > 0) { dest = RECT(pos, rewardPosY, width, 50);	goldTex->render(dest);		pos += width + 20; }

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

	//Keys
	if (chestKey) {
		dest = RECT(pos, rewardPosY, width, 50);	keyTex->render(dest);			pos += width + 20;
		dest = RECT(pos, rewardPosY, width, 50);	keyNumTex->render(dest);		pos += width + 20;
	}

	if (levelKey) {
		dest = RECT(pos, rewardPosY, width, 50);	keyLevelTex->render(dest);		pos += width + 20;
		dest = RECT(pos, rewardPosY, width, 50);	keyNumTex->render(dest);		pos += width + 20;
	}

	if (noKeys) {
		dest = RECT(pos, rewardPosY, width, 50);	noKeysTex->render(dest);		pos += width + 20;
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

