#pragma once

#include "Component.h"
#include "Texture.h"
#include "Transform.h"
#include "Entity.h"

typedef unsigned int uint;

class Sprite : public Component {
public:
	Sprite(Texture* tex, uint r, uint c, bool hide = false, bool marco = false) :
		Component(ecs::Sprite),
		tr_(nullptr), //
		tex_(tex), //
		row(r),
		col(c),
		hide_(hide),
		marco_(marco)
	{}

	virtual ~Sprite() {
	}

	void init() override {
		tr_ = entity_->getComponent<Transform>(ecs::Transform);
		assert(tr_ != nullptr);
	}

	void draw() override {
		if (!hide_) {
			SDL_Rect dest;
			SDL_Rect clip;
			if (!marco_) {
				dest = { int(tr_->getPos().getX()), int(tr_->getPos().getY()), int(tr_->getW()), int(tr_->getH()) };
				clip = { int(row), int(col), tex_->getWidth() / 4, tex_->getHeight() }; // (width / 4)
			}
			else {
				double h = 5; // game_->setVerticalScale(5);
				double w = h;
				dest = { int(tr_->getPos().getX() - w), int(tr_->getPos().getY() - h), int(tr_->getW() + w * 2), int(tr_->getH() + h * 2) };
				clip = { int(row), int(col), tex_->getWidth(), tex_->getHeight() };
			}		
			tex_->render(dest, clip);
		}
	}

	void avanza() { row = row + tex_->getHeight(); };
	bool get() { return (row > 0 && int(row) < tex_->getHeight() * 2); };
	void reset() { row = 0; };
	void setHide(bool set) { hide_ = set; };

private:
	Transform* tr_;
	Texture* tex_;
	uint row;
	uint col;
	bool hide_;
	bool marco_;
};