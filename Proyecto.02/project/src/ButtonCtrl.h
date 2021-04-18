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
            SDL_Rect rect_ = { tr_->getPos().getX(), tr_->getPos().getY(), tr_->getW(), tr_->getH() };
            // mouse event
            if (!e) {
                if (SDL_PointInRect(&p_, &rect_)) {
                    button_->click();
                    //ButtonType* b2t = static_cast<ButtonMovement*>(entity_); // on/off
                    //Button* b = static_cast<Button*>(entity_); // normal
                    //if (b != nullptr && button_ != nullptr)
                    //    b->click(button_, im_);
                    //else {
                    //    
                    //    if (b != nullptr)
                    //        b->click(button_, im_);
                    //}
                }
            }
        }
    }

private:
    InterfazManager* im_;
    InputHandler* ih_;
    Button* button_;
    //cb* button_;
};
