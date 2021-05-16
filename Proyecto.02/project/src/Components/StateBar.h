#pragma once
#include <SDL.h>
#include <cassert>
#include "../ecs/Component.h"
#include "../Utilities/SDL_macros.h"
#include "../Managers/game/CombatManager.h"
#include "../Managers/game/PartyManager.h"
#include "../Managers/TheElementalMaze.h"

typedef unsigned int uint;

enum BarType {
    health,
    mana,
    experience
};

class StateBar : public Component
{
public:
    StateBar(Character* c, BarType ty, SDL_Rect rct) :
        Component(ecs::StateBar), character_(c), type_(ty), rect(rct), width_(rct.w), maxStat_(), stAct_(), color_() {};
    virtual ~StateBar() {
    }

    void init() override {
        assert(character_ != nullptr);
        switch (type_)
        {
        case health:
            color_ = hex2sdlcolor("#DD0000FF");
            break;
        case mana:
            color_ = hex2sdlcolor("#0055FFFF");
            break;
        case experience:
            color_ = hex2sdlcolor("#BBBB00FF");
            break;
        default:
            break;
        }
    }

    void update() override {
        Hero* h_ = nullptr;
        switch (type_)
        {
        case health:
            maxStat_ = character_->getCharacterSheet()->maxHitPoints();
            stAct_ = character_->getCharacterSheet()->hitPoints();
            break;
        case mana:
            maxStat_ = character_->getCharacterSheet()->maxManaPoints();
            stAct_ = character_->getCharacterSheet()->manaPoints();
            break;
        case experience:
            h_ = dynamic_cast<Hero*>(character_);
            if (h_ != nullptr) {
                maxStat_ = h_->getExpMax();
                stAct_ = h_->getExp();
            }            
            break;
        default:
            break;
        }

        double fill = stAct_ * 100.0 / maxStat_;    // porcentaje actual
        rect.w = int(fill * width_ / 100);          // ancho visible
    }

    void draw() override {
        SDL_SetRenderDrawColor(game_->getRenderer(), COLOREXP(color_));
        SDL_RenderFillRect(game_->getRenderer(), &rect);
    }

private:
    SDL_Rect rect;          // general position and size
    uint width_;            // max width size
    Character* character_;  // character reference
    BarType type_;          // type of data

    uint maxStat_;      // much amount of data
    uint stAct_;        // actual amount of data
    SDL_Color color_;   // data type color
};
