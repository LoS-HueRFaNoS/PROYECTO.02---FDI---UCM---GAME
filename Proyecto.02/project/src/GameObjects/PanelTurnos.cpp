#include "PanelTurnos.h"

#include "Character.h"
#include "SDL_Objects.h"
#include "Character.h"
#include "../ecs/Entity.h"
#include "../Utilities/textures_box.h"
#include "../Components/Rectangle.h"
#include "../Components/StateBar.h"
#include "../Managers/game/CombatManager.h"
#include "../Managers/game/PartyManager.h"
#include "../Managers/TheElementalMaze.h"

using namespace textures_box;

void PanelTurnos::drawFondo()
{
    fondo_ = addEntity();
    fondo_->addComponent<Transform>(fondo_rect);
    fondo_->addComponent<Rectangle_cmpt>(SDL_Color{ 10,10,10,255 });

    turns_ = addEntity();
    turns_->addComponent<Transform>(turns_rect);
    turns_->addComponent<Rectangle_cmpt>(SDL_Color{ 000,200,200,150 });

    next_ = addEntity();
    next_->addComponent<Transform>(next_rect);
    next_->addComponent<Rectangle_cmpt>(SDL_Color{ 225,225,000,200 });

    nextTurn_ = addEntity();
    nextTurn_->addComponent<Transform>(SDL_Rect(nextTurn_rect));
    nextTurn_->addComponent<Rectangle_cmpt>(SDL_Color{ 100,100,000,150 });

}

void PanelTurnos::Init()
{
    // DATOS

    icono = RECT(
        pan.fcx + (pan.cw + 2 * pan.ew) - pan.ew,
        pan.fcy - pan.eh,
        pan.cw + 2 * pan.ew,
        pan.ch + 2 * 2 * pan.eh
    );

    number = RECT(
        pan.fcx,
        pan.fcy,
        pan.cw,
        pan.ch
    );

    bar = RECT(
        pan.fcx - pan.ew,
        pan.fcy + (pan.ch + 2 * pan.eh) + pan.ch * 1 / 5 + pan.eh,
        pan.cw + 2 * (pan.cw + 2 * pan.ew) + 2 * pan.ew,
        pan.ch * 1 / 5
    );

    first = RECT(
        pan.lcx + pan.ew,
        pan.lcy,
        pan.cw - 2 * pan.ew,
        pan.ch
    );

    first_bar = RECT(
        pan.lcx - pan.ew / 2,
        pan.lcy + pan.ch + pan.eh / 2,
        pan.cw + pan.ew,
        pan.eh / 2
    );

    // FONDO

    fondo_rect = RECT(pan.x, pan.y, pan.w, pan.h);

    next_rect = RECT(
        pan.lcx - pan.ew,
        pan.lcy - pan.eh / 2,
        pan.cw + 2 * pan.ew,
        pan.ch + 2 * pan.eh
    );

    nextTurn_rect = RECT(
        pan.lcx - pan.ew - 2 * (pan.cw + 2 * pan.ew),
        pan.lcy - pan.eh / 2,
        pan.cw + 2 * pan.ew + (pan.cw + 2 * pan.ew),
        pan.ch + 2 * pan.eh
    );

    turns_rect = RECT(
        nextTurn_rect.x - pan.ew / 2,
        nextTurn_rect.y - pan.ew / 2,
        nextTurn_rect.w + 2 * pan.ew / 2 + (pan.cw + 2 * pan.ew),
        nextTurn_rect.h + 2 * pan.eh / 2
    );

    // Panel Heroes: Primer Heroe
    heroe_turn = RECT(
        game_->setHorizontalScale(1513),
        game_->setVerticalScale(363),
        game_->setHorizontalScale(334),
        game_->setVerticalScale(84)
    );
    offsetY = heroe_turn.y;
    espaceH = game_->setVerticalScale(80);

}

void PanelTurnos::update()
{
    ElementManager::update();

    TheElementalMaze* tem_ = TheElementalMaze::instance();
    CombatManager* cm_ = tem_->getCombatManager();

    if (refresh_done && cm_->getState() != last_state)
    {
        refresh_done = false;
    }

    if (!refresh_done)
    {
        if (cm_->getState() == START_TURN)
        {
            ElementManager::removeEntities();
            drawFondo();

            character_ = cm_->getCurrentCharacter();
            turnsList_ = cm_->getCurrentTurnsList();

            drawCurrentCharacter();
            drawCurrentTurnList();
            drawCurrentInPanelHeroes();

            refresh_done = true;
            last_state = cm_->getState();
        }
    }

}

void PanelTurnos::draw()
{
    ElementManager::draw();

}

void PanelTurnos::drawCurrentCharacter()
{
    // ICONO:

    addElement<SDL_Object>(icono, getCharacterTxt(character_), character_->getType() == rpgLogic::characterType::ENEMY);


    // VIDA y MANA:
    SDL_Rect number_aux = number;
    SDL_Rect number_info = number;
    SDL_Rect bar_aux = bar;

    CharacterSheet* character_sheet = character_->getCharacterSheet();
    number_info.y += number_info.h;

    // --> Health
    SDL_Color red{ 205, 0, 50, 255 };
    Line* line1 = addElement<Line>(number_info, "Health", src::Beaulieux, red);
    line1->addComponent<StateBar>(character_, BarType::health, number_aux, true);
    line1->addComponent<StateBar>(character_, BarType::health, bar_aux);

    number_aux.x += 2 * (pan.cw + 2 * pan.ew);
    number_info.x += 2 * (pan.cw + 2 * pan.ew);
    bar_aux.y += pan.ch * 2 / 5;

    // --> Mana
    SDL_Color blue{ 50,0,205,255 };
    Line* line2 = addElement<Line>(number_info, "Mana", src::Beaulieux, blue);
    line2->addComponent<StateBar>(character_, BarType::mana, number_aux, true);
    line2->addComponent<StateBar>(character_, BarType::mana, bar_aux);

}

void PanelTurnos::drawCurrentTurnList()
{
    SDL_Rect dest_icon = first;
    SDL_Rect dest_bar = first_bar;

    TheElementalMaze* tem_ = TheElementalMaze::instance();
    CombatManager* cm_ = tem_->getCombatManager();

    uint size = cm_->getCurrentTurnsList().size();

    offset = cm_->getTurn() == -1 ? 0 : cm_->getTurn();
    
    for (int i = 0; i < 3; i++)
    {
        uint k = offset + i;
        if (k >= size) { k = k - size; };

        SDL_Object* obj_ = addElement<SDL_Object>(dest_icon, getCharacterTxt(turnsList_[k]), turnsList_[k]->getType() == rpgLogic::characterType::ENEMY);
        obj_->addComponent<StateBar>(turnsList_[k], BarType::health, dest_bar);

        dest_icon.x -= (pan.cw + (2 * pan.ew));
        dest_bar.x -= (pan.cw + (2 * pan.ew));
    }

}

void PanelTurnos::drawCurrentInPanelHeroes()
{
    TheElementalMaze* tem_ = TheElementalMaze::instance();
    PartyManager* pm_ = tem_->getPartyManager();

    std::vector<Hero*> heroes = pm_->getHeroes();

    Hero* h_ = dynamic_cast<Hero*>(character_);
    if (h_ != nullptr) {
        rpgLogic::heroTemplate hero_template = h_->getTemplate();
        int n = -1;

        bool found = false;
        while (!found && n != 4) {
            n++;
            found = (hero_template == heroes[n]->getTemplate());            
        };

        if (found) {
            heroe_turn.y = offsetY + n * espaceH;
            addElement<SDL_Object>(heroe_turn, src::marco_hero);
        };
    }
}
