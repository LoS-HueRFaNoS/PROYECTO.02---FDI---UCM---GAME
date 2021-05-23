#pragma once
#include <SDL.h>
#include <cassert>
#include "../ecs/Component.h"
#include "../Utilities/InputHandler.h"
#include "Transform.h"
#include "Sprite.h"
#include "../Game.h"

class MouseCtrl : public Component
{
public:
    MouseCtrl() :
        Component(ecs::MouseCtrl), ih_(nullptr) {};
    virtual ~MouseCtrl() {
    }

    inline void setSpeed(float speed) {
        speed = speed;
    }

    void init() override {
        tr_ = GETCMP1_(Transform);
        assert(tr_ != nullptr);
        ih_ = InputHandler::instance();
        s_ = GETCMP1_(Sprite);
    }

    void update() override {
        game_->getWindowHeight();
        if (ih_->mouseMotionEvent()) {
            Vector2D pos = ih_->getMousePos();
            //pos.set(pos.getX() - tr_->getW()/ 2, pos.getY() - tr_->getH() / 2);
            pos.set(pos.getX(), pos.getY()); // nuevo cursor
            entity_->getComponent<Transform>(ecs::Transform)->setPos(pos);
        }

        if (ih_->mouseButtonEvent()) {
            float e = ih_->getMouseButtonState(InputHandler::LEFT);

            if (e) s_->avanza();
            else if (!e && !s_->get()) s_->reset();
        }           
    }

private:
    Sprite* s_;
    InputHandler* ih_;
    Transform* tr_;
    
};
