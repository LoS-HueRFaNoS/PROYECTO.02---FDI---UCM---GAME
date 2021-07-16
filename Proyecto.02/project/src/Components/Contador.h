#pragma once

#include "../ecs/Entity.h"
#include "../ecs/Component.h"
#include "../Structures/Texture.h"
#include "../Managers/game/PartyManager.h"
#include "../Managers/game/InterfazManager.h"
#include "../Managers/TheElementalMaze.h"
#include "../GameObjects/SDL_Objects.h"

#include "Transform.h"

enum class PtnType { health, mana, resurrection };

class Contador : public Component {
public:
    Contador(PtnType type) :
        Component(ecs::Contador),
        hide(true),
        potionType_(type),
        nPots()
    {}
    virtual ~Contador() {
        li->disable();
    }

    void init() override {
        Transform* tr_ = entity_->getComponent<Transform>(ecs::Transform);
        assert(tr_ != nullptr);
        dest = RECT(
            tr_->getPos().getX() + tr_->getW() * 2 / 3,
            tr_->getPos().getY() + tr_->getH() * 2 / 3,
            tr_->getW() / 3,
            tr_->getH() / 3
        );

        PartyManager* p = TheElementalMaze::instance()->getPartyManager();
        InterfazManager* iMngr = TheElementalMaze::instance()->getUIManager();
        if (potionType_ == PtnType::health) nPots = p->healthPotions;
        else if (potionType_ == PtnType::mana) nPots = p->manaPotions;

        std::string s = to_string(nPots);
        SDL_Color color = { 255,255,255,255 };
        li = iMngr->addButton<Line>(dest, s, Resources::FontId::Beaulieux, color);
    }

    void update() override {
        uint aux = nPots;
        PartyManager* p = TheElementalMaze::instance()->getPartyManager();
        if (potionType_ == PtnType::health) nPots = p->healthPotions;
        else if (potionType_ == PtnType::mana) nPots = p->manaPotions;
        if (aux != nPots) swapCont();
    }

    void setHide(bool set) { hide = set; };
    void swapCont() {
        li->disable();
        std::string s = to_string(nPots);
        SDL_Color color = { 255,255,255,255 };
        InterfazManager* iMngr = TheElementalMaze::instance()->getUIManager();
        li = iMngr->addButton<Line>(dest, s, Resources::FontId::Beaulieux, color);
    };

private:
    PtnType potionType_;
    SDL_Rect dest;
    uint nPots;

    Line* li;
    bool hide;
};
