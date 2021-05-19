#include "HabilityManager.h"


std::unique_ptr<HabilityManager> HabilityManager::instance_;

void HabilityManager::init()
{
	habilityMap_[habID::LIGHTATTACK] = &HabilityManager::createHability<LightAttack>;
	habilityMap_[habID::FIREBALL] = &HabilityManager::createHability<Fireball>;
	habilityMap_[habID::BLOODYSTRIKE] = &HabilityManager::createHability<BloodyStrike>;
	habilityMap_[habID::HEALINGWORD] = &HabilityManager::createHability<HealingWord>;
	habilityMap_[habID::ALLYTEAMHEALEXAMPLE] = &HabilityManager::createHability<AllyTeamHealExample>;
	habilityMap_[habID::SELFHEALEXAMPLE] = &HabilityManager::createHability<SelfHealExample>;
	habilityMap_[habID::WINDBURST] = &HabilityManager::createHability<WindBurst>;
	habilityMap_[habID::WINDSLASH] = &HabilityManager::createHability<WindSlash>;
	habilityMap_[habID::ROCKPILLAR] = &HabilityManager::createHability<RockPillar>;
	habilityMap_[habID::TOXICSHADOW] = &HabilityManager::createHability<ToxicShadow>;
	habilityMap_[habID::TSUNAMI] = &HabilityManager::createHability<Tsunami>;
	habilityMap_[habID::DIVINEPROTECTION] = &HabilityManager::createHability<DivineProtection>;
	habilityMap_[habID::FLASH] = &HabilityManager::createHability<Flash>;
	habilityMap_[habID::FREEZE] = &HabilityManager::createHability<Freeze>;
	habilityMap_[habID::WHIRLPOOL] = &HabilityManager::createHability<Whirlpool>;
	habilityMap_[habID::LIGHTBEAM] = &HabilityManager::createHability<LightBeam>;
	habilityMap_[habID::DARKVORTEX] = &HabilityManager::createHability<DarkVortex>;
	habilityMap_[habID::FIREARROW] = &HabilityManager::createHability<FireArrow>;
	habilityMap_[habID::MEDITATE] = &HabilityManager::createHability<Meditate>;
	habilityMap_[habID::LIGHTEN] = &HabilityManager::createHability<Lighten>;
	habilityMap_[habID::STRENGTHEN] = &HabilityManager::createHability<Strengthen>;
	habilityMap_[habID::TOUGHEN] = &HabilityManager::createHability<Toughen>;
	habilityMap_[habID::BLOODTHIRST] = &HabilityManager::createHability<BloodThirst>;
	habilityMap_[habID::SACRIFICE] = &HabilityManager::createHability<Sacrifice>;
	habilityMap_[habID::DOUBLESHOT] = &HabilityManager::createHability<DoubleShot>;
	habilityMap_[habID::THROWINGAXES] = &HabilityManager::createHability<ThrowingAxes>;
	habilityMap_[habID::MORPH] = &HabilityManager::createHability<Morph>;
	habilityMap_[habID::REVERSEMORPH] = &HabilityManager::createHability<ReverseMorph>;
	habilityMap_[habID::HEAVYSTRIKE] = &HabilityManager::createHability<HeavyStrike>;
	habilityMap_[habID::SMOKEARROW] = &HabilityManager::createHability<SmokeArrow>;
	habilityMap_[habID::RAINOFDAGGERS] = &HabilityManager::createHability<RainOfDaggers>;
	habilityMap_[habID::ROCKPROJECTILES] = &HabilityManager::createHability<RockProjectiles>;
	habilityMap_[habID::TRICKSHOT] = &HabilityManager::createHability<TrickShot>;
	habilityMap_[habID::GLADIATORBALLAD] = &HabilityManager::createHability<GladiatorBallad>;
	habilityMap_[habID::WINDSONG] = &HabilityManager::createHability<WindSong>;
	habilityMap_[habID::DETERMINATION] = &HabilityManager::createHability<Determination>;
	habilityMap_[habID::BLESSING] = &HabilityManager::createHability<Blessing>;
}

void HabilityManager::Init()
{
	assert(instance_.get() == nullptr);
	instance_.reset(new HabilityManager());
	instance_->init();
}
