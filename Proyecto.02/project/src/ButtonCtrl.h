#pragma once
#include "Component.h"
#include <SDL.h>
#include <cassert>
#include "InputHandler.h"
#include "Game.h"
#include "Button.h"
#include "Transform.h"

class ButtonCtrl : public Component
{
public:
    ButtonCtrl(Game* g, Button* b) :
        Component(ecs::ButtonCtrl), ih_(nullptr), g_(g), button_(b) {};
    virtual ~ButtonCtrl() {
    }

    void init() override {
        ih_ = InputHandler::instance();
        //Vector2D pos = tr_->getPos();
        //buttonRect_ = new SDL_Rect{ (int)pos.getX(), (int)pos.getY(), (int)tr_->getW(), (int)tr_->getH() };
    }

    void update() override {
        if (ih_->mouseButtonEvent()) {
            uint e = ih_->getMouseButtonState(InputHandler::LEFT);
            Vector2D pos_ = ih_->getMousePos();
            SDL_Point p_ = { (int)pos_.getX(), (int)pos_.getY() };
            Transform* tr_ = entity_->getComponent<Transform>(ecs::Transform);
            SDL_Rect rect_ = { tr_->getPos().getX(), tr_->getPos().getY(), tr_->getW(), tr_->getH() };
            if (!e) {
                if (SDL_PointInRect(&p_, &rect_)) {
                    //cout << "buttonCTRL_Test" << endl;

                    button_->click(g_);

                    /*Button* p = dynamic_cast<Button*>(entity_);
                    if (p) p->click(g_);*/
                }
            }
        }
    }

private:
    InputHandler* ih_;
    Game* g_;

    Button* button_;
};
