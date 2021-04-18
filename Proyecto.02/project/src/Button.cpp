#include "Button.h"
#include "SDLGame.h"
#include "InterfazManager.h"
#include "Transform.h"
#include "Image.h"
#include "ButtonCtrl.h"
#include "Panel.h"
#include "PlayerMotion.h"

// todo el juego se une mediante GameMngr(entity_)
void Button::init(Vector2D pos, uint ancho, uint alto, Resources::TextureId imagen)
{
	//SDLGame* game = im->getEntity()->getSDLGame();
	_game
	addComponent<Transform>(pos, Vector2D(), ancho, alto, 0);
	addComponent<Image>(game->getTextureMngr()->getTexture(imagen));
	addComponent<ButtonCtrl>(im); // se pasa el callback directamente
}

template<typename Panel>
void ButtonType_2T<Panel>::click(CallBackOnClick* cb_, InterfazManager* im)
{
	if (!activated) { Button::click(cb_, im); }
	else { p; }
}

template<typename PlayerMotion>
inline void ButtonType<PlayerMotion>::click(CallBackOnClick* cb_, InterfazManager* im)
{
	switch (movementType_)
	{
	case MovType::rotR:
		callbacks::rotarDerecha();
		break;
	case MovType::rotL:
		callbacks::rotarIzquierda();
		break;
	case MovType::forward:
		callbacks::avanzar();
		break;
	case MovType::touch:
		callbacks::interactuar(im);
		break;
	default:
		break;
	}
}

//template<typename T>
//inline void ButtonType<T>::init(T* add, InterfazManager* im, CallBackOnClick* cb, Vector2D pos, uint ancho, uint alto, Resources::TextureId imagen)
//{
//	addon = add; // valor generico (extra) agregable para clasificar por tipos
//	Button::init(im, cb, pos, ancho, alto, imagen);
//	/*SDLGame* game = im->getEntity()->getSDLGame();
//	addComponent<Transform>(pos, Vector2D(), ancho, alto, 0);
//	addComponent<Image>(game->getTextureMngr()->getTexture(imagen));
//	addComponent<ButtonCtrl>(im, cb);*/
//}

//template<typename T>
//void ButtonType<T>::click(CallBackOnClick* cb_, InterfazManager* im)
//{
//	if (!activated) {
//		cb_(im);
//		activated = true;
//	}
//	else {
//		im->destroyPanel(addon->GetID());
//		activated = false;
//	}
//}
