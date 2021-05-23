#pragma once

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../Structures/Texture.h"
#include "../Components/Transform.h"

typedef unsigned int uint;

// habilitado para funcionar de forma lineal y horizontal, se podria expandir a cuadriculas o de forma vertical.
class Sprite : public Component {
public:
	Sprite(Texture* tex, uint r, uint c, uint nFr = 2, bool hide = false/*, bool marco = false*/) :
		Component(ecs::Sprite),
		tr_(nullptr), //
		tex_(tex), //
		row(r),
		col(c),
		NUM_FRAMES(nFr),
		hide_(hide)
		//marco_(marco)
	{}

	virtual ~Sprite() {
	}

	void init() override {
		tr_ = entity_->getComponent<Transform>(ecs::Transform);
		assert(tr_ != nullptr);
	}

	void update() override {
		
	}

	void draw() override {
		if (!hide_) {
			SDL_Rect dest;
			SDL_Rect clip;

			//if (!marco) {
				dest = { int(tr_->getPos().getX()), int(tr_->getPos().getY()), int(tr_->getW()), int(tr_->getH()) };
				clip = { int(row), int(col), tex_->getWidth() / NUM_FRAMES, tex_->getHeight() }; // (width / 4)
			//}
			//else {
			//	double h = 5; // game_->setVerticalScale(5);
			//	double w = h;
			//	dest = { int(tr_->getPos().getX() - w), int(tr_->getPos().getY() - h), int(tr_->getW() + w * 2), int(tr_->getH() + h * 2) };
			//	clip = { int(row), int(col), tex_->getWidth(), tex_->getHeight() };
			//}		
			tex_->render(dest, clip);
		}
	}

	void avanza() { 
		row = row + tex_->getWidth() / NUM_FRAMES; 
	};
	bool get() { return (row >= 0 && int(row) < (tex_->getWidth() / NUM_FRAMES) * (NUM_FRAMES - 1)); };
	void reset() { row = 0; };

	void setHide(bool set) { hide_ = set; };
	bool getHide() { return hide_; };

private:
	Transform* tr_;
	Texture* tex_;
	uint row;
	uint col;
	bool hide_;
	//bool marco_;
	int NUM_FRAMES;
	uint st; // frame state
};