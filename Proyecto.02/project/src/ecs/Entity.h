#pragma once

#include <iostream>
#include <array>
#include "Component.h"
#include "Manager.h"
#include "../Managers/SDLGame.h"

class EntityManager;

class Entity {
public:
    Entity(SDLGame* game, EntityManager* mngr);
    virtual ~Entity();

    EntityManager* getEntityMangr() {
        return mngr_;
    }

    SDLGame* getSDLGame() {
        return game_;
    }

    template<typename T, typename ... TArgs>
    T* addComponent(TArgs&& ...mArgs) {
        T* c(new T(std::forward<TArgs>(mArgs)...));
        std::unique_ptr<Component> uPtr(c);
        components_.push_back(std::move(uPtr));
        componentsArray_[c->getId()] = c;
        c->setEntity(this);
        c->setGame(game_);
        c->init();
        return c;
    }

    void removeComponent(ecs::CmpIdType id) {
        //componentsArray_[id]->disable();
        for (auto it = components_.begin(); it != components_.end(); it++)
        {
            if ((*it).get()->getId() == id) {
                (*it)->disable();
            }
        }
    }

    template<typename T>
    T* getComponent(ecs::CmpIdType id) {
        return static_cast<T*>(componentsArray_[id]);
    }

    bool hasComponent(ecs::CmpIdType id) {
        return componentsArray_[id] != nullptr;
    }

    virtual void update() {
        if (!enabled || !active || pause) return;
        auto n = components_.size();
        for (auto i = 0u; i < n; i++)
        {
            if (isActive())
                components_[i]->update();
        }
        refresh();
    }

    virtual void draw() {
        if (!enabled) return;
        for (auto& c : components_) {
            if (isActive())
                c->draw();
        }
    }

    void refresh()
    {
        ecs::CmpIdType id = ecs::PanelTurns;
        for (auto it = components_.begin(); it != components_.end(); /**/)
        {
            if (!(*it).get()->isActive()) {
                id = (*it).get()->getId();
                it = components_.erase(it);
            }
            else it++;
        }

        componentsArray_[id] = nullptr;
    }

    // ocultar / mostrar
    void toggleEnabled() { enabled = !enabled; }

    // deshabilitar / delete
    void disable() {
        active = false;
        for (int i = 0; i < components_.size(); i++) {
            components_[i].get()->disable();
        }
    }
    bool isActive() const { return active; };

    // pause
    void togglePause() { pause = !pause; };
    void setPause() { pause = true; };
    void setContinue() { pause = false; };

protected:
    SDLGame* game_;
    EntityManager* mngr_;

    bool enabled;	// equivalente a hide / unhide
    bool active;	// se mantiene en memoria o se prepara para ser eliminado
    bool pause;		// cancela el update

    std::vector<unique_ptr<Component>> components_;
    std::array<Component*, ecs::maxComponents> componentsArray_ = {};
};