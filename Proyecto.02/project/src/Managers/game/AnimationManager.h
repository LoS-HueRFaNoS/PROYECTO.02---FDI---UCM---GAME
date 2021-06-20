#ifndef _ANIMATION_MANAGER_
#define _ANIMATION_MANAGER_

#include <vector>
#include "../../Utilities/checkML.h"
#include "../../ecs/Component.h"
#include "../../ecs/ecs.h"
#include "CombatManager.h"
#include "../../Structures/Vector2D.h"
#include "../../Components/Rectangle.h"

class TheElementalMaze;

class AnimationManager : public Component {
private:
	bool vibracion = false;
	bool vibAnimation = false;
	Uint32 startVibTime = 0;

	bool reward = false;
	Vector2D rewardPos = Vector2D(0, 0);
	

	bool habilidad = false;
	int turno = -1;
public:
	AnimationManager();

	virtual ~AnimationManager() {};

	int exp;
	int gold;
	int manaPotions;
	int healthPotions;

	void update() override;
	void draw() override;

	void setVibration(bool vib) { vibracion = vib; }
	void setVibAnimation(bool vib) { vibAnimation = vib; }
	void setVibStartTime(Uint32 vib) { startVibTime = vib; }
	void renderVibration();
	void setReward(bool rew) { reward = rew; }
	void renderReward();
	void setHabilidad(bool hab) { habilidad = hab; }
	void renderHabilidad();
	void setTurno(int tur) { turno = tur; }
	void renderTurno();

	

};


#endif // !_ANIMATION_MANAGER_