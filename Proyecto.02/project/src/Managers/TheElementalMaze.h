#pragma once
#include "../ecs/Entity.h"
#include "../Structures/messages.h"

class CombatManager;
class InterfazManager;
class Interfaz;
class ItemManager;
class Laberinto;
class CharacterManager;
class PartyManager;
class LobbyManager;
class GameStateManager;
class TutorialManager;
class AnimationManager;

enum class GameState {
	MainMenu,
	LOBBY,
	DURING_LOBBY,
	START_EXPLORING,
	EXPLORING,
	START_COMBAT,
	COMBAT,
	END_COMBAT,
	END_EXPLORING,
	GAME_OVER,
	PAUSA,
	DURING_PAUSE
};
using gameST = GameState;

typedef unsigned int uint;

class TheElementalMaze : public Entity
{
private:

	static TheElementalMaze* instance_;

	SDLGame* game_;

	CombatManager* combatManager_; // compt
	Laberinto* laberinto_; // 
	Entity* player_; // 
	Entity* lab_; // 
	Interfaz* uiManager_; // compt
	InterfazManager* iManager_; // 
	ItemManager* itemManager_; //
	CharacterManager* characterManager_; // 
	PartyManager* partyManager_;
	LobbyManager* lobbyManager_;
	GameStateManager* stManager_; // compt
	TutorialManager* tutorial_; // compt
	AnimationManager* animManager_;
	int level = -1;
	uint floor;
	
	bool pause_ = false;
	bool firstLobbyCreated = false;
	GameState previousState; // Estado del juego antes de pausarlo
public:
	TheElementalMaze(SDLGame* game, EntityManager* mngr, CharacterManager* chMngr, InterfazManager* iMngr,AnimationManager* anim) :
		game_(game),
		characterManager_(chMngr),
		iManager_(iMngr),
		animManager_(anim),
		Entity(game, mngr),
		player_(nullptr),
		laberinto_(nullptr)
	{};

public:

	inline static TheElementalMaze* initInstace(SDLGame* game, EntityManager* mngr, CharacterManager* chMngr,InterfazManager* iMngr, AnimationManager* anim) {
		assert(instance_ == nullptr);
		instance_ = new TheElementalMaze(game, mngr, chMngr, iMngr, anim);
		instance_->init();
		return instance_;
	}

	inline static TheElementalMaze* instance() {
		assert(instance_ != nullptr);
		return instance_;
	}

	TheElementalMaze(TheElementalMaze&) = delete;

	TheElementalMaze& operator=(TheElementalMaze&) = delete;

	~TheElementalMaze();

	void init();
	void draw() override;

	void startExploring();
	void createLaberinto();
	void backFromDungeon();
	void firstLobby();
	void checkOutNoInitialEnemy();
	void startCombat();
	void onExitLaberinto();
	bool isFirstLobbyCreated() { return firstLobbyCreated; }
	Laberinto* getLaberinto() { return laberinto_; };
	int getLevel() { return level; }
	void nextLevel() { level++; if (level > 2) level = 0; }
	Entity* getPlayer() { return player_; };

	CharacterManager* getCharacterManager() { return characterManager_; }

	InterfazManager* getUIManager() { return iManager_; }

	ItemManager* getItemManager() { return itemManager_; }

	CombatManager* getCombatManager() { return combatManager_; }

	PartyManager* getPartyManager() { return partyManager_; }

	LobbyManager* getLobbyManager() { return lobbyManager_; }

	TutorialManager* getTutorial() { return tutorial_; }

	AnimationManager* getAnimManager() { return animManager_; }

	Interfaz* getInterfaz() { return uiManager_; }

	GameState gameState();

	bool isPause() { return pause_; }

	void setPauseState(bool set) { pause_ = set; }

	void changeState(GameState state);

	void sendMsg(Message m);

	GameState getPreviousState() { return previousState; };
	void registerPreviousState() { previousState = gameState(); }
	bool wasInMaze = false;
};