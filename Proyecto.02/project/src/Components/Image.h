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

private:
	Transform *tr_;
	Texture *tex_;
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
};