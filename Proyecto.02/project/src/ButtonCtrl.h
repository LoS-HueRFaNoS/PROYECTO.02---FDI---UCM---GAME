#pragma once
#include "Component.h"
#include <SDL.h>
#include <cassert>
#include "InputHandler.h"
#include "Entity.h"
#include "Transform.h"
#include "Game.h"
#include "Button.h"

class ButtonCtrl : public Component
{
    public:
        ButtonCtrl(Game* g) :
            Component(ecs::ButtonCtrl), ih_(nullptr), tr_(nullptr), speed_(10.0), g_(g) {};
        virtual ~ButtonCtrl() {
        }

        inline void setSpeed(float speed) {
            speed = speed;
        }

        void init() override {
            tr_ = GETCMP1_(Transform);
            assert(tr_ != nullptr);
            ih_ = InputHandler::instance();
        }

        void update() override {
            game_->getWindowHeight();
            if (ih_->keyDownEvent()) {
                if (ih_->isKeyDown(SDL_SCANCODE_UP)) {
                    //tr_->setVelY(-speed_); //
                    static_cast<Button*>(entity_)->click(g_);
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
        Game* g_;
        Transform* tr_;
        float speed_;
    };



//Interfaz* i = new interfaz();
//i.deletePanel(nombrePanel)
////constructor
//switch (nombrePANEL)
//{
//case combate:
//	break;
//	case
//	default:
//		break;
//}