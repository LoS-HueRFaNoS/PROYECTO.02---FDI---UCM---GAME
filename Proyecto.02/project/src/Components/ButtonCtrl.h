#pragma once
#include "Sprite.h"
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
		s_ = GETCMP1_(Sprite);
		isMousePointerInRect_ = false; wasMousePointerInRect_ = false;
	}

	void update() override {
		// variables necesarias:
		uint e = ih_->getMouseButtonState(InputHandler::LEFT);
		Vector2D pos_ = ih_->getMousePos();
		SDL_Point p_ = { (int)pos_.getX(), (int)pos_.getY() };
		Transform* tr_ = entity_->getComponent<Transform>(ecs::Transform);
		SDL_Rect rect_ = { int(tr_->getPos().getX()), int(tr_->getPos().getY()), int(tr_->getW()), int(tr_->getH()) };

		// mouse button event
		if (ih_->mouseButtonEvent()) 
		{
			if (SDL_PointInRect(&p_, &rect_)) 
			{
				// effect click
				if (!e) {
					button_->click(); // click
				}

				// animation (click)
				if (s_->get()) {
					s_->avanza();
				}
			}
		}

		// animation (hover)
		if (ih_->mouseMotionEvent())
		{
			if (SDL_PointInRect(&p_, &rect_))
			{
				if (!wasMousePointerInRect_) {
					isMousePointerInRect_ = true;
					button_->pointerEntered();
				}

				s_->setHide(false);
			}
			else
			{
				if (wasMousePointerInRect_) {
					isMousePointerInRect_ = false;
					button_->pointerExited();
				}

				if (s_->get())
				{
					s_->setHide(true);
				}
			}

			/*if (isMousePointerInRect_) button_->pointerEntered();
			else button_->pointerExited();*/

			wasMousePointerInRect_ = isMousePointerInRect_;
		}
	}

private:
	InputHandler* ih_;
	Button* button_;
	Sprite* s_;

	bool wasMousePointerInRect_;
	bool isMousePointerInRect_;
};
