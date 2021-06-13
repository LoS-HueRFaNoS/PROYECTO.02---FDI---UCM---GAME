#pragma once
#include <SDL.h>
#include <cassert>
#include "../ecs/Component.h"
#include "../Components/Sprite.h"
#include "../Managers/game/CombatManager.h"
#include "../Managers/TheElementalMaze.h"
class AnimVibration :   public Component
{
public:
    AnimVibration(SDL_Rect des, Resources::TextureId imag) :Component(ecs::AnimVibration),dest(des),image(imag){};
    void draw() override {
        CombatManager* cbManager = GETCMP2(TheElementalMaze::instance(), CombatManager);
        if (cbManager->getDrawDanger())
        {
            game_->instance()->getTextureMngr()->getTexture(image)->render(dest);
        }
    }
private:
    SDL_Rect dest;
    Resources::TextureId image;
};
