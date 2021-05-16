#include "HabilityManager.h"


std::unique_ptr<HabilityManager> HabilityManager::instance_;

void HabilityManager::init()
{
	habilityMap_[LIGHTATTACK] = &HabilityManager::createHability<LightAttack>;
	habilityMap_[FIREBALL] = &HabilityManager::createHability<Fireball>;
	habilityMap_[BLOODYSTRIKE] = &HabilityManager::createHability<BloodyStrike>;
	habilityMap_[HEALINGWORD] = &HabilityManager::createHability<HealingWord>;
	habilityMap_[ALLYTEAMHEALEXAMPLE] = &HabilityManager::createHability<AllyTeamHealExample>;
	habilityMap_[SELFHEALEXAMPLE] = &HabilityManager::createHability<SelfHealExample>;
	habilityMap_[WINDBURST] = &HabilityManager::createHability<WindBurst>;
	habilityMap_[WINDSLASH] = &HabilityManager::createHability<WindSlash>;
	habilityMap_[ROCKPILLAR] = &HabilityManager::createHability<RockPillar>;
	habilityMap_[TOXICSHADOW] = &HabilityManager::createHability<ToxicShadow>;
	habilityMap_[TSUNAMI] = &HabilityManager::createHability<Tsunami>;
	habilityMap_[DIVINEPROTECTION] = &HabilityManager::createHability<DivineProtection>;
	habilityMap_[FLASH] = &HabilityManager::createHability<Flash>;
	habilityMap_[FREEZE] = &HabilityManager::createHability<Freeze>;
	habilityMap_[WHIRLPOOL] = &HabilityManager::createHability<Whirlpool>;
	habilityMap_[LIGHTBEAM] = &HabilityManager::createHability<LightBeam>;
	habilityMap_[DARKVORTEX] = &HabilityManager::createHability<DarkVortex>;
	habilityMap_[FIREARROW] = &HabilityManager::createHability<FireArrow>;
	habilityMap_[MEDITATE] = &HabilityManager::createHability<Meditate>;
	habilityMap_[LIGHTEN] = &HabilityManager::createHability<Lighten>;
	habilityMap_[STRENGTHEN] = &HabilityManager::createHability<Strengthen>;
	habilityMap_[TOUGHEN] = &HabilityManager::createHability<Toughen>;
	habilityMap_[BLOODTHIRST] = &HabilityManager::createHability<BloodThirst>;
	habilityMap_[SACRIFICE] = &HabilityManager::createHability<Sacrifice>;
	habilityMap_[DOUBLESHOT] = &HabilityManager::createHability<DoubleShot>;
	habilityMap_[THROWINGAXES] = &HabilityManager::createHability<ThrowingAxes>;
	habilityMap_[MORPH] = &HabilityManager::createHability<Morph>;
	habilityMap_[REVERSEMORPH] = &HabilityManager::createHability<ReverseMorph>;
	habilityMap_[HEAVYSTRIKE] = &HabilityManager::createHability<HeavyStrike>;
	habilityMap_[SMOKEARROW] = &HabilityManager::createHability<SmokeArrow>;
	habilityMap_[RAINOFDAGGERS] = &HabilityManager::createHability<RainOfDaggers>;
	habilityMap_[ROCKPROJECTILES] = &HabilityManager::createHability<RockProjectiles>;
	habilityMap_[TRICKSHOT] = &HabilityManager::createHability<TrickShot>;
	habilityMap_[GLADIATORBALLAD] = &HabilityManager::createHability<GladiatorBallad>;
	habilityMap_[WINDSONG] = &HabilityManager::createHability<WindSong>;
}

void HabilityManager::Init()
{
	assert(instance_.get() == nullptr);
	instance_.reset(new HabilityManager());
	instance_->init();
}
