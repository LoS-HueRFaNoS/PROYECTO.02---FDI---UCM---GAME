#pragma once
#include "Entity.h"
#include "Resources.h"
#include "callbacks.h"
#include <cassert>

typedef unsigned int uint;

enum class AtkType { normal, magic, defend, escape };
enum class HeroNum { hero1, hero2, hero3, hero4 };
enum class Inf { inventory, potionHealth, potionMana, chat, config };

//class InterfazManager;
class Button : public Entity
{
protected:

	void initComponents(Vector2D pos, uint ancho, uint alto, Resources::TextureId imagen);

public:
	Button(SDLGame* game, EntityManager* mngr) :
		Entity(game, mngr)
	{};
	~Button() {};
	virtual void init(Vector2D pos, uint ancho, uint alto, Resources::TextureId imagen) {};

	virtual void click() = 0;
};

enum class MovType { rotR, rotL, forward, touch };

class ButtonMovimiento : public Button {
private:
	MovType movementType_;
public:
	ButtonMovimiento(SDLGame* game, EntityManager* mngr) : Button(game, mngr), movementType_(MovType::touch){};

	~ButtonMovimiento() {};

	virtual void init(Vector2D pos, uint ancho, uint alto, Resources::TextureId imagen, MovType movement) {
		movementType_ = movement;
		initComponents(pos, ancho, alto, imagen);
	};

	virtual void click() 
	{
		callbacks::movCommand((int)movementType_);
	}
};

//class ButtonMovimiento : public Button {
//public:
//	void setPlayerMotion(PlayerMotion* plmot) { playermotion_ = plmot; };
//	void setMovType(MovType movType) { movementType_ = movType; };
//private:
//	MovType movementType_;
//	PlayerMotion* playermotion_;
//public:
//	ButtonMovimiento(SDLGame* game, EntityManager* mngr) : Button(game, mngr) {};
//	virtual void click(Game* i) override
//	{
//		switch (movementType_)
//		{
//		case MovType::rotR:
//			playermotion_->rotarDerecha();
//			break;
//		case MovType::rotL:
//			playermotion_->rotarIzquierda();
//			break;
//		case MovType::forward:
//			playermotion_->avanzar();
//			break;
//		case MovType::touch:
//			callbacks::interactuar(i);
//			break;
//		default:
//			break;
//		}
//	}
//};
//
//class ButtonCombate : public Button {
//public:
//	void setPlayerMotion(PlayerMotion* plmot) { playermotion_ = plmot; };
//	void setAtkType(AtkType atkType) { attackType_ = atkType; };
//private:
//	AtkType attackType_;
//	PlayerMotion* playermotion_;
//public:
//	ButtonCombate(SDLGame* game, EntityManager* mngr) : Button(game, mngr) {};
//	virtual void click(Game* i) override
//	{
//		switch (attackType_)
//		{
//		case AtkType::normal:
//			callbacks::ataqueNormal(i);
//			break;
//		case AtkType::magic:
//			callbacks::ataqueMagico(i);
//			break;
//		case AtkType::defend:
//			callbacks::defensa(i);
//			break;
//		case AtkType::escape:
//			callbacks::huida(i);
//			break;
//		default:
//			break;
//		}
//	}
//};
//
//
//class ButtonHeroes : public Button {
//public:
//	void setPlayerMotion(PlayerMotion* plmot) { playermotion_ = plmot; };
//	void setHero(HeroNum hero) { hero_ = hero; };
//private:
//	HeroNum hero_;
//	PlayerMotion* playermotion_;
//public:
//	ButtonHeroes(SDLGame* game, EntityManager* mngr) : Button(game, mngr) {};
//	virtual void click(Game* i) override
//	{
//		switch (hero_)
//		{
//		case HeroNum::hero1:
//			callbacks::pruebaGame0(i);
//			break;
//		case HeroNum::hero2:
//			callbacks::pruebaGame1(i);
//			break;
//		case HeroNum::hero3:
//			callbacks::pruebaGame2(i);
//			break;
//		case HeroNum::hero4:
//			callbacks::pruebaGame3(i);
//			break;
//		default:
//			break;
//		}
//	}
//};
//
//class ButtonInfo : public Button {
//public:
//	void setPlayerMotion(PlayerMotion* plmot) { playermotion_ = plmot; };
//	void setInf(Inf inf) { inf_ = inf; };
//private:
//	Inf inf_;
//	PlayerMotion* playermotion_;
//public:
//	ButtonInfo(SDLGame* game, EntityManager* mngr) : Button(game, mngr) {};
//	virtual void click(Game* i) override
//	{
//		switch (inf_)
//		{
//		case Inf::inventory:
//			callbacks::inventario(i);
//			break;
//		case Inf::potionHealth:
//			callbacks::pocionVida(i);
//			break;
//		case Inf::potionMana:
//			callbacks::pocionMana(i);
//			break;
//		case Inf::chat:
//			callbacks::chat(i);
//			break;
//		case Inf::config:
//			callbacks::configuracion(i);
//			break;
//		default:
//			break;
//		}
//	}
//};