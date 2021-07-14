#pragma once
#include <SDL.h>
#include <cassert>
#include "../ecs/Component.h"
#include "../Utilities/SDL_macros.h"
#include "../GameObjects/SDL_Objects.h"
#include "../Managers/game/CombatManager.h"
#include "../Managers/game/PartyManager.h"
#include "../Managers/TheElementalMaze.h"

typedef unsigned int uint;

enum class BarType {
    health,
    mana,
    experience
};

class StateBar : public Component
{
public:
    StateBar(Character* c, BarType ty, SDL_Rect rct, bool num = false) :
        Component(ecs::StateBar), character_(c), type_(ty), rect(rct), background(rct), width_(rct.w), maxStat_(0), stAct_(0), aux_(0), color_(), color2_(), isNumber(num) {};
    virtual ~StateBar() {
        if (number_ != nullptr) { delete number_; number_ = nullptr; };
    }

    void init() override {
        assert(character_ != nullptr);
        setColors();
        spaceToFill = RECT(
            background.x + game_->setHorizontalScale(2),
            background.y + game_->setVerticalScale(2),
            background.w - game_->setHorizontalScale(2),
            background.h - game_->setVerticalScale(2)
        );
        if (isNumber) {
            number_ = new Line(game_, nullptr);
            number_->init(rect, to_string(character_->getCharacterSheet()->hitPoints()), src::Beaulieux, color_);
        }
        // initial values
        setValues();  
        setInitHPBar();
        aux2_ = 0.0;
    }

    void update() override {
        setValues();

        if (aux_ < stAct_) {
            aux_ = aux_ + 0.125;
            parpadeo();
        }
        else if (aux_ > stAct_) {
            aux_ = aux_ - 0.125;
            parpadeo();
        }

        if (aux_ == stAct_) color_.a = 255;

        if (!isNumber) {
            double fill = aux_ * 100.0 / maxStat_;    // porcentaje actual
            rect.w = int(fill * width_ / 100);          // ancho visible
        }
        else {
            number_->setLine(to_string(int(aux_)), src::Beaulieux, color_);
        }
    }

    void draw() override {
        if (!isNumber) {
            renderRects();
        }
        else {            
            number_->draw();
        }
    }

    bool equalHP_pair() { return aux_ == stAct_; }

private:
    SDL_Rect rect;          // rectangle for actual stat data
    SDL_Rect background;    // rectangle for background edge data
    SDL_Rect spaceToFill;   // rectangle for background data
    uint width_;            // max width size
    Character* character_;  // character reference
    BarType type_;          // type of data

    uint maxStat_;      // much amount of data
    uint stAct_;        // actual amount of data
    double aux_;        // auxiliar for animation and progresive decrement
    double aux2_;         // auxiliar for wink animation
    SDL_Color color_;   // data type color
    SDL_Color color2_;  // data backgorund type color

    bool isNumber;
    Line* number_ = nullptr;

private:
    void setInitHPBar() {
        TheElementalMaze* tem_ = TheElementalMaze::instance();
        CombatManager* cm_ = tem_->getCombatManager();

        Hero* h_ = dynamic_cast<Hero*>(character_);
        if (h_ == nullptr && cm_->getState() != ACTION_PHASE_SPELL && cm_->getState() != ACTION_PHASE_TARGET) { aux_ = stAct_; }
        else if (h_ != nullptr) { aux_ = 0.0; };
    }

    void setValues() {
        Hero* h_ = nullptr;
        switch (type_)
        {
        case BarType::health:
            maxStat_ = character_->getCharacterSheet()->maxHitPoints();
            stAct_ = character_->getCharacterSheet()->hitPoints();
            break;
        case BarType::mana:
            maxStat_ = character_->getCharacterSheet()->maxManaPoints();
            stAct_ = character_->getCharacterSheet()->manaPoints();
            break;
        case BarType::experience:
            h_ = dynamic_cast<Hero*>(character_);
            if (h_ != nullptr) {
                maxStat_ = h_->getExpMax();
                stAct_ = h_->getExp();
            }
            break;
        default:
            break;
        }        
    }

    void setColors() {
        // actual data color
        switch (type_)
        {
        case BarType::health:
            color_ = hex2sdlcolor("#DD0000FF");
            break;
        case BarType::mana:
            color_ = hex2sdlcolor("#0055FFFF");
            break;
        case BarType::experience:
            color_ = hex2sdlcolor("#BBBB00FF");
            break;
        default:
            break;
        }

        // background data color
        switch (type_)
        {
        case BarType::health:
            color2_ = hex2sdlcolor("#5E0000FF");
            break;
        case BarType::mana:
            color2_ = hex2sdlcolor("#001540FF");
            break;
        case BarType::experience:
            color2_ = hex2sdlcolor("#3B3B00FF");
            break;
        default:
            break;
        }
    }

    void renderRects() {
        SDL_SetRenderDrawColor(game_->getRenderer(), COLOREXP(color_));
        SDL_RenderFillRect(game_->getRenderer(), &background);
        SDL_SetRenderDrawColor(game_->getRenderer(), COLOREXP(color2_));        
        SDL_RenderFillRect(game_->getRenderer(), &spaceToFill);
        SDL_SetRenderDrawBlendMode(game_->getRenderer(), SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(game_->getRenderer(), COLOREXP(color_));
        SDL_RenderFillRect(game_->getRenderer(), &rect);
        SDL_SetRenderDrawBlendMode(game_->getRenderer(), SDL_BLENDMODE_NONE);
    }

    void parpadeo() {
        aux2_ = aux2_ + 0.125;
        if (aux2_ == 2.25) {
            if (color_.a == 255) color_.a = 75;
            else color_.a = 255;
            aux2_ = 0;
        }
    }

};
