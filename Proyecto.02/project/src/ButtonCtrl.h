#pragma once
#include "Button.h"
#include "InputHandler.h"
#include "Transform.h"
using cb = CallBackOnClick;

class ButtonCtrl : public Component
{
public:
    ButtonCtrl(InterfazManager* im, cb* b) :
        Component(ecs::ButtonCtrl), ih_(nullptr), im_(im), button_(b) {};
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
            SDL_Rect rect_ = { int(tr_->getPos().getX()), int(tr_->getPos().getY()), int(tr_->getW()), int(tr_->getH()) };
            // mouse event
            if (!e) {
                if (SDL_PointInRect(&p_, &rect_)) {
                    //button_->click(im_);
                    button_(im_); // click
                }
            }
        }
    }

private:
    InterfazManager* im_;
    InputHandler* ih_;
    //Button* button_;
    cb* button_;
};
