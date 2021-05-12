#pragma once
#include "Component.h"
#include <SDL.h>
#include <cassert>
#include "SDL_macros.h"
#include "../TheElementalMaze.h"
#include "CombatManager.h"
#include "PartyManager.h"

typedef unsigned int uint;

enum BarType {
    health,
    mana,
    experience
};

class StateBar : public Component
{
public:
    StateBar(BarType ty, uint n, SDL_Rect rct) :
        Component(ecs::StateBar), type_(ty), numHero_(n), rect(rct), width_(rct.w), maxStat_(), stAct_(), color_(), heroes() {};
    virtual ~StateBar() {
    }

    void init() override {
        PartyManager* p = TheElementalMaze::instance()->getPartyManager();
        assert(p != nullptr);
        heroes = p->getHeroes();
    }

    void update() override {
        switch (type_)
        {
        case health:
            maxStat_ = heroes[numHero_]->getCharacterSheet()->maxHitPoints();
            stAct_ = heroes[numHero_]->getCharacterSheet()->hitPoints();
            color_ = hex2sdlcolor("#DD0000FF");
            break;
        case mana:
            maxStat_ = heroes[numHero_]->getCharacterSheet()->maxManaPoints();
            stAct_ = heroes[numHero_]->getCharacterSheet()->manaPoints();
            color_ = hex2sdlcolor("#0055FFFF"); //5500AAFF
            break;
        case experience:
            maxStat_ = heroes[numHero_]->getExpMax();
            stAct_ = heroes[numHero_]->getExp();
            color_ = hex2sdlcolor("#BBBB00FF"); //00EEFFFF
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
    SDL_Rect rect;
    uint width_;
    std::vector<Hero*> heroes;
    BarType type_;
    uint numHero_;
    uint maxStat_;
    uint stAct_;
    SDL_Color color_;
};
