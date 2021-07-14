#include "../../Templates/RPGLogic.h"
#include "CombatManager.h"
#include "CharacterManager.h"
#include "PartyManager.h"
#include "AnimationManager.h"
#include "../TheElementalMaze.h"
#include "../../Components/Laberinto.h"
#include "ChatManager.h"
#include "../../Components/Paneles/PanelTurns.h"

#pragma region CombatePorConsola

#include <iomanip>
#include <string>

void CombatManager::showTeams()
{
    system("cls");
    cout << "---------- HEROES ----------" << endl;
    for (Hero* h : _heroes) {
        CharacterSheet* s = h->getCharacterSheet();
        if (h->isDead())
            cout << std::setfill(' ') << std::left << setw(10) << s->name << std::right << setw(8) << "DEAD" << endl;
        else
        {
            cout << std::setfill(' ') << std::left << setw(12) << s->name << setw(15) << "HP " + to_string(s->hitPoints()) + "/" + to_string(s->maxHitPoints()) <<
                setw(15) << "MP " + to_string(s->manaPoints()) + "/" + to_string(s->maxManaPoints()) << std::right <<
                " STR " << std::setfill('0') << setw(2) << s->getStat(rpgLogic::ms::STR).value << "  CON " << std::setfill('0') << setw(2) <<
                s->getStat(rpgLogic::ms::CON).value << "  DEX " << std::setfill('0') << setw(2) << s->getStat(rpgLogic::ms::DEX).value << "  INT " <<
                std::setfill('0') << setw(2) << s->getStat(rpgLogic::ms::INT).value << endl;
        }
    }

    cout << endl << "---------- ENEMIES ----------" << endl;

    for (Enemy* e : _enemies) {
        CharacterSheet* s = e->getCharacterSheet();
        if (e->isDead())
            cout << std::setfill(' ') << std::left << setw(10) << s->name << std::right << setw(8) << "DEAD" << endl;
        else {
            cout << std::setfill(' ') << std::left << setw(12) << s->name << setw(15) << "HP " + to_string(s->hitPoints()) + "/" + to_string(s->maxHitPoints()) <<
                setw(15) << "MP " + to_string(s->manaPoints()) + "/" + to_string(s->maxManaPoints()) << std::right <<
                " STR " << std::setfill('0') << setw(2) << s->getStat(rpgLogic::ms::STR).value << "  CON " << std::setfill('0') << setw(2) <<
                s->getStat(rpgLogic::ms::CON).value << "  DEX " << std::setfill('0') << setw(2) << s->getStat(rpgLogic::ms::DEX).value << "  INT " <<
                std::setfill('0') << setw(2) << s->getStat(rpgLogic::ms::INT).value << endl;
        }
    }

}

void CombatManager::showQ()
{
    cout << std::left << std::setfill(' ') << "\n---------- TURN QUEUE ----------" << endl;

    for (int i = 0; i < _turnQueue.size(); i++) {
        cout << setw(15) << _turnQueue[i]->name();
        if (i == _turn)
            cout << "<----";
        cout << "\n";
    }

}

void CombatManager::animVib()
{
    TheElementalMaze::instance()->getAnimManager()->animVib(currentCharacter->getType(), nextCharacter->getType());
}



void CombatManager::showTargets()
{
    cout << "TARGETS (Press enter to cancel spell): " << endl;

    maxTargets = 0;
    try {
        for (Character* ch : getCurrentTargetList()) {

            CharacterSheet* c = ch->getCharacterSheet();
            cout << maxTargets << ". " << std::setfill(' ') << std::left << setw(12) << c->name << setw(15) << "HP " + to_string(c->hitPoints()) + "/" + to_string(c->maxHitPoints()) << endl;
            maxTargets++;

        }
    }
    catch (...) { cout << "ERROR: taking out targets"; }
    cout << "Choose target: ";
}

#pragma endregion


void CombatManager::startCombat(bool boss)
{
    _boss = boss;
    if (_boss) {
        _gold = 500;
        game_->getAudioMngr()->playMusic(Resources::AudioId::CombateBoss, -1);
    }
    else {
        _gold = 50;
        game_->getAudioMngr()->playMusic(Resources::AudioId::Combate, -1);
    }
    changeState(COMBAT_START);
}

void CombatManager::passTurn()
{
    AnimationManager* anim = TheElementalMaze::instance()->getAnimManager();
    if (!checkEnd()) {
        for (std::vector<Character*>::iterator it = _turnQueue.begin(); it != _turnQueue.end();) {
            if ((*it)->isDead()) {
                if ((bool)((*it)->getType()) || (!(bool)((*it)->getType()) && static_cast<Hero*>(*it)->getDeathGate())) {
                    if ((bool)((*it)->getType()))
                        _enemies.erase(std::find(_enemies.begin(), _enemies.end(), (*it)));
                    else
                        _heroes.erase(std::find(_heroes.begin(), _heroes.end(), (*it)));

                    it = _turnQueue.erase(it);
                }
                else
                    it++;
            }
            else {
                it++;
            }
        }
        _turn = ++_turn % _turnQueue.size();
        currentCharacter = _turnQueue[_turn];

        if (_turnQueue.size() > 1)
            nextCharacter = _turnQueue[(_turn + 1) % _turnQueue.size()];


        changeState(START_TURN);
    }
    else
    {

        changeState(COMBAT_END);

    }
}

bool CombatManager::checkEnd()
{
    bool end = true;
    for (Hero* h : _heroes)
        end = end * h->isDead();
    if (end) {
        _win = false;
        return true;
    }
    end = true;
    for (Enemy* e : _enemies)
        end = end * e->isDead();
    return end;
}

bool CombatManager::isABoss()
{
    for (Enemy* e : _enemies)
        if (e->isBoss()) _boss = true;

    return _boss;
}

void CombatManager::tryEscape()
{
    if (isABoss()) {
        cout << "YOU CAN'T ESCAPE FROM THIS COMBAT\n";
        ChatManager::instance()->add("YOU CAN'T ESCAPE FROM THIS COMBAT", linCol::Red);
        return;
    }

    cout << "YOU TRY TO ESCAPE\n";
    ChatManager::instance()->add("YOU TRY TO ESCAPE", LineColor::White);
    int tiradasH = 0;
    int tiradasE = 0;

    for (Hero* h : _heroes) {
        if (!h->isDead())
        {
            int huida = h->throwStat(ms::DEX);
            if (tiradasH < huida)
                tiradasH = huida;
        }
    }

    for (Enemy* e : _enemies) {
        if (!e->isDead())
        {
            int huida = e->throw20PlusMod(ms::DEX, false);
            if (tiradasE < huida)
                tiradasE = huida;
        }
    }

    cout << "Heroes: " << tiradasH << "\n";
    ChatManager::instance()->add("Heroes: " + to_string(tiradasH), LineColor::Green);
    cout << "Enemies(+5): " << tiradasE + 5 << "\n";
    ChatManager::instance()->add("Enemies(+5): " + to_string(tiradasE + 5), LineColor::Green);

    if (tiradasH > tiradasE + 5) 
    {
        savingRunningThrows++;

        if (savingRunningThrows > 2)
        {
            cout << "YOU ESCAPED \n";
            ChatManager::instance()->add("YOU ESCAPED", LineColor::Green);
            bool leftBehind = false;
            savingRunningThrows = 0;
            _exp = 0;
            _gold = 0;

            for (Hero* h : _heroes)
                if (h->isDead()) {
                    h->killHero();
                    leftBehind = true;
                    cout << "You just left " << h->name() << " behind !!! \n";
                    ChatManager::instance()->add("You just left " + h->name() + " behind !!!", LineColor::Red);
                }
            if (!leftBehind) {
                cout << "No one was left behind\n";
                ChatManager::instance()->add("No one was left behind", LineColor::White);
            }
            changeState(COMBAT_END);
            _win = true;
        }

        else
        {
            cout << "YOU NEED " << (3 - savingRunningThrows) << " TO ESCAPE FROM THE COMBAT\n";
            ChatManager::instance()->add("YOU NEED MORE THROWS: " + to_string(3 - savingRunningThrows), LineColor::Green);
        }
    }

    else {
        cout << "YOU FAILED TO ESCAPE \n";
        ChatManager::instance()->add("YOU FAILED TO ESCAPE", LineColor::Red);
        sort(_turnQueue.begin(), _turnQueue.end(), escape_failed());
        _turn = -1;
        changeState(END_TURN);
    }
}

void CombatManager::endCombat()
{
    if (_win) {
        cout << "YOU WIN" << endl << _exp << " EXP SHARED" << endl;
        ChatManager::instance()->clean_n_addLine("YOU WIN", LineColor::Green);

        if (_gold > 0) {
            cout << "You find " << _gold << " gold coins" << endl;
            TheElementalMaze::instance()->getPartyManager()->gold += _gold;
            ChatManager::instance()->add("You find " + std::to_string(_gold) + " gold coins", LineColor::Yellow);
            int manaPotions = throwDice(1, 4) - 1;
            cout << "You find " << manaPotions << " mana potions" << endl;
            if (manaPotions > 0)
                ChatManager::instance()->add("You find " + std::to_string(manaPotions) + "  mana potions", LineColor::Blue);
            TheElementalMaze::instance()->getPartyManager()->manaPotions += manaPotions;
            int healthPotions = throwDice(1, 4) - 1;
            cout << "You find " << manaPotions << " health potions" << endl;
            if (healthPotions > 0)
                ChatManager::instance()->add("You find " + std::to_string(healthPotions) + " health potions", LineColor::Green);
            TheElementalMaze::instance()->getPartyManager()->healthPotions += healthPotions;

            int randomKey = rand() % 10; //Numero aleatorio entre 0 y 9
            bool dropKey = randomKey > 6; //Solo si randomKey es 7, 8 o 9 dropea llave (30%)
            if (dropKey) TheElementalMaze::instance()->getPartyManager()->takeChestKey();
            TheElementalMaze::instance()->getAnimManager()->showReward(_exp, _gold, manaPotions, healthPotions, dropKey);

        }
        ChatManager::instance()->add(std::to_string(_exp) + " exp", LineColor::Yellow);
        for (Hero* h : _heroes) {
            if (h->getDeathGate())
                TheElementalMaze::instance()->getPartyManager()->removeHero(h);
            else
                h->endCombat(_exp);
        }
        // si es lich derrotado y vuelve a empezar
    }
    else {
        cout << "Another party lost to the Lich" << endl;
        ChatManager::instance()->clean_n_addLine("Another party lost to the Lich", LineColor::Red);
        game_->getAudioMngr()->playMusic(Resources::AudioId::Derrota, 0);
        TheElementalMaze::instance()->getPartyManager()->partyLost();
        // vuelta al lobby
    }

    _heroes.clear();
    for (Enemy* e : _enemies) {
        e->disable();
    }
    _enemies.clear();
    TheElementalMaze::instance()->checkOutNoInitialEnemy();
    _turnQueue.clear();
}

void CombatManager::castHability(Hability* hability)
{
    ObjectiveType t = hability->getObjectiveType();
    cout << "\n";

    _habilityToCast = hability;

    switch (t)
    {
    case objTy::SINGLEALLY:
        targetList = currentCharacter->getType();
        changeState(ACTION_PHASE_TARGET);
        break;
    case objTy::SINGLEENEMY:
        targetList = (characterType)((int)currentCharacter->getType() ^ 1);
        changeState(ACTION_PHASE_TARGET);
        break;
    case objTy::ALLYTEAM:
        targetList = currentCharacter->getType();
        castToTeam();
        break;
    case objTy::ENEMYTEAM:
        targetList = (characterType)((int)currentCharacter->getType() ^ 1);
        castToTeam();
        break;
    case objTy::CASTER:
        throwHability(hability->getCaster(), hability);
        break;
    default:
        break;
    }
}

bool CombatManager::isMagicAttack()
{
    if (_habilityToCast != nullptr) {
        if (_habilityToCast->getID() == habID::LIGHTATTACK || _habilityToCast->getID() == habID::HEAVYSTRIKE)
            return false;
        else
            return true;
    }
}

void CombatManager::resetHabilityToCast()
{
    _habilityToCast = nullptr;
    _state = ACTION_PHASE_SPELL;
}

void CombatManager::castToTeam()
{
    if (size_t(targetList)) {
        for (Enemy* e : _enemies)
            if (!e->isDead())throwHability(e, _habilityToCast);
    }
    else {
        for (Hero* h : _heroes)
            if (!h->isDead())throwHability(h, _habilityToCast);
    }

}


void CombatManager::castToSingleTarget(int input)
{
    if (!(input < maxTargets && input >= 0)) {
        cout << "Use a valid index please: \n";
        return;
    }

    throwHability(size_t(targetList) ? dynamic_cast<Character*>(_enemies[input]) : dynamic_cast<Character*>(_heroes[input]), _habilityToCast);
}

void CombatManager::throwHability(Character* objective, Hability* hability)
{
    std::string out = hability->name() + " on " + objective->name();
    cout << out << endl;
    ChatManager::instance()->add(out, LineColor::White);
    int hit = hability->getCaster()->throw20PlusMod(hability->getMod(), true);
    hability->getCaster()->getCharacterSheet()->recieveMana(-hability->getMana());
    if ((size_t(hability->getHabilityType()) > 1) || objective->checkHit(hit)) {
        cout << hability->name() << " hits" << endl;;
        ChatManager::instance()->add(hability->name() + " hits", LineColor::White);
        if (hit == 100) {
            cout << "CRITICAL" << endl;
            ChatManager::instance()->add("CRITICAL", LineColor::Yellow);
        }
        hability->throwHability(objective, hit == 100);
    }
    else {
        if (hit == -100) {
            cout << "CRITICAL FAILURE" << endl;
            ChatManager::instance()->add("CRITICAL FAILURE", LineColor::Red);
        }
        cout << "No Hit" << endl;
        ChatManager::instance()->add("No hit", LineColor::White);


    }
    cout << "\n\n";

    changeState(END_TURN);
}

void CombatManager::calculateTurns()
{
    vector<Initiative> ini;
    for (int i = 0; i < _heroes.size(); i++)
        ini.push_back(Initiative(_heroes[i]->getType(), i, throwDice(1, _heroes[i]->getStat(ms::DEX), false) + _heroes[i]->getMod(ms::DEX)));
    for (int i = 0; i < _enemies.size(); i++)
        ini.push_back(Initiative(_enemies[i]->getType(), i, throwDice(1, _enemies[i]->getStat(ms::DEX), false) + _enemies[i]->getMod(ms::DEX)));

    sort(ini.begin(), ini.end(), initiative_roll());

    for (Initiative i : ini) {
        if (size_t(i.type))
            _turnQueue.push_back(_enemies[i.pos]);
        else
            _turnQueue.push_back(_heroes[i.pos]);
    }
    currentCharacter = _turnQueue[0];
    if (_turnQueue.size() > 1)
        nextCharacter = _turnQueue[1];


}

int CombatManager::calculateExp()
{
    for (Enemy* e : _enemies)
        _exp += e->getExp();

    return _exp;
}


void CombatManager::onStateChanged()
{
    stateChanged = false;

    switch (_state)
    {
    case COMBAT_START:
        _turn = 0;
        _exp = 0;
        currentCharacter = nullptr;
        nextCharacter = nullptr;
        calculateTurns();
        calculateExp();
        changeState(START_TURN);
        break;
    case PASS_TURN:
        passTurn();
        break;
    case START_TURN:
#ifdef DEBUG
        showTeams();
#endif // DEBUG
        animVib();
        showQ();
        cout << "---------- START TURN ----------" << endl;
        changeState(ACTION_PHASE_SPELL);
        currentCharacter->startTurn(this);

        break;
    case ACTION_PHASE_SPELL:
        if (!size_t(currentCharacter->getType()))
            static_cast<Hero*>(currentCharacter)->showSpellList();
        break;
    case ACTION_PHASE_TARGET:
        showTargets();
        break;
    case END_TURN:
        currentCharacter->endTurn();
        cout << "---------- PRESS ENTER TO END TURN ----------" << endl;
        ChatManager::instance()->add("PRESS TO END TURN", linCol::White);
        break;
    case COMBAT_END:
        endCombat();
        TheElementalMaze::instance()->changeState(gameST::END_COMBAT);
        changeState(NO_COMBAT);
        break;
    case NO_COMBAT:
        if (_win)
            TheElementalMaze::instance()->changeState(gameST::EXPLORING);
        else {
            TheElementalMaze::instance()->onExitLaberinto();
            TheElementalMaze::instance()->changeState(gameST::LOBBY);
        }

        break;
    default:
        break;
    }
}

void CombatManager::sendKeyEvent(int key)
{
    switch (_state)
    {
    case END_TURN:
        if (key == -1) {
            changeState(PASS_TURN);		// terminar turno (para que continue el siguiente)
            ChatManager::instance()->clean_n_addLine(" ", linCol::White);
        }
        break;
    case ACTION_PHASE_SPELL:

        switch (key)
        {
        case -1:
            changeState(END_TURN);		// pasar turno (sin hacer nada)
            break;
        case -4:
            tryEscape();
            break;
        case -5: case -6:
            TheElementalMaze::instance()->getPartyManager()->usePotion((Hero*)currentCharacter, (6 + key));
            break;
        default:
            if (!size_t(currentCharacter->getType()))
                static_cast<Hero*>(currentCharacter)->manageInput(this, key);
            break;
        }
        break;
    case ACTION_PHASE_TARGET:
        if (key == -1) {
            _habilityToCast = nullptr;
            changeState(ACTION_PHASE_SPELL);
            break;
        }
        if (!size_t(currentCharacter->getType()) && key >= 0)
            castToSingleTarget(key);
        break;
    default:
        break;
    }
}

void CombatManager::update()
{
    if (TheElementalMaze::instance()->gameState() != gameST::COMBAT)
        return;
    if (stateChanged)
        onStateChanged();



#if (defined _DEBUG)
    InputHandler* ih = InputHandler::instance();

    if (ih->keyDownEvent()) {
        if (ih->isKeyDown(SDLK_0)) sendKeyEvent(0);
        else if (ih->isKeyDown(SDLK_1)) sendKeyEvent(1);
        else if (ih->isKeyDown(SDLK_2)) sendKeyEvent(2);
        else if (ih->isKeyDown(SDLK_3)) sendKeyEvent(3);
        else if (ih->isKeyDown(SDLK_4)) sendKeyEvent(4);
        else if (ih->isKeyDown(SDLK_5)) sendKeyEvent(5);
        else if (ih->isKeyDown(SDLK_6)) sendKeyEvent(6);
        else if (ih->isKeyDown(SDLK_7)) sendKeyEvent(7);
        else if (ih->isKeyDown(SDLK_8)) sendKeyEvent(8);
        else if (ih->isKeyDown(SDLK_9)) sendKeyEvent(9);
        else if (ih->isKeyDown(SDLK_RETURN))
            sendKeyEvent(-1);			// Saltar turno , terminar turno
        else if (ih->isKeyDown(SDLK_l)) sendKeyEvent(-2);			// Ataque ligero
        else if (ih->isKeyDown(SDLK_h)) sendKeyEvent(-3);			// Ataque pesado
        else if (ih->isKeyDown(SDLK_x)) sendKeyEvent(-4);			// Intentar Huir
        else if (ih->isKeyDown(SDLK_q)) sendKeyEvent(-5);			// Poción de mana
        else if (ih->isKeyDown(SDLK_e)) sendKeyEvent(-6);			// Poción de vida
    }
#endif
}


