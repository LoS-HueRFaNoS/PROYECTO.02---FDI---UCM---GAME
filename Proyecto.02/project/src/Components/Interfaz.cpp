#include "Interfaz.h"
#include "../ecs/ecs.h"
#include "../Templates/callbacks.h"
#include "../Structures/messages.h"
#include "../GameObjects/Button.h"
#include "../GameObjects/Character.h"
#include "Image.h"
#include "Transform.h"
#include "StateBar.h"
#include "BorrarAlMorir.h"
#include "Laberinto.h"
#include "Tutorial.h"
#include "Rectangle.h"
#include "Paneles/PanelTurns.h"
#include "Paneles/PanelDnD.h"
#include "Paneles/PanelDesc.h"
#include "Paneles/ChatInfo.h"
#include "Paneles/ChestPanel.h"
#include "Paneles/PanelDescObj.h"
#include "Paneles/DadosP.h"
#include "../Utilities/SDL_macros.h"
#include "../Utilities/textures_box.h"
#include "../Managers/SDLGame.h"
#include "../Managers/TheElementalMaze.h"
#include "../Managers/game/PartyManager.h"
#include "../Managers/game/InterfazManager.h"
#include "../Managers/game/CombatManager.h"
#include "../Managers/game/ChatManager.h"
#include "../Managers/game/LobbyManager.h"
#include "../Managers/game/itemManager.h"
#include "../Components/PlayerMotion.h"
#include "../Components/MazePos.h"

using cb = callbacks;
using src = Resources;
using namespace textures_box;

Interfaz::~Interfaz()
{
    for (int i = 0; i < maxPanels; i++)
        delete allPanels[i];
    allPanels.clear();

    delete gameVolume;
    delete gameSound;
    gameVolume = gameSound = nullptr;
}

void Interfaz::createFight()
{
    CombatManager* c = GETCMP2(TheElementalMaze::instance(), CombatManager); // falta paso intermedio para guardar la habilidad y seleccionar enemigos

    // posicion en pixeles del 'fondo'
    double x_ = 70;
    double y_ = 790;
    // tamano en pixeles del 'fondo'
    double w_ = 540;
    double h_ = 190;
    // tamano de los margenes
    double n = 20;

    // posicion del panel respecto a la ventana
    x_ = game_->setHorizontalScale(x_ + n);
    y_ = game_->setVerticalScale(y_ + n);

    // espacios entre objetos
    double espace = game_->setHorizontalScale((w_ - n) / 4);

    // ancho y alto de cada objeto
    w_ = espace - game_->setHorizontalScale(n);
    h_ = game_->setVerticalScale(h_ - n * 2);

    // construccion y asignacion del panel:
    Panel* p = new Panel(Fight);
    allPanels[Fight] = p;

    if (c->getState() != END_TURN)
    {
        // BOTONES: normal, magic, defend, escape
        p->addButton(iManager->addButton<ButtonCombate>(Vector2D(x_ + 0, y_), w_, h_, src::AtaqueNormal, CmbtType::attack));
        p->addButton(iManager->addButton<ButtonCombate>(Vector2D(x_ + espace, y_), w_, h_, src::AtaqueMagico, CmbtType::magic));
        p->addButton(iManager->addButton<ButtonCombate>(Vector2D(x_ + espace * 2, y_), w_, h_, src::Huida, CmbtType::escape));
        p->addButton(iManager->addButton<ButtonCombate>(Vector2D(x_ + espace * 3, y_), w_, h_, src::Enter, CmbtType::defend));
    }
    else
    {
        double width_ = espace * 4 - game_->setHorizontalScale(n);
        p->addButton(iManager->addButton<ButtonCombate>(Vector2D(x_, y_), width_, h_, src::Enter, CmbtType::defend));
    }
}

void Interfaz::createEnemies() //:-)
{
    CombatManager* c = GETCMP2(TheElementalMaze::instance(), CombatManager);
    std::vector<Enemy*> enemies = c->getEnemiesTeam(); //:-)
    size_t nEnemies = c->getEnemysTam();

    // posicion en pixeles del 'fondo'
    double x_ = 70;
    double y_ = 70;
    // tamano en pixeles del 'fondo'
    double w_ = 1340;
    double h_ = 620;
    // tamano de los margenes
    double n = 0;

    // posicion del panel respecto a la ventana
    x_ = game_->setHorizontalScale(x_ + n);
    y_ = game_->setVerticalScale(y_ + n);

    // espacios entre objetos
    double tamBar_w = game_->setHorizontalScale((w_ - n) / 5);
    double tamBar_h = game_->setHorizontalScale((h_ - n) / 10 / 3);
    double espace = game_->setHorizontalScale((w_ - n) / nEnemies);

    // ancho y alto de cada objeto
    w_ = espace - game_->setHorizontalScale(n);
    h_ = game_->setVerticalScale(h_ - n * 2);

    // construccion y asignacion del panel:
    Panel* p = new Panel(Enemies);
    allPanels[Enemies] = p;

    for (int i = 0; i < nEnemies; i++) {
        Enemy* enemy = enemies[i];
        enemyTemplate enTemp = enemy->getTemplate();
        SDL_Object* b_;
        double lado;
        double margenBarra = w_ - tamBar_w;
        if (enTemp == enemyTemplate::DRACOLICH || enTemp == enemyTemplate::HELLHOUND || enTemp == enemyTemplate::GIANTWORM) {
            b_ = iManager->addButton<SDL_Object>(Vector2D(x_ + i * espace, y_), w_, h_, getEnemyTxt(i), true);
            ///p->addButton(iManager->addButton<ButtonTarget>(Vector2D(x_ + i * espace, y_), w_, h_, Resources::Joker, (target)i, &playerSelectingTarget));
        }
        else {
            if (nEnemies == 1) lado = h_;
            else {
                lado = w_;
                margenBarra = espace - tamBar_w;
            }

            b_ = iManager->addButton<SDL_Object>(Vector2D(x_ + i * espace + espace / 2.0 - lado / 2.0, y_ + h_ - lado), lado, lado, getEnemyTxt(i), true);
            ///p->addButton(iManager->addButton<ButtonTarget>(Vector2D(x_ + i * espace + espace / 2.0 - lado / 2.0, y_ + h_ - lado), lado, lado, Resources::Joker, (target)i, &playerSelectingTarget));
        }

        //BARRA DE VIDA
        b_->addComponent<StateBar>(enemy, BarType::health, SDL_Rect(RECT((x_ + i * espace + margenBarra / 2.0), (y_ + h_ / 10.0), tamBar_w, tamBar_h)));
        b_->addComponent<BorrarAlMorir>(this, i, enemy);
        b_->getComponent<Image>(ecs::Image)->setEnemy(enemy);
        //b_->addComponent<StateBar>(enemies[i], mana, SDL_Rect(RECT((x_ + i * espace), (y_ + h_ * 2.5 / k), w_ * 2, h_ / k)));
        p->addButton(b_);
    }
}

void Interfaz::createMovement()
{
    // posicion en pixeles del 'fondo'
    double x_ = 70;
    double y_ = 790;
    // tamano en pixeles del 'fondo'
    double w_ = 540;
    double h_ = 190;
    // tamano de los margenes
    double n = 20;

    // posicion del panel respecto a la ventana
    x_ = game_->setHorizontalScale(x_ + n);
    y_ = game_->setVerticalScale(y_ + n);

    /* || 20px - button - 20px - button - 20px - button - 20px - button - 20px - button - 20px || */
    double espace = game_->setHorizontalScale((w_ - n) / 3);

    w_ = espace - game_->setHorizontalScale(n);
    h_ = game_->setVerticalScale(h_ - n * 2);

    // construccion y asignacion del panel:
    Panel* p = new Panel(Movement);
    allPanels[Movement] = p;

    // BOTONES: rotR, rotL, forward, touch
    p->addButton(iManager->addButton<ButtonMovimiento>(Vector2D(x_ + 0, y_), w_, h_, src::RotarI, MovType::rotL));
    p->addButton(iManager->addButton<ButtonMovimiento>(Vector2D(x_ + espace, y_), w_, h_, src::Avanzar, MovType::forward));
    p->addButton(iManager->addButton<ButtonMovimiento>(Vector2D(x_ + espace * 2, y_), w_, h_, src::RotarD, MovType::rotR));
}

void Interfaz::createHeroes()
{
    PartyManager* c = TheElementalMaze::instance()->getPartyManager();
    std::vector<Hero*> heroes = c->getHeroes();
    size_t nHeros = heroes.size();

    // posicion en pixeles del 'fondo'
    double x_ = 1510;
    double y_ = 360;
    // tamano en pixeles del 'fondo'
    double w_ = 340;
    double h_ = 330;
    // tamano de los margenes
    double n = 5.0 + 5.0;
    
    // posicion del panel respecto a la ventana
    x_ = game_->setHorizontalScale(x_ + n);
    y_ = game_->setVerticalScale(y_ + n);

    double espace = game_->setVerticalScale((h_ - n) / nHeros);

    h_ = espace - game_->setVerticalScale(n);
    w_ = h_;

    // construccion del panel de heroes
    Panel* p = new Panel(Heroes);
    allPanels[Heroes] = p;

    // BOTONES: hero1, hero2, hero3, hero4
    for (int i = 0; i < nHeros; i++) {
        if (c->getHeroes()[i] != nullptr)
        {
            ButtonHero* b_ = iManager->addButton<ButtonHero>(Vector2D(x_, y_ + i * espace), w_, h_, getHeroTxt(i), (HeroNum)i, DDPan, false);
            uint k = 6;
            b_->addComponent<StateBar>(heroes[i], BarType::health, SDL_Rect(RECT((x_ + w_ + n), (y_ + i * espace + h_ * 1 / k), w_ * 2, h_ / k)));
            b_->addComponent<StateBar>(heroes[i], BarType::mana, SDL_Rect(RECT((x_ + w_ + n), (y_ + i * espace + h_ * 2.5 / k), w_ * 2, h_ / k)));
            b_->addComponent<StateBar>(heroes[i], BarType::experience, SDL_Rect(RECT((x_ + w_ + n), (y_ + i * espace + h_ * 4 / k), w_ * 2, h_ / k)));
            p->addButton(b_);
        }
    }
}

void Interfaz::createInfo()
{
    uint nInfoButton_H = 4; // separaciones horizontales
    uint nInfoButton_V = 2; // separaciones verticales

    // posicion en pixeles del 'fondo'
    double x_ = 1350; //880;
    double y_ = 790; //790;
    // tamano en pixeles del 'fondo'
    double w_ = 500;
    double h_ = 190;
    // tamano de los margenes
    double n = 5;

    // posicion del panel respecto a la ventana
    x_ = game_->setHorizontalScale(x_ + n);
    y_ = game_->setVerticalScale(y_ + n);

    double espace_H = game_->setHorizontalScale((w_ - n) / nInfoButton_H);
    double espace_V = game_->setVerticalScale((h_ - n) / nInfoButton_V);

    w_ = espace_H - game_->setHorizontalScale(n);
    h_ = espace_V - game_->setVerticalScale(n);

    // construccion del panel de informacion
    Panel* p = new Panel(Info);
    allPanels[Info] = p;

    // BOTONES: health, mana
    p->addButton(iManager->addButton<ButtonPanel>(Vector2D(x_, y_), w_ * 2, h_ * 2, src::Inventario, Inventory, false));
   

    ButtonPotion* bp1_ = iManager->addButton<ButtonPotion>(Vector2D(x_ + 2 * espace_H, y_ + 0 * espace_V), w_, h_, src::PocionVida, PtnType::health);
    bp1_->addComponent<Contador>(PtnType::health);
    p->addButton(bp1_);

    ButtonPotion* bp2_ = iManager->addButton<ButtonPotion>(Vector2D(x_ + 2 * espace_H, y_ + 1 * espace_V), w_, h_, src::PocionMana, PtnType::mana);
    bp2_->addComponent<Contador>(PtnType::mana);
    p->addButton(bp2_);

    p->addButton(iManager->addButton<ButtonSettings>(Vector2D(x_ + 3 * espace_H, y_ + 0 * espace_V), w_, h_, src::Change));
    p->addButton(iManager->addButton<ButtonPanel>(Vector2D(x_ + 3 * espace_H, y_ + 1 * espace_V), w_, h_, src::Configuracion, PausePanel, false, true));

} // 

void Interfaz::createInventory()
{
    SDLGame* game_ = entity_->getSDLGame();
    PartyManager* party = TheElementalMaze::instance()->getPartyManager();

    vector<Item*> items = party->getItems();
    double slotTam = game_->getWindowWidth() / 16;
    double posX;
    double posY = slotTam * 0.8;

    Panel* p = new Panel(Inventory);
    //allPanels.emplace(allPanels.begin() + Inventory, p);
    allPanels[Inventory] = p;

    // Cuadro de inventario 5x5
    int margen = 0.1 * slotTam;
    int itemTam = 0.8 * slotTam;
    Resources::TextureId id;
    uint pivot, auxId;
    for (int i = 0; i < 5; ++i) {

        posX = slotTam * 2.2; //Se resetea la coordenada X

        for (int j = 0; j < 5; ++j) {
            p->addButton(iManager->addButton<SDL_Object>(Vector2D(posX, posY), slotTam, slotTam, src::Slot));

            int indice = i * 5 + j;
            if (indice < items.size())
            {
                Item* item = items[indice];
                if (item != nullptr) {
                    ItemType itemType = item->getItemType();

                    if (itemType == ItemType::ARMOR) {
                        pivot = src::_firstArmorId_;
                        auxId = (int) static_cast<Armor*>(item)->getArmorId();
                        isItemToEquipAWeapon = false;
                    }
                    else {
                        pivot = src::_firstWeaponId_;
                        auxId = (int) static_cast<Weapon*>(item)->getWeaponId();
                        isItemToEquipAWeapon = true;
                    }
                    id = (Resources::TextureId) (pivot + auxId + 1);
                    p->addButton(iManager->addButton<ButtonItemManagement>(Vector2D(posX + margen, posY + margen), itemTam, itemTam, id, accionItem::showSendToStash, isItemToEquipAWeapon, indice, this));
                }
            }

            posX += slotTam;
        }
        posY += slotTam; // Se suma la coordenada Y

    }

    posX += slotTam * 0.3; // Se suma la coordenada X dejando un espacio.
    posY = slotTam * 0.8;


    // Inventario personajes: clase + arma + armadura
    PartyManager* c = TheElementalMaze::instance()->getPartyManager();
    std::vector<Hero*> heroes = c->getHeroes();
    for (int i = 0; i < 4; ++i) {
        if (!heroes[i])
            continue;
        p->addButton(iManager->addButton<SDL_Object>(Vector2D(posX, posY), slotTam, slotTam, getHeroTxt(i)));

        Weapon* weapon = heroes[i]->getWeapon();
        if (weapon != nullptr && weapon->getWeaponId() != wID::DESARMADO) {
            p->addButton(iManager->addButton<SDL_Object>(Vector2D(posX + slotTam, posY), slotTam, slotTam, src::Slot));
            pivot = src::_firstWeaponId_;
            auxId = (int)weapon->getWeaponId();
            id = (Resources::TextureId) (pivot + auxId + 1);
            p->addButton(iManager->addButton<ButtonHeroEquipment>(Vector2D(posX + slotTam + margen, posY + margen), itemTam, itemTam, id, accionHeroEquipment::showUnequip, true, -1, i, this));
        }
        else
            p->addButton(iManager->addButton<SDL_Object>(Vector2D(posX + slotTam, posY), slotTam, slotTam, src::WeaponSlot));

        Armor* armor = heroes[i]->getArmor();
        if (armor != nullptr) {
            p->addButton(iManager->addButton<SDL_Object>(Vector2D(posX + slotTam * 2, posY), slotTam, slotTam, src::Slot));
            pivot = src::_firstArmorId_;
            auxId = (int)armor->getArmorId();
            id = (Resources::TextureId) (pivot + auxId + 1);
            p->addButton(iManager->addButton<ButtonHeroEquipment>(Vector2D(posX + slotTam * 2 + margen, posY + margen), 0.8 * slotTam, 0.8 * slotTam, id, accionHeroEquipment::showUnequip, false, -1, i, this));
        }
        else
            p->addButton(iManager->addButton<SDL_Object>(Vector2D(posX + slotTam * 2, posY), slotTam, slotTam, src::ArmorSlot));



        posY += slotTam * 1.33;
    }

    //Llaves
    bool levelKey = party->getLevelKey();
    uint chestKeys = party->getChestKeys();
    slotTam = slotTam * 0.6;

        //Llaves de cofres
    posX = slotTam * 1.1; //Se resetea la coordenada X
    posY = slotTam / 0.6;

    SDL_Color color = { 255,255,255,255 };
    string text = "x" + to_string(chestKeys);
    SDL_Rect dest;
    dest.x = posX * 1.1 + slotTam;
    dest.y = posY;
    dest.h = slotTam;
    dest.w = slotTam;

    if (chestKeys > 0) p->addButton(iManager->addButton<SDL_Object>(Vector2D(posX, posY), slotTam, slotTam, src::LlaveCofre));
    else               p->addButton(iManager->addButton<SDL_Object>(Vector2D(posX, posY), slotTam, slotTam, src::LlaveVacia));

    p->addButton(iManager->addButton<Line>(dest, text, Resources::FontId::HERMAN, color));

        //Llaves de puerta
    posY += slotTam * 1.5;

    if (levelKey)   p->addButton(iManager->addButton<SDL_Object>(Vector2D(posX, posY), slotTam, slotTam, src::LlaveNivel));
    else            p->addButton(iManager->addButton<SDL_Object>(Vector2D(posX, posY), slotTam, slotTam, src::LlaveVacia));
    
}

void Interfaz::createChest()
{
    if (getActivePan(ActivateChest)) return;
    // posicion en pixeles del 'fondo'
    double x_ = 335;
    double y_ = 350;
    // tamano en pixeles del 'fondo'
    double w_ = 450;
    double h_ = 185;
    Panel* p = new Panel(ActivateChest);
    allPanels[ActivateChest] = p;
    togglePanel(ActivateChest);
    game_->setHorizontalScale(x_);
    game_->setHorizontalScale(w_);
    game_->setVerticalScale(y_);
    game_->setVerticalScale(h_);
    p->addButton(iManager->addButton<ButtonPanel>(Vector2D(x_, y_), w_, h_, src::Joker, _ChestPanel_, false));
}

void Interfaz::createFichaDD(uint nCharacter)
{
    PartyManager* c = TheElementalMaze::instance()->getPartyManager();
    std::vector<Hero*> heroes = c->getHeroes();

    SDL_Panel pan;
    pan = game_->relativePanel(1510, 70, 340, 190, 1, 1, 20, 20);
    SDL_Rect dest = RECT(
        pan.fcx,
        pan.fcy,
        pan.cw,
        pan.ch
    );

    // construccion y asignacion del panel:
    Panel* p = new Panel(DDPan);
    allPanels[DDPan] = p;

    if (TheElementalMaze::instance()->gameState() == GameState::DURING_LOBBY)
        p->addButton(iManager->addButton<ButtonHeroManagement>(dest, src::FireButton, accionHero::sendHeroToStash, nCharacter, this));

    TheElementalMaze::instance()->addComponent<PanelDnD>(game_, p, heroes[nCharacter], iManager);
}

void Interfaz::createFichaDesc(Hability* hab, bool aff) {
    Panel* p = new Panel(DescPan);
    allPanels[DescPan] = p;

    TheElementalMaze::instance()->addComponent<PanelDesc>(game_, p, iManager, hab, aff);
}

void Interfaz::createFichaDescObj(Item* ite) {
    Panel* p = new Panel(DescPanObj);
    allPanels[DescPanObj] = p;

    TheElementalMaze::instance()->addComponent<PanelDescObj>(game_, p, iManager, ite);
}

void Interfaz::createChat() {}

void Interfaz::createTargets() //:-)
{
    CombatManager* c = GETCMP2(TheElementalMaze::instance(), CombatManager);
    std::vector<Character*> targets = c->getCurrentTargetList(); //:-)
    size_t nTargets = targets.size();

    // construccion y asignacion del panel:
    Panel* p = new Panel(Targets);
    allPanels[Targets] = p;

    // posicion en pixeles del 'fondo'
    double x_ = 70;
    double y_ = 70;
    // tamano en pixeles del 'fondo'
    double w_ = 1340;
    double h_ = 620;
    // tamano de los margenes
    double n = 0;
    // posicion del panel respecto a la ventana
    x_ = game_->setHorizontalScale(x_ + n);
    y_ = game_->setVerticalScale(y_ + n);
    // espacios entre objetos
    double tamBar_w = game_->setHorizontalScale((w_ - n) / 5);
    double tamBar_h = game_->setHorizontalScale((h_ - n) / 10 / 3);
    double espace = game_->setHorizontalScale((w_ - n) / c->getEnemysTam());
    // ancho y alto de cada objeto
    w_ = espace - game_->setHorizontalScale(n);
    h_ = game_->setVerticalScale(h_ - n * 2);

    // NUEVOS BOTONES:
    for (int i = 0; i < c->getEnemysTam(); i++)
    {
        enemyTemplate enTemp = c->getEnemiesTeam()[i]->getTemplate();
        double lado;

        if (enTemp == enemyTemplate::DRACOLICH ||
            enTemp == enemyTemplate::HELLHOUND ||
            enTemp == enemyTemplate::GIANTWORM)
        {
            p->addButton(iManager->addButton<ButtonTarget>
                (Vector2D(x_ + i * espace, y_), w_, h_, Resources::Joker, (target)i, &playerSelectingTarget));
        }
        else
        {
            if (c->getEnemysTam() == 1) lado = h_;
            else lado = w_;

            p->addButton(iManager->addButton<ButtonTarget>
                (Vector2D(x_ + i * espace + espace / 2.0 - lado / 2.0, y_ + h_ - lado), lado, lado,
                    Resources::Joker, (target)i, &playerSelectingTarget));
        }
    }

    // posicion en pixeles del 'fondo'
    x_ = 70;
    y_ = 790;
    // tamano en pixeles del 'fondo'
    w_ = 540;
    h_ = 190;
    // tamano de los margenes
    n = 20;

    SDL_Rect dest = RECT(
        game_->setHorizontalScale(x_ + w_ - n * 2 + 30),
        game_->setVerticalScale(y_ - 30),
        game_->setHorizontalScale(n * 2),
        game_->setVerticalScale(n * 2)
    );

    // posicion del panel respecto a la ventana
    x_ = game_->setHorizontalScale(x_ + n);
    y_ = game_->setVerticalScale(y_ + n);

    espace = game_->setHorizontalScale((w_ - n) / 4);

    w_ = espace - game_->setHorizontalScale(n);
    h_ = game_->setVerticalScale(h_ - n * 2);

    // BOTONES:
    playerSelectingTarget = true;
    for (int i = 0; i < nTargets; i++) {
        src::TextureId img = size_t(targets[i]->getType()) ? getEnemyTxt(i) : getHeroTxt(i);
        p->addButton(iManager->addButton<ButtonTarget>(Vector2D(x_ + espace * i, y_), w_, h_, img, (target)i, &playerSelectingTarget));
    }

    idPanel idRegreso;
    if (c->isMagicAttack()) { idRegreso = Habilities; }
    else { idRegreso = WeaponsAttacks; };

    p->addButton(iManager->addButton<ButtonReturn>(dest, src::close, Targets, idRegreso, false));
}

void Interfaz::createHabilities()
{
    CombatManager* c = GETCMP2(TheElementalMaze::instance(), CombatManager);
    Hero* hero = static_cast<Hero*>(c->getCurrentCharacter());
    std::vector<Hability*> habilities = hero->getHabilities();
    size_t nHabilities = habilities.size();

    // posicion en pixeles del 'fondo'
    double x_ = 70;
    double y_ = 790;
    // tamano en pixeles del 'fondo'
    double w_ = 540;
    double h_ = 190;
    // tamano de los margenes
    double n = 20;

    SDL_Rect dest = RECT(
        game_->setHorizontalScale(x_ + w_ - n * 2 + 30),
        game_->setVerticalScale(y_ - 30),
        game_->setHorizontalScale(n * 2),
        game_->setVerticalScale(n * 2)
    );

    // posicion del panel respecto a la ventana
    x_ = game_->setHorizontalScale(x_ + n);
    y_ = game_->setVerticalScale(y_ + n);

    double espace = game_->setHorizontalScale((w_ - n) / nHabilities);

    w_ = espace - game_->setHorizontalScale(n);
    h_ = game_->setVerticalScale(h_ - n * 2);

    // construccion y asignacion del panel:
    Panel* p = new Panel(Habilities);
    allPanels[Habilities] = p;

    // BOTONES: //¡
    for (int i = 0; i < nHabilities; i++) {
        p->addButton(iManager->addButton<ButtonHability>(Vector2D(x_ + espace * i, y_), w_, h_, getHabilityTxt(hero, i), i));
    }

    p->addButton(iManager->addButton<ButtonReturn>(dest, src::close, Habilities, Fight, false));
}

void Interfaz::createWeaponAttacks()
{
    CombatManager* c = GETCMP2(TheElementalMaze::instance(), CombatManager);
    Hero* hero = static_cast<Hero*>(c->getCurrentCharacter());
    std::vector<Hability*> habilities = hero->getHabilities();
    size_t nAttack = 2;

    // posicion en pixeles del 'fondo'
    double x_ = 70;
    double y_ = 790;
    // tamano en pixeles del 'fondo'
    double w_ = 540;
    double h_ = 190;
    // tamano de los margenes
    double n = 20;

    SDL_Rect dest = RECT(
        game_->setHorizontalScale(x_ + w_ - n * 2 + 30),
        game_->setVerticalScale(y_ - 30),
        game_->setHorizontalScale(n * 2),
        game_->setVerticalScale(n * 2)
    );

    // posicion del panel respecto a la ventana
    x_ = game_->setHorizontalScale(x_ + n);
    y_ = game_->setVerticalScale(y_ + n);

    double espace = game_->setHorizontalScale((w_ - n) / nAttack);

    w_ = espace - game_->setHorizontalScale(n);
    h_ = game_->setVerticalScale(h_ - n * 2);

    // construccion y asignacion del panel:
    Panel* p = new Panel(WeaponsAttacks);
    allPanels[WeaponsAttacks] = p;

    p->addButton(iManager->addButton<ButtonWeaponAttack>(Vector2D(x_, y_), w_, h_, src::LightAttack, -2));
    p->addButton(iManager->addButton<ButtonWeaponAttack>(Vector2D(x_ + espace, y_), w_, h_, src::GolpeDuro, -3));

    p->addButton(iManager->addButton<ButtonReturn>(dest, src::close, WeaponsAttacks, Fight, false));
}

void Interfaz::createMenuPrincipal()
{
    Panel* p = new Panel(MenuPrincipal);
    allPanels[MenuPrincipal] = p;

    SDL_Panel pan;

    pan = game_->relativePanel(0, 1050 / 2, 1920, 1050);
    p->addButton(iManager->addButton<SDL_Object>(Vector2D(0, 0), pan.w, pan.h, src::mFondo));

    pan = game_->relativePanel(0, 1050 / 2, 1920, 1050 / 2, 7, 4, 20, 20, 0, 10);

    // START
    SDL_Rect dest = RECT(
        pan.fcx + pan.cw * 2 + pan.cw * 12 / 14,
        pan.fcy - pan.ch * 3 / 2,
        pan.cw + pan.cw * 4 / 14,
        pan.ch + pan.ch / 2
    );
    if (!TheElementalMaze::instance()->wasInMaze)
        p->addButton(iManager->addButton<ButtonMenu>(dest, src::start, accionMenu::lobby, this));
    else p->addButton(iManager->addButton<ButtonMenu>(dest, src::start, accionMenu::backToMaze, this));

    // resto de botones:
    dest = RECT(
        pan.fcx + pan.cw * 3,
        pan.fcy + pan.ch / 4,
        pan.cw,
        pan.ch
    );

    // OPTIONS
    dest.y = dest.y + pan.eh;
    p->addButton(iManager->addButton<ButtonMenu>(dest, src::options, accionMenu::options, this));

    // HOW TO PLAY
    dest.y = dest.y + pan.ch + pan.eh;
    //p->addButton(iManager->addButton<ButtonMenu>(dest, src::howToPlay, accionMenu::how_to_play, this));

    // QUIT
    dest.y = pan.lcy;
    p->addButton(iManager->addButton<ButtonMenu>(dest, src::quit, accionMenu::quit, this));
}

void Interfaz::createLobby() // botones principales
{
    Panel* p = new Panel(Lobby);
    allPanels[Lobby] = p;

    string text;
    string text2;
    SDL_Color color;

    createPanel(Heroes);

    // TITLE
    color = { 205,105,225,255 };
    text = "Bienvenido a la taberna";
    text2 = "¿Una copa?¿";

    SDL_Panel pan;
    pan = game_->relativePanel(70, 70, 1370, 650, 11, 6, 20, 20);
    SDL_Rect dest = RECT(
        pan.fcx + (pan.fcx + 20) * 3,
        pan.fcy,
        pan.cw * 3,
        pan.ch
    );

    p->addButton(iManager->addButton<SDL_Object>(Vector2D(40, 40), pan.w, pan.h, src::tabernaLobby));
    p->addButton(iManager->addButton<Line>(dest, text, Resources::FontId::Beaulieux, color));

    p->addButton(iManager->addButton<Line>(Vector2D(pan.fcx + (pan.fcx + 20) * 3, pan.fcy + 100), pan.cw * 3, pan.ch, text2, Resources::FontId::Beaulieux, color));
    p->addButton(iManager->addButton<SDL_Object>(Vector2D(650, 100), 250, pan.h - 55, src::bartender, true));

    //p->addButton(iManager->addButton<SDL_Object>(dest, src::mFondo));

    // BUY
    pan = game_->relativePanel(710, 790, 540, 190, 1, 1, 40, 40);
    dest = RECT(
        pan.fcx,
        pan.fcy,
        pan.cw,
        pan.ch
    );

    // Botón para ir a la tienda
    p->addButton(iManager->addButton<ButtonMenu>(dest, src::BuyButton, accionMenu::shop, this));

    // STASH / INVENTORY
    pan = game_->relativePanel(70, 790, 540, 190, 1, 2, 20, 20, 5, 5);
    dest = RECT(
        pan.fcx,
        pan.fcy,
        pan.cw,
        pan.ch
    );

    // Botón para ir al stash
    p->addButton(iManager->addButton<ButtonMenu>(dest, src::stash_button, accionMenu::stash, this));
    dest.y = dest.y + pan.ch + pan.eh;
    p->addButton(iManager->addButton<ButtonMenu>(dest, src::inventory_button, accionMenu::inventarioLobby, this));

    // PLAY
    pan = game_->relativePanel(1350, 790, 500, 190, 1, 1, 20, 20);
    dest = RECT(
        pan.fcx,
        pan.fcy,
        pan.cw,
        pan.ch
    );

    // Botón para empezar la partida
    p->addButton(iManager->addButton<ButtonMenu>(dest, src::start, accionMenu::start, this));

    p->addButton(iManager->addButton<ButtonMenu>(Vector2D(48, 48), 40, 40, src::close, accionMenu::backToMenu, this));


}

void Interfaz::createShop() // tienda con heroes y objetos
{
    Panel* p = new Panel(Shop);
    nameItemTienda = " ";
    descrItemTienda = " ";
    allPanels[Shop] = p;
    int w, h;
    SDL_Color color;
    string text;
    w = game_->getWindowWidth();
    h = game_->getWindowHeight();
    SDL_Panel pan;

    // Botón para retroceder al lobby
    pan = game_->relativePanel(1350, 790, 500, 190, 1, 1, 20, 20);
    SDL_Rect dest = RECT(
        pan.fcx,
        pan.fcy,
        pan.cw,
        pan.ch
    );
    p->addButton(iManager->addButton<ButtonMenu>(dest, src::lobby_button, accionMenu::shop_lobby, this));

    // TIENDA
    LobbyManager* loManager = TheElementalMaze::instance()->getLobbyManager();
    if (loManager->getLobbyStore() != nullptr)
    {
        pan = game_->relativePanel(70, 70, 1370, 650, 11, 5, 20, 20);
        dest = RECT(
            pan.fcx + (pan.fcx + 20) * 3,
            pan.fcy,
            pan.cw * 2,
            pan.ch
        );

        text = "Shop";
        color = { 155,155,155,255 };
        p->addButton(iManager->addButton<SDL_Object>(Vector2D(40, 40), pan.w, pan.h, src::tabernaShop));
        p->addButton(iManager->addButton<Line>(dest, text, Resources::FontId::HERMAN, color));

        dest.x = pan.lcx;
        dest.w = pan.cw;
        dest.h = pan.ch / 2;
        // Dinero del jugador
        text = to_string(loManager->getPlayerStash()->gold);
        color = { 155,155,255,255 };
        p->addButton(iManager->addButton<Line>(dest, text, Resources::FontId::HERMAN, color));

        dest = RECT(
            dest.x = pan.fcx,
            dest.y = pan.fcy + pan.ch,
            dest.w = pan.cw,
            dest.h = pan.ch
        );

        //dest.h = pan.ch;
        //dest.w = pan.cw * 10;
        //// Slots de la tienda
        //p->addButton(iManager->addButton<SDL_Object>(dest, src::inventory_slots));
        //dest.y = pan.fcy + pan.ch * 4;
        //p->addButton(iManager->addButton<SDL_Object>(dest, src::inventory_slots));

        // Se generan 10 héroes a la venta
        for (int i = 0; i < 10; i++)
        {
            HeroContract* her = loManager->getLobbyStore()->heroes[i];
            int tex = src::_firstHeroRId_ + (int)her->hero->getTemplate() + 1;

            // Dibujo del héroe
            p->addButton(iManager->addButton<SDL_Object>(dest, src::Slot));
            dest.x = dest.x + 10;
            dest.y = dest.y + 10;
            dest.w = pan.cw - 20;
            dest.h = pan.ch - 20;
            p->addButton(iManager->addButton<ButtonInfoTienda>(dest, static_cast<Resources::TextureId>(tex), true, i, this));

            // Si se han vendido se marcan como tal, si no se escribe su precio
            if (her->sold) text = "sold";
            else text = "x" + to_string(her->price);

            dest.y = pan.fcy + pan.ch * 2 + pan.ch / 6;
            dest.h = pan.ch / 4;
            p->addButton(iManager->addButton<Line>(dest, text, Resources::FontId::HERMAN, color));

            // Botón de comprar
            dest.y = pan.fcy + pan.ch * 2 + pan.ch * 2 / 4;
            dest.h = pan.ch / 2;
            p->addButton(iManager->addButton<ButtonBuyHero>(dest, src::BuyButton, i, this));

            dest.x = dest.x + pan.cw;
            dest.y = pan.fcy + pan.ch;
            dest.w = pan.cw;
            dest.h = pan.ch;
        }

        dest = RECT(
            dest.x = pan.fcx,
            dest.y = pan.fcy + pan.ch * 4,
            dest.w = pan.cw,
            dest.h = pan.ch
        );

        int tam = loManager->getLobbyStore()->items.size();
        // Se generan 10 objetos a la venta
        int tex;
        for (int i = 0; i < 10 && i < tam; i++)
        {
            ItemToBuy* it = loManager->getLobbyStore()->items[i];
            if ((int)it->item->getItemType() == 0)
            {
                Weapon* arma = static_cast<Weapon*>(it->item);
                tex = (int)src::_firstWeaponId_ + (int)arma->getWeaponId() + 1;
            }
            else
            {
                Armor* armadura = static_cast<Armor*>(it->item);
                tex = (int)src::_firstArmorId_ + (int)armadura->getArmorId() + 1;
            }

            // Dibujo del objeto
            p->addButton(iManager->addButton<SDL_Object>(dest, src::Slot));
            dest.x = dest.x + 10;
            dest.y = dest.y + 10;
            dest.w = pan.cw - 20;
            dest.h = pan.ch - 20;
            p->addButton(iManager->addButton<ButtonInfoTienda>(dest, static_cast<Resources::TextureId>(tex), false, i, this));

            // Si se han vendido se marcan como tal, si no se escribe su precio
            if (it->sold) text = "sold";
            else text = "x" + to_string(it->item->getBuyValue());

            dest.y = pan.fcy + pan.ch * 5 + pan.ch / 6;
            dest.h = pan.ch / 4;
            p->addButton(iManager->addButton<Line>(dest, text, Resources::FontId::HERMAN, color));

            // Botón de comprar
            dest.y = pan.fcy + pan.ch * 5 + pan.ch * 2 / 4;
            dest.h = pan.ch / 2;
            p->addButton(iManager->addButton<ButtonBuyItem>(dest, src::BuyButton, i, 1, this));

            dest.x = dest.x + pan.cw;
            dest.y = pan.fcy + pan.ch * 4;
            dest.w = pan.cw;
            dest.h = pan.ch;
        }
    }
}


void Interfaz::createStash() // stash de objetos y heroes en tienda
{
    LobbyManager* loManager = TheElementalMaze::instance()->getLobbyManager();

    SDL_Panel pan;

    Panel* p = new Panel(StashPanel);
    allPanels[StashPanel] = p;

    EntityManager* mngr_ = TheElementalMaze::instance()->getEntityMangr();

    pan = game_->relativePanel(1350, 790, 500, 190, 1, 1, 20, 20);
    SDL_Rect dest = RECT(
        pan.fcx,
        pan.fcy,
        pan.cw,
        pan.ch
    );

    // Botón para volver al lobby (LOBBY)
    p->addButton(iManager->addButton<ButtonMenu>(dest, src::lobby_button, accionMenu::stash_lobby, this));

    pan = game_->relativePanel(70, 70, 1370, 650, 11, 5, 20, 20);
    dest = RECT(
        pan.fcx,
        pan.fcy,
        pan.cw * 10,
        pan.ch
    );
    p->addButton(iManager->addButton<SDL_Object>(Vector2D(40, 40), pan.w, pan.h, src::tabernaStash));
    // Slots del stash de héroes: filas de slots conjuntas
    p->addButton(iManager->addButton<SDL_Object>(dest, src::inventory_slots));
    dest.y = dest.y + dest.h;
    p->addButton(iManager->addButton<SDL_Object>(dest, src::inventory_slots));

    dest.y = dest.y + dest.h * 2;
    // Slots del stash de objetos: filas de slots conjuntas
    p->addButton(iManager->addButton<SDL_Object>(dest, src::inventory_slots));
    dest.y = dest.y + dest.h;
    p->addButton(iManager->addButton<SDL_Object>(dest, src::inventory_slots));

    // Botones subir y bajar paginas de stash de cada grupo
    dest = RECT(
        dest.x = pan.lcx,
        dest.y = pan.fcy,
        dest.w = pan.cw,
        dest.h = pan.ch
    );
    if (pagHeroes == 0)
        p->addButton(iManager->addButton<ButtonMenu>(dest, src::AvanzarBloqueado, accionMenu::retrocederHeroes, this));
    else p->addButton(iManager->addButton<ButtonMenu>(dest, src::Avanzar, accionMenu::retrocederHeroes, this));

    dest.y = dest.y + dest.h;
    if (loManager->getPlayerStash()->heroes.size() > 20 * (pagHeroes + 1))
        p->addButton(iManager->addButton<ButtonMenu>(dest, src::Retroceder, accionMenu::avanzarHeroes, this));
    else p->addButton(iManager->addButton<ButtonMenu>(dest, src::RetrocederBloqueado, accionMenu::avanzarHeroes, this));

    dest.y = dest.y + dest.h * 2;
    if (pagItems == 0)
        p->addButton(iManager->addButton<ButtonMenu>(dest, src::AvanzarBloqueado, accionMenu::retrocederItems, this));
    else p->addButton(iManager->addButton<ButtonMenu>(dest, src::Avanzar, accionMenu::retrocederItems, this));

    dest.y = dest.y + dest.h;
    if (loManager->getPlayerStash()->items.size() > 20 * (pagItems + 1))
        p->addButton(iManager->addButton<ButtonMenu>(dest, src::Retroceder, accionMenu::avanzarItems, this));
    else p->addButton(iManager->addButton<ButtonMenu>(dest, src::RetrocederBloqueado, accionMenu::avanzarItems, this));

    dest = RECT(
        dest.x = pan.fcx + 10,
        dest.y = pan.fcy + 10,
        dest.w = pan.cw - 20,
        dest.h = pan.ch - 20
    );

    int tam = loManager->getPlayerStash()->heroes.size();
    // Por cada fila de slots de héroes
    for (int i = 0; i < 2; i++)
    {
        // Por cada héroe de la fila
        for (int j = 0; j < 10 && pagHeroes * 20 + i * 10 + j < tam; j++)
        {
            Hero* her = loManager->getPlayerStash()->heroes[20 * pagHeroes + i * 10 + j];
            auto tex = src::_firstHeroRId_ + (int)her->getTemplate() + 1;
            p->addButton(iManager->addButton<ButtonShowHeroToParty>(dest, static_cast<Resources::TextureId>(tex), 20 * pagHeroes + i * 10 + j, this));
            dest.x = dest.x + dest.w + 20;
        }
        dest.y = dest.y + dest.h + 20;
    }
    ItemManager* itemMngr_ = TheElementalMaze::instance()->getItemManager();
    int Itemtam = loManager->getPlayerStash()->items.size();

    dest = RECT(
        dest.x = pan.fcx + 10,
        dest.y = pan.fcy + pan.ch * 3 + 10,
        dest.w = pan.cw - 20,
        dest.h = pan.ch - 20
    );
    // Por cada fila de slots de objetos
    int tex;
    int a;
    for (int i = 0; i < 2; i++)
    {
        // Por cada objeto de la fila
        for (int j = 0; j < 10 && pagItems * 20 + i * 10 + j < Itemtam; j++)
        {
            Item* objeto = loManager->getPlayerStash()->items[pagItems * 20 + i * 10 + j];
            if ((int)objeto->getItemType() == 0)
            {
                Weapon* arma = static_cast<Weapon*>(loManager->getPlayerStash()->items[pagItems * 20 + i * 10 + j]);
                tex = (int)src::_firstWeaponId_ + (int)arma->getWeaponId() + 1;
            }
            else
            {
                Armor* armadura = static_cast<Armor*>(loManager->getPlayerStash()->items[pagItems * 20 + i * 10 + j]);
                tex = (int)src::_firstArmorId_ + (int)armadura->getArmorId() + 1;
            }
            p->addButton(iManager->addButton<ButtonItemManagement>(dest, static_cast<Resources::TextureId>(tex), accionItem::showSellButton, isWeapon, j, this));
            dest.x = dest.x + dest.w + 20;
        }
        dest.y = dest.y + dest.h + 20;
    }

}

void Interfaz::createOptions() // <3
{
    Panel* p = new Panel(Options);
    allPanels[Options] = p;

    uint w = game_->getWindowWidth();
    uint h = game_->getWindowHeight();

    int centerXOffset = -200;
    int columnX = w / 2 + centerXOffset;
    int controlsSize = 50;
    int titleW = 400;
    int titleH = 100;
    int subtitleW = 200;
    int subtitleH = 50;

    // Argumentos
    SDL_Rect dest;
    string text;
    SDL_Color color = { 255,255,255,255 };

    // Objetos cambiantes
    SDL_Object* objVolume;
    SDL_Object* objSound;

    // Fondo
    dest.x = 0;
    dest.y = 0;
    dest.w = w;
    dest.h = h;
    p->addButton(iManager->addButton<SDL_Object>(dest, src::Cartel));
    // Titulo
    dest.x = columnX;
    dest.y = 50; // + 50
    dest.w = titleW;
    dest.h = titleH;
    text = "Options";
    p->addButton(iManager->addButton<Line>(dest, text, Resources::FontId::Beaulieux, color));
    // Volumen
    dest.y = 250; // + 200
    dest.w = subtitleW;
    dest.h = subtitleH;
    text = "Volume";
    p->addButton(iManager->addButton<Line>(dest, text, Resources::FontId::Beaulieux, color));
    // contenedor volumen
    dest.y = 330; // +80
    dest.w = VOLUME_BAR_MAX;
    dest.h = VOLUME_BAR_HEIGHT;
    p->addButton(iManager->addButton<SDL_Object>(dest, Resources::TextureId::VolumeBarBackground));
    // deslizador volumen
    dest.w = (*gameVolume / (float)(VOLUME_MAX - VOLUME_MIN)) * VOLUME_BAR_MAX;;
    objVolume = iManager->addButton<SDL_Object>(dest, Resources::TextureId::VolumeBar);
    p->addButton(objVolume);
    // audio volumen -10
    dest.x = columnX - 2 * controlsSize;
    dest.w = controlsSize;
    dest.h = controlsSize;
    p->addButton(iManager->addButton<ButtonVolumen>(dest, Resources::TextureId::RotarI, objVolume,
        gameVolume, gameSound, VOLUME_MIN, VOLUME_MAX, -10, VOLUME_BAR_MAX, true));
    // audio volumen -1
    dest.x = columnX - controlsSize;
    p->addButton(iManager->addButton<ButtonVolumen>(dest, Resources::TextureId::RotarIAlt, objVolume,
        gameVolume, gameSound, VOLUME_MIN, VOLUME_MAX, -1, VOLUME_BAR_MAX, true));
    // audio volumen +1
    dest.x = columnX + VOLUME_BAR_MAX;
    p->addButton(iManager->addButton<ButtonVolumen>(dest, Resources::TextureId::RotarDAlt, objVolume,
        gameVolume, gameSound, VOLUME_MIN, VOLUME_MAX, 1, VOLUME_BAR_MAX, true));
    // audio volumen +10
    dest.x = columnX + VOLUME_BAR_MAX + controlsSize;
    p->addButton(iManager->addButton<ButtonVolumen>(dest, Resources::TextureId::RotarD, objVolume,
        gameVolume, gameSound, VOLUME_MIN, VOLUME_MAX, 10, VOLUME_BAR_MAX, true));
    // Sonido
    dest.x = columnX;
    dest.y = 450; // +120
    dest.w = subtitleW;
    dest.h = subtitleH;
    text = "Sound";
    p->addButton(iManager->addButton<Line>(dest, text, Resources::FontId::Beaulieux, color));
    // contenedor sonido
    dest.y = 530; // +80
    dest.w = VOLUME_BAR_MAX;
    dest.h = VOLUME_BAR_HEIGHT;
    p->addButton(iManager->addButton<SDL_Object>(dest, Resources::TextureId::VolumeBarBackground));
    // deslizador sonido
    dest.w = (*gameSound / (float)(VOLUME_MAX - VOLUME_MIN)) * VOLUME_BAR_MAX;;
    objSound = iManager->addButton<SDL_Object>(dest, Resources::TextureId::VolumeBar);
    p->addButton(objSound);
    // audio sonido -10
    dest.x = columnX - 2 * controlsSize;
    dest.w = controlsSize;
    dest.h = controlsSize;
    p->addButton(iManager->addButton<ButtonVolumen>(dest, Resources::TextureId::RotarI, objSound,
        gameVolume, gameSound, VOLUME_MIN, VOLUME_MAX, -10, VOLUME_BAR_MAX, false));
    // audio sonido -1
    dest.x = columnX - controlsSize;
    p->addButton(iManager->addButton<ButtonVolumen>(dest, Resources::TextureId::RotarIAlt, objSound,
        gameVolume, gameSound, VOLUME_MIN, VOLUME_MAX, -1, VOLUME_BAR_MAX, false));
    // audio sonido +1
    dest.x = columnX + VOLUME_BAR_MAX;
    p->addButton(iManager->addButton<ButtonVolumen>(dest, Resources::TextureId::RotarDAlt, objSound,
        gameVolume, gameSound, VOLUME_MIN, VOLUME_MAX, 1, VOLUME_BAR_MAX, false));
    // audio sonido +10
    dest.x = columnX + VOLUME_BAR_MAX + controlsSize;
    p->addButton(iManager->addButton<ButtonVolumen>(dest, Resources::TextureId::RotarD, objSound,
        gameVolume, gameSound, VOLUME_MIN, VOLUME_MAX, 10, VOLUME_BAR_MAX, false));
    // Volver
    p->addButton(iManager->addButton<ButtonMenu>(Vector2D(70, 70), 80, 80, src::close, accionMenu::options, this));
}

void Interfaz::createGuide()
{
    Panel* p = new Panel(HowToPlay);
    allPanels[HowToPlay] = p;
    int w, h;
    int x, y;
    int ancho;
    string text;
    SDL_Color color;

    w = game_->getWindowWidth();
    h = game_->getWindowHeight();
    p->addButton(iManager->addButton<SDL_Object>(Vector2D(0, 0), w, h, src::mFondo));

    p->addButton(iManager->addButton<SDL_Object>(Vector2D(100, 100), w - 200, h - 200, src::Pergamino));

    x = w / 2 - 200; y = 250;
    color = { 0,0,0,255 };
    text = "How To Play";
    p->addButton(iManager->addButton<Line>(Vector2D(x, y), 400, 100, text, Resources::FontId::HERMAN, color));

    color = { 100,50,0,255 };
    x = 250; y = 370;
    text = "Click on the virtual buttons to play the game";
    ancho = int(text.size()) * 15 - 100;
    p->addButton(iManager->addButton<Line>(Vector2D(x, y), ancho, 30, text, Resources::Fornite64, color));

    color = { 150,150,0,255 };
    y += 50;
    text = "Special Keyboards";
    ancho = int(text.size()) * 20;
    p->addButton(iManager->addButton<Line>(Vector2D(x + 150, y), ancho, 40, text, Resources::Fornite64, color));

    color = { 100,50,0,255 };
    y += 50;
    text = "Press left-right arrows or A-D keys to rotate the view";
    ancho = int(text.size()) * 15 - 100;
    p->addButton(iManager->addButton<Line>(Vector2D(x, y), ancho, 30, text, Resources::Fornite64, color));

    y += 30;
    text = "Press up arrows or W keys to advance";
    ancho = int(text.size()) * 15 - 30;
    p->addButton(iManager->addButton<Line>(Vector2D(x, y), ancho, 30, text, Resources::Fornite64, color));

    y += 30;
    text = "Press spacebar or E keys to interact";
    ancho = int(text.size()) * 15 - 50;
    p->addButton(iManager->addButton<Line>(Vector2D(x, y), ancho, 30, text, Resources::Fornite64, color));

    p->addButton(iManager->addButton<ButtonMenu>(Vector2D(w - 225, 120), 64, 64, src::close, accionMenu::how_to_play, this));

}

void Interfaz::createTurns()
{
    TheElementalMaze::instance()->addComponent<PanelTurns>(game_);
}

void Interfaz::createInventoryLobby()
{
    SDLGame* game_ = entity_->getSDLGame();
    vector<Item*> items = TheElementalMaze::instance()->getPartyManager()->getItems();
    double slotTam = game_->getWindowWidth() / 16;
    double posX;
    double posY = slotTam * 0.8;
    int w, h, tam;
    w = game_->getWindowWidth();
    h = game_->getWindowHeight();
    Panel* p = new Panel(InventoryLobby);
    allPanels[InventoryLobby] = p;

    SDL_Panel pan;
    pan = game_->relativePanel(1350, 790, 500, 190, 1, 1, 20, 20);
    SDL_Rect dest = RECT(
        pan.fcx,
        pan.fcy,
        pan.cw,
        pan.ch
    );

    // Botón para volver al lobby
    p->addButton(iManager->addButton<ButtonMenu>(dest, src::lobby_button, accionMenu::inventario_to_lobby, this));

    // Cuadro de inventario 5x5
    int margen = 0.1 * slotTam;
    int itemTam = 0.8 * slotTam;
    Resources::TextureId id;
    uint pivot, auxId;
    for (int i = 0; i < 5; ++i) {

        posX = slotTam * 1.5; //Se resetea la coordenada X

        for (int j = 0; j < 5; ++j) {
            p->addButton(iManager->addButton<SDL_Object>(Vector2D(posX, posY), slotTam, slotTam, src::Slot));

            int indice = i * 5 + j;
            if (indice < items.size())
            {
                Item* item = items[indice];
                if (item != nullptr) {
                    ItemType itemType = item->getItemType();

                    if (itemType == ItemType::ARMOR) {
                        pivot = src::_firstArmorId_;
                        auxId = (int) static_cast<Armor*>(item)->getArmorId();
                        isItemToEquipAWeapon = false;
                    }
                    else {
                        pivot = src::_firstWeaponId_;
                        auxId = (int) static_cast<Weapon*>(item)->getWeaponId();
                        isItemToEquipAWeapon = true;
                    }
                    id = (Resources::TextureId) (pivot + auxId + 1);
                    p->addButton(iManager->addButton<ButtonItemManagement>(Vector2D(posX + margen, posY + margen), itemTam, itemTam, id, accionItem::showSendToStash, isItemToEquipAWeapon, indice, this));
                }
            }

            posX += slotTam;
        }
        posY += slotTam; // Se suma la coordenada Y

    }

    posX += slotTam; // Se suma la coordenada X dejando un espacio.
    posY = slotTam * 0.8;


    // Inventario personajes: clase + arma + armadura
    PartyManager* c = TheElementalMaze::instance()->getPartyManager();
    std::vector<Hero*> heroes = c->getHeroes();
    for (int i = 0; i < 4; ++i) {
        if (c->getHeroes()[i] != nullptr)
        {
            p->addButton(iManager->addButton<SDL_Object>(Vector2D(posX, posY), slotTam, slotTam, getHeroTxt(i)));

            Weapon* weapon = heroes[i]->getWeapon();
            if (weapon != nullptr && weapon->getWeaponId() != wID::DESARMADO) {
                p->addButton(iManager->addButton<SDL_Object>(Vector2D(posX + slotTam, posY), slotTam, slotTam, src::Slot));
                pivot = src::_firstWeaponId_;
                auxId = (int)weapon->getWeaponId();
                id = (Resources::TextureId) (pivot + auxId + 1);
                p->addButton(iManager->addButton<ButtonHeroEquipment>(Vector2D(posX + slotTam + margen, posY + margen), itemTam, itemTam, id, accionHeroEquipment::showUnequip, true, -1, i, this));
            }
            else
                p->addButton(iManager->addButton<SDL_Object>(Vector2D(posX + slotTam, posY), slotTam, slotTam, src::WeaponSlot));

            Armor* armor = heroes[i]->getArmor();
            if (armor != nullptr) {
                p->addButton(iManager->addButton<SDL_Object>(Vector2D(posX + slotTam * 2, posY), slotTam, slotTam, src::Slot));
                pivot = src::_firstArmorId_;
                auxId = (int)armor->getArmorId();
                id = (Resources::TextureId) (pivot + auxId + 1);
                p->addButton(iManager->addButton<ButtonHeroEquipment>(Vector2D(posX + slotTam * 2 + margen, posY + margen), 0.8 * slotTam, 0.8 * slotTam, id, accionHeroEquipment::showUnequip, false, -1, i, this));
            }
            else
                p->addButton(iManager->addButton<SDL_Object>(Vector2D(posX + slotTam * 2, posY), slotTam, slotTam, src::ArmorSlot));
        }


        posY += slotTam * 1.33;
    }
}

void Interfaz::createUnequipPanel()
{
    int w, h, tam;
    w = game_->getWindowWidth();
    h = game_->getWindowHeight();
    Panel* p = new Panel(UnequipPanel);
    allPanels[UnequipPanel] = p;
    if (getActivePan(EquipPanel)) removePanel(EquipPanel);
    p->addButton(iManager->addButton<ButtonHeroEquipment>(Vector2D(w / 2 - 150, 2 * h / 3 + 100), 300, 100, src::StoreItemButton, accionHeroEquipment::Unequip, isWeapon, -1, selectedInventoryHero, this));
}

void Interfaz::createDados()
{
    Panel* p = new Panel(DadosPan);
    allPanels[DadosPan] = p;

    std::vector<Hero*> heroes = TheElementalMaze::instance()->getPartyManager()->getHeroes();

    /*TheElementalMaze::instance()->addComponent<DadosP>
        (game_, p, iManager, Vector2D(1500, 390), Vector2D(0, 80), &heroes);*/

    double x_ = game_->setHorizontalScale(1755);
    double y_ = game_->setVerticalScale(370);
    double space_ = game_->setVerticalScale(80);
    TheElementalMaze::instance()->addComponent<DadosP>
        (game_, p, iManager, Vector2D(x_, y_), Vector2D(0, space_), heroes);
}

void Interfaz::toggleMinimap()
{
    TheElementalMaze::instance()->getLaberinto()->toggleMiniMap();
}

void Interfaz::checkAndDeletePanel(idPanel id)
{
    delete allPanels[id];
    allPanels[id] = nullptr;
}

void Interfaz::createHeroToPartyPanel()
{
    int w, h;
    w = game_->getWindowWidth();
    h = game_->getWindowHeight();
    Panel* p = new Panel(ButtonHeroToPartyPanel);
    allPanels[ButtonHeroToPartyPanel] = p;
    p->addButton(iManager->addButton<ButtonHeroManagement>(Vector2D(w / 2 + w / 3 - 65, 75), 250, 100, src::RecruitButton, accionHero::sendHeroToParty, selectedHeroToParty, this));
}

void Interfaz::createSendToStashPanel()
{
    int w, h;
    w = game_->getWindowWidth();
    h = game_->getWindowHeight();
    Panel* p = new Panel(sendToStashPanel);
    allPanels[sendToStashPanel] = p;
    p->addButton(iManager->addButton<ButtonItemManagement>(Vector2D(w / 2 + w / 3 - 65, 75), 250, 100, src::StoreItemButton, accionItem::sendToStash, isWeapon, selectedInventoryItem, this));
    //p->addButton(iManager->addButton<ButtonItemManagement>(Vector2D(w / 2 - w / 3 - 150, 2 * h / 3 + 100), 300, 100, src::EquipButton, accionItem::showEquipButton,isItemToEquipAWeapon, selectedInventoryItem, this));
}


void Interfaz::createSellButtonPanel()
{
    int w, h;
    w = game_->getWindowWidth();
    h = game_->getWindowHeight();
    Panel* p = new Panel(SellButtonPanel);
    allPanels[SellButtonPanel] = p;
    p->addButton(iManager->addButton<ButtonItemManagement>(Vector2D(w / 2 - w / 3 - 150, 2 * h / 3 + 100), 300, 100, src::SellButton, accionItem::sellItem, isWeapon, selectedItem, this));
    p->addButton(iManager->addButton<ButtonItemManagement>(Vector2D(w / 2 - 150, 2 * h / 3 + 100), 300, 100, src::take, accionItem::sendToInventory, isWeapon, selectedItem, this));
}

void Interfaz::createEquipPanel()
{
    PartyManager* pa = TheElementalMaze::instance()->getPartyManager();
    LobbyManager* lo = TheElementalMaze::instance()->getLobbyManager();
    double slotTam = game_->getWindowWidth() / 16;
    double posX = slotTam * 1.5;
    double posY = slotTam * 0.8;
    int w, h, tam;
    int margen = 0.1 * slotTam;
    int itemTam = 0.8 * slotTam;
    Panel* p = new Panel(EquipPanel);
    allPanels[EquipPanel] = p;
    if (getActivePan(UnequipPanel)) removePanel(UnequipPanel);
    if (isItemToEquipAWeapon)
    {
        posX += slotTam * 6;

        for (int i = 0; i < pa->getHeroes().size(); ++i)
        {
            if (pa->getHeroes()[i] != nullptr && pa->getHeroes()[i]->getWeapon()->getWeaponId() == wID::DESARMADO)
            {
                //p->addButton(iManager->addButton<ButtonHeroEquipment>(Vector2D(0, posY + margen), itemTam, itemTam, src::EquipButton, accionHeroEquipment::Equip, true,selectedInventoryItem, i, this));
                p->addButton(iManager->addButton<ButtonHeroEquipment>(Vector2D(posX + slotTam + margen, posY + margen), itemTam, itemTam, src::EquipButton, accionHeroEquipment::Equip, true, selectedInventoryItem, i, this));
            }
            posY += slotTam * 1.33;
        }
    }
    else
    {
        posX += slotTam * 7;

        for (int i = 0; i < pa->getHeroes().size(); ++i)
        {
            if (pa->getHeroes()[i] != nullptr && pa->getHeroes()[i]->getArmor() == nullptr)
            {
                p->addButton(iManager->addButton<ButtonHeroEquipment>(Vector2D(posX + slotTam + margen, posY + margen), itemTam, itemTam, src::EquipButton, accionHeroEquipment::Equip, false, selectedInventoryItem, i, this));
            }
            posY += slotTam * 1.33;
        }
    }
}
void Interfaz::createPausePanel()
{
    if (TheElementalMaze::instance()->gameState() == GameState::COMBAT)
        return;
    iManager->setPause();
    Panel* p = new Panel(PausePanel);
    allPanels[PausePanel] = p;
    //iManager->setPause();
    SDL_Rect a = RECT(0, 0, game_->getWindowWidth(), game_->getWindowHeight(), 0);
    p->addButton(iManager->addButton<SDL_Object>(a, src::cinematica));
    SDL_Panel pan;
    pan = game_->relativePanel(0, 1050 / 2, 1920, 1050 / 2, 7, 4, 20, 20, 0, 10);

    // START
    SDL_Rect dest = RECT(
        pan.fcx + pan.cw * 2 + pan.cw * 12 / 14,
        pan.fcy - pan.ch * 3 / 2,
        pan.cw + pan.cw * 4 / 14,
        pan.ch + pan.ch / 2
    );
    p->addButton(iManager->addButton<ButtonMenu>(dest, src::start, accionMenu::resume, this));

    // resto de botones:
    dest = RECT(
        pan.fcx + pan.cw * 3,
        pan.fcy + pan.ch / 4,
        pan.cw,
        pan.ch
    );

    // OPTIONS
    dest.y = dest.y + pan.eh;
    p->addButton(iManager->addButton<ButtonMenu>(dest, src::options, accionMenu::options, this));

    // HOW TO PLAY
    dest.y = dest.y + pan.ch + pan.eh;
    //p->addButton(iManager->addButton<ButtonMenu>(dest, src::howToPlay, accionMenu::how_to_play, this));

    // QUIT
    dest.y = pan.lcy;
    p->addButton(iManager->addButton<ButtonMenu>(dest, src::quit, accionMenu::backToMenu, this));
    TheElementalMaze::instance()->changeState(gameST::DURING_PAUSE);
}

void Interfaz::createPanel(idPanel panelID)
{
    checkAndDeletePanel(panelID);
    switch (panelID) {
    case Fight:
        createFight();
        break;
    case Movement:
        createMovement();
        break;
    case Minimap:
        TheElementalMaze::instance()->getLaberinto()->toggleMiniMap();
        break;
    case Heroes:
        createHeroes();
        break;
    case Info:
        createInfo();
        break;
    case Inventory:
        createInventory();
        break;
    case HeroesStats:
        //createFichaDnD();
        break;
    case BigMap:
        createBigMap();
        break;
    case Turns:
        createTurns();
        break;
    case Settings:
        createSettings();
        break;
    case Chat:
        TheElementalMaze::instance()->addComponent<ChatInfo>();
        break;
    case ActivateChest:
        createChest();
        break;
    case _ChestPanel_:
        if (TheElementalMaze::instance()->getLaberinto()->getCasillaInfo(GETCMP2(TheElementalMaze::instance()->getPlayer(), MazePos)->getPos().getX(), GETCMP2(TheElementalMaze::instance()->getPlayer(), MazePos)->getPos().getY())->getChest()->getAlreadyOpen()) {
            if (GETCMP2(TheElementalMaze::instance(), ChestPanel) == NULL)
            {
                togglePanel(Heroes);
                Panel* p = new Panel(_ChestPanel_);
                allPanels[_ChestPanel_] = p;
                TheElementalMaze::instance()->addComponent<ChestPanel>(TheElementalMaze::instance()->getLaberinto()->getCasillaInfo(GETCMP2(TheElementalMaze::instance()->getPlayer(), MazePos)->getPos().getX(), GETCMP2(TheElementalMaze::instance()->getPlayer(), MazePos)->getPos().getY())->getChest());
            }
            else closeChest();
        }
        else if (TheElementalMaze::instance()->getPartyManager()->hasChestKeys()) {
            TheElementalMaze::instance()->getLaberinto()->getCasillaInfo(GETCMP2(TheElementalMaze::instance()->getPlayer(), MazePos)->getPos().getX(), GETCMP2(TheElementalMaze::instance()->getPlayer(), MazePos)->getPos().getY())->getChest()->setAlreadyOpen(true);
            TheElementalMaze::instance()->getPartyManager()->useChestKey();
        }
            
        break;
    case Targets:
        createTargets();
        break;
    case Habilities:
        createHabilities();
        break;
    case WeaponsAttacks:
        createWeaponAttacks();
        break;
    case MenuPrincipal:
        createMenuPrincipal();
        break;
    case HowToPlay:
        createGuide();
        break;
    case Options:
        createOptions();
        break;
    case Enemies:
        createEnemies();
        break;
    case Lobby:
        createLobby();
        break;
    case StashPanel:
        createStash();
        break;
    case Shop:
        createShop();
        break;
    case ButtonHeroToPartyPanel:
        createHeroToPartyPanel();
        break;
    case SellButtonPanel:
        createSellButtonPanel();
        break;
    case InventoryLobby:
        createInventoryLobby();
        break;
    case sendToStashPanel:
        createSendToStashPanel();
        break;
    case EquipPanel:
        createEquipPanel();
        break;
    case UnequipPanel:
        createUnequipPanel();
        break;
    case PausePanel:
        createPausePanel();
        break;
    default:
        break;
    }
}

void Interfaz::removePanel(idPanel panID)
{
    switch (panID)
    {
        /*case interfaz::Movement:
         break;
        case interfaz::Heroes:
         break;
        case interfaz::Inventory:
         break;
        case interfaz::Info:
         break;*/
    case interfaz::Minimap:
        TheElementalMaze::instance()->getLaberinto()->toggleMiniMap();
        break;
        /*case interfaz::Targets:
         break;
        case interfaz::Habilities:
         break;
        case interfaz::Fight:
         break;*/
    case interfaz::Turns:
        TheElementalMaze::instance()->removeComponent(ecs::PanelTurns);
        delete allPanels[panID];
        allPanels[panID] = nullptr;
        break;
        /*case interfaz::HeroesStats:
         break;*/
    case interfaz::DDPan:
        TheElementalMaze::instance()->removeComponent(ecs::PanelDnD);
        delete allPanels[panID];
        allPanels[panID] = nullptr;
        break;
        /*case interfaz::BigMap:
         break;
        case interfaz::Settings:
         break;*/
    case interfaz::DadosPan:
        TheElementalMaze::instance()->removeComponent(ecs::DadosP);
        delete allPanels[panID];
        allPanels[panID] = nullptr;
        break;
    case interfaz::DescPanObj:
        TheElementalMaze::instance()->removeComponent(ecs::PanelDescObj);
        delete allPanels[panID];
        allPanels[panID] = nullptr;
        break;
    case interfaz::Chat:
        TheElementalMaze::instance()->removeComponent(ecs::ChatInfo);
        break;
    case interfaz::_ChestPanel_:
        TheElementalMaze::instance()->removeComponent(ecs::ChestPanel);
        togglePanel(Heroes);
        break;
        /*case interfaz::MenuPrincipal:
         break;
        case interfaz::Lobby:
         break;
        case interfaz::Options:
         break;
        case interfaz::HowToPlay:
         break;
        case interfaz::Enemies:
         break;
        case interfaz::_LastPanId_:
         break;*/
    default:
        delete allPanels[panID];
        allPanels[panID] = nullptr;
        break;
    }
}

void Interfaz::resetPanel(idPanel panelID)
{
    removePanel(panelID);
    createPanel(panelID);
}

void Interfaz::removeChat()
{
    TheElementalMaze::instance()->removeComponent(ecs::ChatInfo);
}

void Interfaz::destroyPanel(idPanel panelID)
{
    /*delete allPanels[panelID];
    allPanels[panelID] = nullptr;*/
}

void Interfaz::togglePanel(Panel* pan)
{
    pan->toggleEnable();
}

bool Interfaz::getEnablePan(idPanel panID)
{
    if (getActivePan(panID)) return allPanels[panID]->getEnable();
    else return false;
}

void Interfaz::avPagHeroes()
{
    LobbyManager* loManager = TheElementalMaze::instance()->getLobbyManager();
    if (loManager->getPlayerStash()->heroes.size() > 20 * (pagHeroes + 1))
        pagHeroes++;
}
void Interfaz::rePagHeroes()
{
    if (pagHeroes > 0)
        pagHeroes--;
}
void Interfaz::avPagItems()
{
    LobbyManager* loManager = TheElementalMaze::instance()->getLobbyManager();
    if (loManager->getPlayerStash()->items.size() > 20 * (pagItems + 1))
        pagItems++;
}
void Interfaz::rePagItems()
{

    if (pagItems > 0)
        pagItems--;
}

void Interfaz::toggleCombat_Movement()
{
    togglePanel(Fight);
    togglePanel(Movement);
}

void Interfaz::init()
{
    ChatManager::Init();
    // Fondo de todo la interfaz, para delimitar claramente los paneles: 
    // (mejor que ButtonSlott ser�a crear unaclase foto/image y que button herede de ella)
    //iManager->addButton<ButtonSlott>(Vector2D(), game_->getWindowWidth(), game_->getWindowHeight(), src::Fondo); 
    createPanel(MenuPrincipal);
    createPanel(HowToPlay);


    togglePanel(HowToPlay);


    /*createPanel(Movement);
    createPanel(Heroes);
    createPanel(Info);

    togglePanel(Movement);
    togglePanel(Heroes);
    togglePanel(Info);*/
}

void Interfaz::update()
{
    InputHandler* ih_ = InputHandler::instance();
    if (ih_->isKeyDown(SDLK_t)) {
        // mouse event
        toggleCombat_Movement();
    }
    GameState state_ = TheElementalMaze::instance()->gameState();
    switch (state_)
    {
    case gameST::MainMenu:
        break;
    case gameST::LOBBY:
        if (getActivePan(DDPan)) removePanel(DDPan);
        if (getActivePan(Inventory)) removePanel(Inventory);
        if (getActivePan(UnequipPanel)) removePanel(UnequipPanel);
        if (getActivePan(EquipPanel)) removePanel(EquipPanel);
        ChatManager::instance()->clean_n_addLine(" ", LineColor::White);
        callbacks::startLobby(this);
        break;
    case gameST::START_EXPLORING:
        if (!getActivePan(Movement))
        {
            TheElementalMaze::instance()->wasInMaze = true;
            Message m;
            m.id_ = MsgId::_MOVIMIENTO_;
            TheElementalMaze::instance()->sendMsg(m);
            m.id_ = MsgId::_MINIMAP_;
            TheElementalMaze::instance()->sendMsg(m);
            // create Tutorial
            createPanel(Movement);
            createPanel(Heroes);
            createPanel(Info);
            createPanel(Chat); // CHAT/FEED
            string s = "Welcome! Here is where the adventure begins, dear friends";
            ChatManager::instance()->clean_n_addLine(s, linCol::Yellow);
        }
        break;
    case gameST::EXPLORING:
        if (!getEnablePan(Movement))
        {
            togglePanel(Movement);
            if (getActivePan(Fight)) {
                removePanel(Fight);
            }
        }
        break;
    case gameST::START_COMBAT:
        if (!getActivePan(Fight))
        {
            //ponerPanelDados
            createDados();

            Message m;
            m.id_ = MsgId::_COMBATE_;
            TheElementalMaze::instance()->sendMsg(m);
            togglePanel(Movement);
            createPanel(Fight);
            createPanel(Enemies);
            createPanel(Turns);
            toggleMinimap();
        }
        break;
    case gameST::END_COMBAT:
        if (getActivePan(Enemies))
        {
            //quitarPanelDados
            removePanel(DadosPan);

            Message m;
            m.id_ = MsgId::_INVENTARIO_;
            TheElementalMaze::instance()->sendMsg(m);
            m.id_ = MsgId::_CONFIG_;
            TheElementalMaze::instance()->sendMsg(m);
            m.id_ = MsgId::_SUPPORT_;
            TheElementalMaze::instance()->sendMsg(m);
            toggleMinimap();
            removePanel(Enemies);
            removePanel(Turns);
            TheElementalMaze::instance()->removeComponent(ecs::PanelTurns);
            checkHerosParty(); // check de puertas de la muerte
            TheElementalMaze::instance()->changeState(gameST::COMBAT);
        }
        break;
    case gameST::END_EXPLORING:
        if (getActivePan(DDPan)) removePanel(DDPan);
        if (getActivePan(Inventory)) removePanel(Inventory);
        if (getActivePan(UnequipPanel)) removePanel(UnequipPanel);
        if (getActivePan(EquipPanel)) removePanel(EquipPanel);
        removePanel(Movement);
        removePanel(Heroes);
        removePanel(Info);
        removeChat();
        // remove tutorial
        break;
    case gameST::PAUSA:
        createPausePanel();
        break;
    default:
        break;
    }
}

Entity* Interfaz::getEntity()
{
    return entity_;
}

void Interfaz::checkActiveHeroButton(HeroNum nAct)
{
    ButtonPanel* b = allPanels[Heroes]->getButtonActive();
    if (b != nullptr) {
        ButtonHero* b_hero = dynamic_cast<ButtonHero*>(b);
        if (b_hero != nullptr && b_hero->getNumHero() != nAct) {
            b->turnOFF();
            removePanel(DDPan);
        }
    }
}

void Interfaz::checkHerosParty()
{
    bool changed = false;
    vector<Entity*> savedHeroes;
    PartyManager* c = TheElementalMaze::instance()->getPartyManager();
    std::vector<Hero*> heroes = c->getHeroes();
    auto n = heroes.size(); // max number of heros
    for (auto i = 0u; i < n; i++)
        if (!heroes[i]) {
            allPanels[Heroes]->removeButton(i);
            changed = true;
        }
        else {
            savedHeroes.push_back(allPanels[Heroes]->getButton(i));
        }
    if (changed) allPanels[Heroes]->swapButtonList(savedHeroes);
}

void Interfaz::enemyDead(int indice) {
    Panel* p = allPanels[Enemies];
    p->removeButton(indice);
}

void Interfaz::closeChest()
{
    if (getActivePan(_ChestPanel_))
        removePanel(_ChestPanel_);
    togglePanel(Heroes);
    TheElementalMaze::instance()->removeComponent(ecs::CmpId::ChestPanel);
}