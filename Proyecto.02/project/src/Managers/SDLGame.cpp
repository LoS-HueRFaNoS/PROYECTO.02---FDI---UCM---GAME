#include "SDLGame.h"
#include "SDL/SDLFontsManager.h"
#include "SDL/SDLAudioManager.h"
#include "SDL/SDLTexturesManager.h"

#include <time.h>
#include <iostream>

#include "../Utilities/SRandBasedGenerator.h"


unique_ptr<SDLGame> SDLGame::instance_;

/// \brief panel data with relative size respect window size and with given interfaz parameters
SDL_Panel SDLGame::relativePanel(double x, double y, double w, double h, int r, int c, double mw, double mh, double ew, double eh)
{
	SDL_Panel panel;

	// margins size
	panel.mw = setHorizontalScale(mw);
	panel.mh = setVerticalScale(mh);

	// number of elements in a row or in a col
	panel.r = r; // horizontal
	panel.c = c; // vertical

	// panel position respect window
	panel.x = setHorizontalScale(x);
	panel.y = setVerticalScale(y);

	// panel size in window
	panel.w = setHorizontalScale(w);
	panel.h = setVerticalScale(h);	

	// espaces between elements
	panel.ew = setHorizontalScale(ew);
	panel.eh = setVerticalScale(eh);

	// first element position
	panel.fcx = panel.x + panel.mw + panel.ew;
	panel.fcy = panel.y + panel.mh + panel.eh;

	// cells size
	panel.cw = ((panel.w - (panel.mw * 2)) / panel.r) - panel.ew;
	panel.ch = ((panel.h - (panel.mh * 2)) / panel.c) - panel.eh;

	// last element position
	panel.lcx = panel.x + panel.w - panel.mw - panel.ew - panel.cw;
	panel.lcy = panel.y + panel.h - panel.mh - panel.eh - panel.ch;

	return panel;
}

SDLGame::SDLGame(string windowTitle, int width, int height) :
		windowTitle_(windowTitle), width_(width), height_(height) {
	initSDL();
	//initResources(); // comentado para segmentar el inicio y reducir tiempos
}

SDLGame::~SDLGame() {
	closeResources();
	closeSDL();
}

void SDLGame::initSDL() {

	int sdlInit_ret = SDL_Init(SDL_INIT_EVERYTHING);
	assert(sdlInit_ret == 0);

	// Create window
	window_ = SDL_CreateWindow(windowTitle_.c_str(),
	SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED, width_, height_, SDL_WINDOW_SHOWN);
	assert(window_ != nullptr);

	// Create the renderer
	renderer_ = SDL_CreateRenderer(window_, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	assert(renderer_ != nullptr);

	// Clear screen (background color).
	int sdlSetDrawColor_ret = SDL_SetRenderDrawColor(renderer_, 0, 100, 100,
			255);  // Dark grey.
	assert(sdlSetDrawColor_ret != -1);
	int sdlRenderClear_ret = SDL_RenderClear(renderer_);
	assert(sdlRenderClear_ret != -1);
	SDL_RenderPresent(renderer_);

	// hide cursor by default
	SDL_ShowCursor(0); //

}

void SDLGame::closeSDL() {

	SDL_DestroyRenderer(renderer_);
	renderer_ = nullptr;

	SDL_DestroyWindow(window_);
	window_ = nullptr;

	SDL_Quit();
}

void SDLGame::initResources() {

	random_ = new SRandBasedGenerator();
	random_->init();

	textures_ = new SDLTexturesManager();
	textures_->init();

	fonts_ = new SDLFontsManager();
	fonts_->init();

	audio_ = new SDLAudioManager();
	audio_->init();

	for (auto &image : Resources::images_) {
		textures_->loadFromImg(image.id, renderer_, image.fileName);
	}

	for (auto &font : Resources::fonts_) {
		fonts_->loadFont(font.id, font.fileName, font.size);
	}

	for (auto &txtmsg : Resources::messages_) {
		textures_->loadFromText(txtmsg.id, renderer_, txtmsg.msg,
				fonts_->getFont(txtmsg.fontId), txtmsg.color);
	}

	for (auto &sound : Resources::sounds_) {
		audio_->loadSound(sound.id, sound.fileName);
	}

	for (auto &music : Resources::musics_) {
		audio_->loadMusic(music.id, music.fileName);
	}

}

void SDLGame::closeResources() {
	delete fonts_;
	delete textures_;
	delete random_;
	delete audio_;
}

