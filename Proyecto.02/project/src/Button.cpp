#include "Button.h"
#include "SDLGame.h"
#include "InterfazManager.h"
#include "Transform.h"
#include "Image.h"
#include "ButtonCtrl.h"

// todo el juego se une mediante GameMngr(entity_)
void Button::init(InterfazManager* im, CallBackOnClick* cb, Vector2D pos, uint ancho, uint alto, Resources::TextureId imagen)
{
	SDLGame* game = im->getEntity()->getSDLGame();
	addComponent<Transform>(pos, Vector2D(), ancho, alto, 0);
	addComponent<Image>(game->getTextureMngr()->getTexture(imagen));
	addComponent<ButtonCtrl>(im, cb); // se pasa el callback directamente
}

template<typename T>
inline void ButtonType<T>::init(T* add, InterfazManager* im, CallBackOnClick* cb, Vector2D pos, uint ancho, uint alto, Resources::TextureId imagen)
{
	addon = add; // valor generico (extra) agregable para clasificar por tipos
	SDLGame* game = im->getEntity()->getSDLGame();
	addComponent<Transform>(pos, Vector2D(), ancho, alto, 0);
	addComponent<Image>(game->getTextureMngr()->getTexture(imagen));
	addComponent<ButtonCtrl>(im, cb);
}