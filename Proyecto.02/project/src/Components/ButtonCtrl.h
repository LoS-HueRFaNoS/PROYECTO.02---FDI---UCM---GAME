#pragma once
#include "../GameObjects/Button.h"
#include "../Utilities/InputHandler.h"
#include "Transform.h"


class ButtonCtrl : public Component
{
public:
	ButtonCtrl(Button* b) :
		Component(ecs::ButtonCtrl), ih_(nullptr), button_(b) {};
	virtual ~ButtonCtrl() {
	}

	void init() override {
		ih_ = InputHandler::instance();
	}

	void update() override {
		if (ih_->mouseButtonEvent()) {
			uint e = ih_->getMouseButtonState(InputHandler::LEFT);
			Vector2D pos_ = ih_->getMousePos();
			SDL_Point p_ = { (int)pos_.getX(), (int)pos_.getY() };
			Transform* tr_ = entity_->getComponent<Transform>(ecs::Transform);
			SDL_Rect rect_ = { tr_->getPos().getX(), tr_->getPos().getY(), tr_->getW(), tr_->getH() };
			// mouse event
			if (!e) {
				if (SDL_PointInRect(&p_, &rect_)) {
					button_->click(); // click
				}
			}
		}
	}

private:
	InputHandler* ih_;
	Button* button_;
};
