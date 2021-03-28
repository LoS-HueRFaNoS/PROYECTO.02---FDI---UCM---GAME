#pragma once

#include "Component.h"
#include "Texture.h"
#include "Transform.h"
#include "Entity.h"

typedef unsigned int uint;

class Sprite : public Component {
public:
	Sprite(Texture* tex, uint r, uint c) :
		Component(ecs::Sprite),
		tr_(nullptr), //
		tex_(tex), //
		row(r),
		col(c)
	{}
	virtual ~Sprite() {
	}

	void init() override {
		tr_ = entity_->getComponent<Transform>(ecs::Transform);
		assert(tr_ != nullptr);
	}

	void draw() override {
		SDL_Rect dest = { tr_->getPos().getX(), tr_->getPos().getY(), tr_->getW(), tr_->getH() };
		SDL_Rect clip = { row, col, tex_->getWidth() / 4, tex_->getHeight() };
		tex_->render(dest, clip);
	}

	void avanza() { row = row + tex_->getHeight(); };
	bool get() { return (row > 0 && row < tex_->getHeight() * 2); };
	void reset() { row = 0; };
private:
	Transform* tr_;
	Texture* tex_;
	uint row;
	uint col;
};