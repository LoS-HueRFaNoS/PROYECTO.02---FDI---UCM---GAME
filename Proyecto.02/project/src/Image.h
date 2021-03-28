// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "Component.h"
#include "Texture.h"

#include "Transform.h"

class Image: public Component {
public:
	Image(Texture* tex) :
		Component(ecs::Image),
		tr_(nullptr), //
		tex_(tex) //
	{}
	virtual ~Image() {
	}

	void init() override {
		tr_ = entity_->getComponent<Transform>(ecs::Transform);
		assert(tr_ != nullptr);
	}

	void draw() override {
		SDL_Rect dest = { tr_->getPos().getX(), tr_->getPos().getY(), tr_->getW(), tr_->getH() };
		tex_->render(dest, tr_->getRot());
	}

private:
	Transform *tr_;
	Texture *tex_;
};