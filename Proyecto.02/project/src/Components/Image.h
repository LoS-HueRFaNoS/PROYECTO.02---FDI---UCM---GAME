// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../ecs/Entity.h"
#include "../ecs/Component.h"
#include "../Structures/Texture.h"

#include "Transform.h"

class Image: public Component {
public:
	Image(Texture* tex, bool animation = false) :
		Component(ecs::Image),
		tr_(nullptr), //
		tex_(tex), //
		hide(false),
		animation(animation)
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
	}


	void setHide(bool set) { hide = set; };

	Texture* getTexture() { return tex_; };
	void setTexture(Texture* txt) { tex_ = txt; };

private:
	Transform *tr_;
	Texture *tex_;
	bool hide;

	bool animation = true;
	SDL_Rect dest;
	bool limite = false;
	int cont = 0;
	int division = 0;
	int timer = 0;
};