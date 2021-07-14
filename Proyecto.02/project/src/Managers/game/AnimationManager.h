#ifndef _ANIMATION_MANAGER_
#define _ANIMATION_MANAGER_


#include "../../ecs/Manager.h"
#include "../../Templates/RPGLogic.h"

class TheElementalMaze;

class AnimationManager : public EntityManager {
private:
	bool vibracion = false;
	bool vibAnimation = false;
	Uint32 startVibTime = 0;

	bool reward = false;
	int rewardPosY = 0;
	
	int exp = 0;
	int gold = 0;
	int manaPotions = 0;
	int healthPotions = 0;
	bool key = false;

	Texture* expTex = nullptr;
	Texture* goldTex = nullptr;
	Texture* manaTex = nullptr;
	Texture* manaNumTex = nullptr;
	Texture* healthTex = nullptr;
	Texture* healthNumTex = nullptr;
	Texture* transiTex = nullptr;
	Texture* keyTex = nullptr;
	Texture* keyNumTex = nullptr;


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
	void showReward(int exp, int gold, int manaPotions, int healthPotions, bool key) ;
	void renderVibration();
	void renderReward();

	void addtransicion(Uint32 transTime);
	void renderTransicion();
	bool getTransition() { return transicion; };

	

};


#endif // !_ANIMATION_MANAGER_