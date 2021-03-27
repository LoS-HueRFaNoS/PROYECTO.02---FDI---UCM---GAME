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
        ButtonCtrl(Game* g) : Component(ecs::ButtonCtrl),
            ih_(nullptr),
            tr_(nullptr),
            speed_(10.0),
            g_(g),
            buttonRect_(nullptr),
            mousePointer_(nullptr)
        {

        };
        
        virtual ~ButtonCtrl(){
            delete buttonRect_; buttonRect_ = nullptr;
            delete mousePointer_; mousePointer_ = nullptr;
        }

        inline void setSpeed(float speed) {
            speed = speed;
        }

        void init() override {
            tr_ = GETCMP1_(Transform);
            assert(tr_ != nullptr);

            ih_ = InputHandler::instance();

            Vector2D pos = tr_->getPos();
            buttonRect_ = new SDL_Rect{ (int)pos.getX(), (int)pos.getY(), (int)tr_->getW(), (int)tr_->getH() };
        }

        void update() override {
            game_->getWindowHeight();
            if (ih_->mouseButtonEvent()) {
                if (ih_->getMouseButtonState((InputHandler::MOUSEBUTTON)0)) {

                    delete mousePointer_;
                    Vector2D mouse = ih_->getMousePos();
                    mousePointer_ = new SDL_Point{ (int)mouse.getX(), (int)mouse.getY() };

                    if (SDL_PointInRect(mousePointer_, buttonRect_)) {
                        //tr_->setVelY(-speed_); //
                        static_cast<Button*>(entity_)->click(g_);
                    }
                }
            }
        }

    private:
        InputHandler* ih_;
        Game* g_;
        Transform* tr_;
        float speed_;

        SDL_Rect* buttonRect_;
        SDL_Point* mousePointer_ = nullptr;
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