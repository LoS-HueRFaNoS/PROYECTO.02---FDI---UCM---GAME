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
            Component(ecs::ButtonCtrl), tr_(nullptr), speed_(10.0) {};
        virtual ~ButtonCtrl() {
        }


        inline void setSpeed(float speed) {
            speed = speed;
        }

        void init() override;

        void update() override {
            game_->getWindowHeight();
            if (ih_->keyDownEvent()) {
                if (ih_->isKeyDown(SDL_SCANCODE_UP)) {
                    tr_->setVelY(-speed_); //
                }
                else if (ih_->isKeyDown(SDL_SCANCODE_DOWN)) {
                    tr_->setVelY(speed_); //
                }
                else if (ih_->isKeyDown(SDL_SCANCODE_LEFT)) {
                    tr_->setVelX(-speed_); //
                }
                else if (ih_->isKeyDown(SDL_SCANCODE_RIGHT)) {
                    tr_->setVelX(speed_); //
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

