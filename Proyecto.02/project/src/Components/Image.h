// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../ecs/Entity.h"
#include "../ecs/Component.h"
#include "../Structures/Texture.h"
#include "../Templates/Resources.h"
#include "../Managers/game/CombatManager.h"
#include "../Managers/TheElementalMaze.h"

#include "Transform.h"

class Image: public Component {
public:
	Image(Texture* tex, bool animation = false,bool damage=false) :
		Component(ecs::Image),
		tr_(nullptr), //
		tex_(tex), //
		hide(false),
		animation(animation),
		damaged(damage)
	{}
	virtual ~Image() {
		tex_ = nullptr;
	}

	void init() override {
		tr_ = entity_->getComponent<Transform>(ecs::Transform);
		assert(tr_ != nullptr);
	}

	void draw() override {
		if (!hide) {
			if (animation) 
				renderIdle(dest);
			

			else {
				dest = { int(tr_->getPos().getX()), int(tr_->getPos().getY()), int(tr_->getW()), int(tr_->getH()) };
				tex_->render(dest, tr_->getRot());
				if (heroptr)
				{
					showHeroUpdate();
				}

			}
		}
	}

	bool Limite(bool& avanza, int rectX, int textW) {

		if (rectX >= textW * 3 / 4 || rectX <= 0) {

			avanza = !avanza;
		}

		return avanza;
	}

	void renderIdle(SDL_Rect& dest) {

		SDL_Rect clip;

		dest = { int(tr_->getPos().getX()), int(tr_->getPos().getY()), int(tr_->getW()), int(tr_->getH()) };
		clip = { int(division), int(0), tex_->getWidth() / 4, tex_->getHeight() };
		tex_->render(dest, clip);

		if (timer > 35) {
			if (!limite) {
				division += tex_->getWidth() / 4;
			}
			else
				division -= tex_->getWidth() / 4;

			limite = Limite(limite, division, tex_->getWidth());

			timer = 0;
		}
		else timer++;


		if (!enemyInd) {
			return;
		}
		if (damaged || enemyInd->isDamaged()) {
			damaged = true;
			renderDamage(Resources::slash);
		}
	}
	void showHeroUpdate()
	{
		if (heroptr->isDamaged())
		{
			renderHeroD = true;
			frame = 0;
			startDamageTime = game_->getTime();
		}
		else if (heroptr->isLevelUp())
		{
			renderHeroL = true;
			startLevelUpTime= game_->getTime();
		}
		if (renderHeroD)
		{

			Uint32 frameTime = game_->getTime() - startDamageTime;
			if (frameTime > 100)
			{
				frame++;
				startDamageTime = game_->getTime();
			}
			if (frame == 6)
			{
				renderHeroD = false;
			}
			else
			{
				renderHeroDamage();
			}
		}
		if (renderHeroL)
		{
			Uint32 frameTime = game_->getTime() - startLevelUpTime;
			if (frameTime > 1000) renderHeroL = false;
			else {
				string text="";
				int w = int(tr_->getH() / 10);
				int tim = frameTime / 100;
				if (tim == 0){ text = "Level";}
				else if (tim == 1 || tim == 2){ text = "Level +    ";}
				else if (tim == 3 || tim == 4){ text = "Level ++  ";}
				else if (tim == 5 || tim == 6){ text = "Level +++";}
				else if (tim == 7 || tim == 8 || tim == 9){ text = "Level " + to_string( heroptr->getLevel())+"   " ; }
				renderLevel(text, tim*w);
			}
		}
	}
	void renderLevel(string text, int posY)
	{
		if (textLevelUp == nullptr) 
			textLevelUp = new Texture();
		SDL_Color color;
		color = { 255, 255, 0, 255 };

		textLevelUp->loadFromText(game_->getRenderer(), text, game_->getFontMngr()->getFont(Resources::FontId::Beaulieux), color);

		dest = { int(tr_->getPos().getX()) , int(tr_->getPos().getY()) + int(tr_->getH()) - posY, int(tr_->getW()), int(tr_->getH()/3) };

		textLevelUp->render(dest);

	}
	void renderHeroDamage()
	{
		SDL_Rect clip;
		Texture* textureSlash = game_->getTextureMngr()->getTexture(Resources::slashHero);

		dest = RECT(int(tr_->getPos().getX()), int(tr_->getPos().getY()), int(tr_->getW()), int(tr_->getH()));
		double clipw = textureSlash->getWidth() / 6;
		double cliph = textureSlash->getHeight();
		clip = RECT(frame * clipw, 0, clipw, cliph);
		textureSlash->render(dest, clip);

	}

	void renderDamage(Resources::TextureId image) {

		SDL_Rect clip;
		Texture* textureSlash = game_->getTextureMngr()->getTexture(image);


		dest = { int(tr_->getPos().getX()), int(tr_->getPos().getY()), int(tr_->getW()), int(tr_->getH()) };
		clip = { int(divisionSlash), int(0), textureSlash->getWidth() / 6, textureSlash->getHeight() };

		textureSlash->render(dest, clip);

		if (timerSlash > 15) {
			if (divisionSlash < textureSlash->getWidth() * 5 / 6) {
				divisionSlash += textureSlash->getWidth() / 6;

			}
			else {
				divisionSlash = 0;
				damaged = false;
			}
			timerSlash = 0;

		}
		else timerSlash++;

	}


	void setHide(bool set) { hide = set; };

	Texture* getTexture() { return tex_; };
	void setTexture(Texture* txt) { tex_ = txt; };

	void setEnemy(Enemy* enemyN) {
		enemyInd = enemyN;
	};

	void setHero(Hero* her)
	{
		heroptr = her;
	}

private:
	Transform *tr_;
	Texture *tex_;
	Texture* textLevelUp = nullptr;
	bool hide;

	bool animation = true;
	bool damaged = false;
	SDL_Rect dest;
	bool limite = false;
	int cont = 0;
	int division = 0;
	int divisionSlash = 0;
	int timer = 0;
	int timerSlash = 0;
	Enemy* enemyInd = nullptr;
	Hero* heroptr = nullptr;
	Uint32 startDamageTime = 0;
	Uint32 startLevelUpTime = 0;
	int frame = 0;
	bool renderHeroD = false;
	bool renderHeroL = false;

};