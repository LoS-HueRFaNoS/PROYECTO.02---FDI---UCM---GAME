// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
//

#pragma once
#ifndef WINDOW_APP_H_
#define WINDOW_APP_H_

#include "checkML.h"

#include "textureMachine.h"
#include "SDLError.h"
// inherits
#include "Singleton.h"

const uint WIN_WIDTH = 800;										// ancho de la ventana
const uint WIN_HEIGHT = 600;									// alto de la ventana

class windowAPP : public Singleton<windowAPP>
{
	friend Singleton<windowAPP>;
	windowAPP();
protected:
	SDL_Window* window = nullptr;								// window
	SDL_Renderer* renderer = nullptr;							// renderer
	uint RP_X, RP_Y;

public:
	virtual ~windowAPP();

	void setMaximizeWindow();
	Texture* getTexture(TextureName name) { return acedTxtMot().getTexture(name); };
	SDL_Renderer* getRenderer() { return renderer; };
	uint getWin_h() { return WIN_HEIGHT; };
	uint getWin_w() { return WIN_WIDTH; };
	uint getRP_Y() { return RP_Y; };
	uint getRP_X() { return RP_X; };
};

inline windowAPP& acedWinApp() {
	return *windowAPP::instance();
}














// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
#endif