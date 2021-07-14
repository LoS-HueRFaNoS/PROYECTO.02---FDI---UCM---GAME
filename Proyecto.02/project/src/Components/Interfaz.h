#pragma once
#include <string>
#include <list>
#include "../ecs/Component.h"
#include "../Structures/Panel.h"

class Font;

class InterfazManager;

using namespace std;

class Interfaz : public Component {

private:
    bool tutorial_active;
    bool playerSelectingTarget;
    InterfazManager* iManager;
    std::vector<Panel*> allPanels;
    uint pagHeroes = 0;
    uint pagItems = 0;
    void createFight();
    void createEnemies();
    void createMovement();
    void createHeroes();
    void createInfo();
    void createInventory();
    void createChest();
    void createBigMap() {}; //
    void createTurns(); //
    void createSettings() {}; //
    void createChat();
    void createTargets(); //
    void createHabilities(); //
    void createWeaponAttacks();
    void createInventoryLobby();
    void createSendToStashPanel();
    void createMenuPrincipal();
    void createLobby();
    void createOptions();
    void createGuide();
    void createShop();
    void createStash();
    void createInfoTienda();
    void createUnequipPanel();
    void toggleMinimap();
    string nameItemTienda;
    string descrItemTienda;
    void checkAndDeletePanel(idPanel id);
    void createHeroToPartyPanel();
    void createSellButtonPanel();
    void createEquipPanel();
    int selectedHeroToParty;
    bool isWeapon;
    bool isItemToEquipAWeapon;
    int selectedInventoryHero;
    int selectedInventoryItem;
    int selectedItem;
    std::vector<Message> msgsQueue_;
    MsgId activeMsg;
    SDL_Object* f;

    const int VOLUME_MAX = 100;
    const int VOLUME_MIN = 0;
    const uint VOLUME_BAR_HEIGHT = 50;
    const uint VOLUME_BAR_MAX = 400;
    int* gameVolume;
    int* gameSound;
    
public:
    Interfaz(InterfazManager* i, SDLGame* g) :
        Component(ecs::Interfaz, g),
        allPanels(std::vector<Panel*>(maxPanels, nullptr)),
        iManager(i),
        tutorial_active(true),
        playerSelectingTarget(false)
    {
        gameVolume = new int(game_->getAudioMngr()->INITIAL_GAME_VOLUME);
        gameSound = new int(game_->getAudioMngr()->INITIAL_GAME_SOUND);
    };
    virtual ~Interfaz();
    void createPausePanel();
    void createPanel(idPanel panelID);
    void removePanel(idPanel panelID);
    void resetPanel(idPanel panelID);
    void removeChat();
    void destroyPanel(idPanel panelID);

    void togglePanel(Panel* pan);
    void togglePanel(idPanel panID) { togglePanel(allPanels[panID]); };
    bool getEnablePan(idPanel panID);
    void avPagHeroes();
    void rePagHeroes();
    void avPagItems();
    void rePagItems();
    void toggleCombat_Movement();

    virtual void init() override;
    virtual void update() override;
    virtual void draw() override { iManager->draw(); };

    Entity* getEntity();
    bool getActivePan(idPanel pan) { return allPanels[pan] != nullptr; };
    void checkActiveHeroButton(HeroNum nAct);
    void checkHerosParty();
    void createFichaDD(uint nCharacter);
    void createDados();
    void createFichaDesc(Hability* hab, bool aff);
    void createFichaDescObj(Item* ite);

    void setNameItem(string name_) { nameItemTienda = name_; }
    void setDescrItem(string descr_) { descrItemTienda = descr_; }
    void setSelectedHeroToParty(int selectedHero) { selectedHeroToParty = selectedHero; }
    void setSelectedItem(int selectedItem_) { selectedItem = selectedItem_; }
    void setIsWeapon(bool isWeapon_) { isWeapon = isWeapon_; }
    void setSelectedInventoryHero(int selectedHero_) { selectedInventoryHero = selectedHero_; }
    void setSelectedInventoryItem(int selectedItem_) { selectedInventoryItem = selectedItem_; }
    void setIsItemToEquipAWeapon(bool isItemToEquipAWeapon_) { isItemToEquipAWeapon = isItemToEquipAWeapon_; }
    void enemyDead(int indice);
    void closeChest();
};