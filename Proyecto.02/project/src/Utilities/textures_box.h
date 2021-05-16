#pragma once
#include "../Templates/Resources.h"
typedef unsigned int uint;
namespace textures_box {
	Resources::TextureId getHeroTxt(uint number);
	Resources::TextureId getEnemyTxt(uint number);
	Resources::TextureId getItemTxt(uint number);
	Resources::TextureId getHabilityTxt(uint hero, uint number);
};