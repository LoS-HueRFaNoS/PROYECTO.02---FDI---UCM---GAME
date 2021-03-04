// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
//

#include "windowAPP.h"

#pragma region METODOS_WINDOW_APP

// :::::::::::::::::: CONSTRUCTOR ::::::::::::::::::::::

windowAPP::windowAPP()
{
	// Inicia SDL:
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) throw SDLerror(SDL_GetError(), "SDL");

	window = SDL_CreateWindow("windowAPP: PACMAN", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr) throw SDLerror(string(SDL_GetError()).c_str(), "SDL window");
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer) throw SDLerror(string(SDL_GetError()).c_str(), "SDL render");
	
	setMaximizeWindow(); // establece el modo pantalla completa
}

// :::::::::::::::::: DESTRUCTOR ::::::::::::::::::::::

windowAPP::~windowAPP()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void windowAPP::setMaximizeWindow()
{
	/*SDL_Rect rect;
	SDL_GetWindowPosition(window, &rect.x, &rect.y);
	SDL_GetRendererOutputSize(renderer, &rect.w, &rect.h);
	SDL_MaximizeWindow(window);
	SDL_RenderSetViewport(renderer, &rect);*/

	// ---- C�digo usado es igual pero m�s robusto ----

	int tam_w, tam_h;
	SDL_Rect rect;
	SDL_GetRendererOutputSize(renderer, &tam_w, &tam_h);
	SDL_MaximizeWindow(window);
	SDL_GetWindowSize(window, &rect.w, &rect.h);
	RP_X = rect.x = rect.w / 2 - tam_w / 2;
	RP_Y = rect.y = rect.h / 2 - tam_h / 2;
	SDL_RenderSetViewport(renderer, &rect);
}

















// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
#pragma endregion