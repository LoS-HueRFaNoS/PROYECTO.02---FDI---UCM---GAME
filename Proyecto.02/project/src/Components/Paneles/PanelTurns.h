#pragma once
#include <string>
#include "../../ecs/Component.h"
#include "../../GameObjects/PanelTurnos.h"

class PanelTurns : public Component
{
private:
    PanelTurnos* pan_;

public:
    PanelTurns(SDLGame* game) : Component(ecs::PanelTurns) {
        pan_ = new PanelTurnos(game);
        pan_->Init();
    };
    virtual ~PanelTurns() {};

    void update() override { pan_->update(); };
    void draw() override {
        pan_->draw();
    };

};