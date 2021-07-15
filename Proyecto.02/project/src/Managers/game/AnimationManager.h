#ifndef _ANIMATION_MANAGER_
#define _ANIMATION_MANAGER_


#include "../../ecs/Manager.h"
#include "../../Templates/RPGLogic.h"
#include <SDL_messagebox.h>

class TheElementalMaze;

class AnimationManager : public EntityManager {
private:
	bool vibracion = false;
	bool vibAnimation = false;
	Uint32 startVibTime = 0;

	bool reward = false;
	int rewardPosY = 0;

	bool receiveDamage = false;
	Uint32 startDamageTime = 0;
	int texSize = 0;

	bool miss = false;
	int misspos = 2;
	Uint32 startMissTime = 0;

	bool vs = false;
	bool win = false;
	Uint32 startVsTime = 0;
	bool vsR = false;
	int killPosX = 0;
	int frameKill = 0;
	
	int exp = 0;
	int gold = 0;
	int manaPotions = 0;
	int healthPotions = 0;
	bool chestKey = false;
	bool levelKey = false;
	bool noKeys = false;


	Texture* expTex = nullptr;
	Texture* goldTex = nullptr;
	Texture* manaTex = nullptr;
	Texture* manaNumTex = nullptr;
	Texture* healthTex = nullptr;
	Texture* healthNumTex = nullptr;
	Texture* transiTex = nullptr;
	Texture* keyTex = nullptr;
	Texture* keyLevelTex = nullptr;
	Texture* noKeysTex = nullptr;
	Texture* keyNumTex = nullptr;
	Texture* heroTex = nullptr;
	Texture* damageTex = nullptr;
	Texture* missTex = nullptr;
	Texture* vsTex = nullptr;
	Texture* heroVsTex = nullptr;
	Texture* EnemyVsTex = nullptr;
	Texture* KillTex = nullptr;


	bool transicion = false;
	Uint32 totalTransitTime = 0;
	Uint32 startTransitTime = 0;
	int frame = 0;
	void init();

public:
	AnimationManager(SDLGame* game) :EntityManager(game) {
		init();
	}


	virtual ~AnimationManager() {};



	void update() override;
	void draw() override;

	void animVib(rpgLogic::characterType current, rpgLogic::characterType next);
	void showDamage(int damage, Resources::TextureId hero);
	void showMiss(bool enemy);
	void showKillEnemy(Resources::TextureId hero, Resources::TextureId enemy, bool win);
	void showReward(int exp, int gold, int manaPotions, int healthPotions, bool chestKey);
	void showLevelKey();
	void showNoKeys();
	void renderVibration();
	void renderReward();
	void renderDamage();
	void renderMiss();
	void renderKillEnemy();
	void addtransicion(Uint32 transTime);
	void renderTransicion();
	bool getTransition() { return transicion; };


	

};


#endif // !_ANIMATION_MANAGER_