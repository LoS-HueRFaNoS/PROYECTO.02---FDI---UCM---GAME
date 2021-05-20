// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../ecs/Entity.h"
#include "../ecs/Component.h"
#include "../Structures/Texture.h"

#include "Transform.h"

class Image: public Component {
public:
	Image(Texture* tex) :
		Component(ecs::Image),
		tr_(nullptr), //
		tex_(tex), //
		hide(false)
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
			SDL_Rect dest = { int(tr_->getPos().getX()), int(tr_->getPos().getY()), int(tr_->getW()), int(tr_->getH()) };
			tex_->render(dest, tr_->getRot());
		}
	}

	void setHide(bool set) { hide = set; };

	Texture* getTexture() { return tex_; };
	void setTexture(Texture* txt) { tex_ = txt; };

private:
	Transform *tr_;
	Texture *tex_;
	bool hide;
};