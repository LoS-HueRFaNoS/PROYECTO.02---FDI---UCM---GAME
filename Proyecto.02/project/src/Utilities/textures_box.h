#pragma once
#include "../Templates/Resources.h"
#include "../GameObjects/Character.h"
typedef unsigned int uint;
namespace textures_box {
	Resources::TextureId getHeroTxt(uint number);
	Resources::TextureId getEnemyTxt(uint number);
	Resources::TextureId getItemTxt(uint number);
	Resources::TextureId getHabilityTxt(Hero* hero, uint number);
};