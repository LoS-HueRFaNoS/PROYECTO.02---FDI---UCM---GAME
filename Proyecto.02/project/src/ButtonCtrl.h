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
    ButtonCtrl(Game* g) :
        Component(ecs::ButtonCtrl), ih_(nullptr), g_(g) {};
    virtual ~ButtonCtrl() {
    }

    void init() override {
        ih_ = InputHandler::instance();
    }

    void update() override {
        game_->getWindowHeight();
        if (ih_->keyDownEvent()) {
            if (ih_->isKeyDown(SDL_SCANCODE_UP)) {
                static_cast<Button*>(entity_)->click(g_);
            }
        }
        if (ih_->mouseButtonEvent()) {
            uint e = ih_->getMouseButtonState(InputHandler::LEFT);
            Vector2D pos_ = ih_->getMousePos();
            SDL_Point p_ = { pos_.getX(), pos_.getY() };
            Transform* tr_ = entity_->getComponent<Transform>(ecs::Transform);
            SDL_Rect rect_ = { tr_->getPos().getX(), tr_->getPos().getY(), tr_->getW(), tr_->getH() };
            if (!e) {
                if (SDL_PointInRect(&p_, &rect_)) {
                    static_cast<Button*>(entity_)->click(g_);
                }
            }
        }
    }

private:
    InputHandler* ih_;
    Game* g_;
};