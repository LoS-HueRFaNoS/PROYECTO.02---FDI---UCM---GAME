#ifndef _COMBAT_MANAGER_
#define _COMBAT_MANAGER_
#include "../../ecs/Component.h"
#include "../../GameObjects/Character.h"
#include "../../Utilities/checkML.h"

#include <queue>

enum CombatState {
    COMBAT_START,
    PASS_TURN,
    START_TURN,
    ACTION_PHASE_SPELL,
    ACTION_PHASE_TARGET, // target concreto
    END_TURN, // multitarget
    COMBAT_END,
    NO_COMBAT
};

class CombatManager : public Component {
private:

    vector<Hero*> _heroes;	// equipo formado por los heroes elegidos
    vector<Enemy*> _enemies; // enemigos en combate

    vector<Character*> _turnQueue; // lista ordenada de turnos

    Character* currentCharacter; // personaje actual en combate
    Character* nextCharacter; // personaje actual en combate

    int _turn = 0;

    int _exp = 0;

    int _gold = 0;

    bool _win = true;

    bool _boss = false;

    int savingRunningThrows = 0;


    CombatState _state;

    bool stateChanged = false;

    Hability* _habilityToCast = nullptr;
    characterType targetList = charTy::ENEMY;
    int maxTargets = 0;

    struct Initiative {
        characterType type;
        int pos;
        int roll;
        Initiative(characterType t, int p, int r) {
            type = t;
            pos = p;
            roll = r;
        }
    };

    struct initiative_roll
    {
        inline bool operator() (const Initiative& in1, const Initiative& in2)
        {
            return (in1.roll > in2.roll);
        }
    };

    struct escape_failed
    {
        inline bool operator() (const Character* c1, const Character* c2)
        {
            return c1->getType() == characterType::ENEMY && c2->getType() != characterType::ENEMY;
        }
    };

    void onStateChanged();

    void castToSingleTarget(int input);

    void calculateTurns();

    void passTurn();

    bool checkEnd();

    void endCombat();

    void castToTeam();

    void tryEscape();

    /*void castToSingleTarget(int input);*/

#pragma region CombatePorConsola

 //void consoleCombat();

    void showTeams();

    void showQ();

    void animVib();

    void showTargets();

#pragma endregion
public:
    CombatManager() : currentCharacter(nullptr), _heroes(vector<Hero*>()), _enemies(vector<Enemy*>()), Component(ecs::CombatManager)
    {}

    ~CombatManager() {}

    void update() override;


    Character* nextTurn() {
        if (!_turnQueue.empty()) return _turnQueue[_turn];
    }

    void addCharacter(Character* c) {
        if (size_t(c->getType()))
            _enemies.push_back(dynamic_cast<Enemy*>(c));
        else
            _heroes.push_back(dynamic_cast<Hero*>(c));
    }

    void addHeroesTeam(vector<Hero*> heroes) {
        _heroes = heroes;
    }

    bool isABoss();

    vector<Hero*> getHeroesTeam()
    {
        return _heroes;
    }

    vector<Enemy*> getEnemiesTeam()
    {
        return _enemies;
    }

    void addEnemyTeam(vector<Enemy*> enemies) {
        _enemies = enemies;
    }

    void startCombat(bool boss = false);

    int calculateExp();

    void throwHability(Character* objective, Hability* hability);

    void changeState(CombatState state) { _state = state; stateChanged = true; }

    // -------- METODOS NECESARIOS PARA INTERFAZ ---------
    CombatState getState() { return _state; }

    Character* getCharacter(int index, characterType type) {
        return  size_t(type) ? static_cast<Character*>(_enemies[index]) : static_cast<Character*>(_heroes[index]);
    };

    size_t getHerosTam() { return _heroes.size(); }
    size_t getEnemysTam() { return _enemies.size(); }

    void sendKeyEvent(int key);

    void castHability(Hability* hability);

    characterType getCurrentTarget() { return targetList; }

    Character* getCurrentCharacter() { return currentCharacter; }

    vector<Character*> getCurrentTargetList() {
        std::vector<Character*> ret = size_t(targetList) ? std::vector<Character*>(_enemies.begin(), _enemies.end()) : std::vector<Character*>(_heroes.begin(), _heroes.end());
        return ret;
    }
    vector<Character*> getCurrentTurnsList() {
        return _turnQueue;
    }

    bool isMagicAttack();
    void resetHabilityToCast();

    int getTurn() { return _turn; }
    // ----------------------------------------------------
};


#endif