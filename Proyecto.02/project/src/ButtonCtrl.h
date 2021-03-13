#pragma once
#include "Component.h"
#include <SDL.h>
#include <cassert>
#include "InputHandler.h"
#include "Entity.h"
#include "Transform.h"

class ButtonCtrl : public Component
{
    public:
        ButtonCtrl() :
            Component(ecs::ButtonCtrl), tr_(nullptr), speed_(10.0) { init(); }
        virtual ~ButtonCtrl() {
        }


        inline void setSpeed(float speed) {
            speed = speed;
        }

        void init() override {
            ih_ = InputHandler::instance();
        }

        void update() override {
            tr_ = entity_->getComponent<Transform>(ecs::Transform);
            assert(tr_ != nullptr);
            if (ih_->keyDownEvent()) {
                if (ih_->isKeyDown(SDL_SCANCODE_UP)) {
                    tr_->setVelY(-speed_);
                }
                else if (ih_->isKeyDown(SDL_SCANCODE_DOWN)) {
                    tr_->setVelY(speed_);
                }
                else if (ih_->isKeyDown(SDL_SCANCODE_LEFT)) {
                    tr_->setVelX(-speed_);
                }
                else if (ih_->isKeyDown(SDL_SCANCODE_RIGHT)) {
                    tr_->setVelX(speed_);
                }
                else if (ih_->isKeyDown(SDL_SCANCODE_SPACE)) {
                    tr_->setVelY(0.0f);
                    tr_->setVelX(0.0f);
                }
            }
        }

    private:
        InputHandler* ih_;
        Transform* tr_;
        float speed_;
    };

