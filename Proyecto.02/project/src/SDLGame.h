#pragma once

#include <SDL.h>
#include "Resources.h"
#include "TexturesManager.h"
#include "AudioManager.h"
#include "FontsManager.h"
#include "RandomNumberGenerator.h"

#include <string>
#include <memory>
#include <assert.h>

#include "InputHandler.h"
using namespace std;

class SDLGame {
public:
	virtual ~SDLGame();

	SDLGame(SDLGame&) = delete;
	SDLGame& operator=(SDLGame&) = delete;

	inline static SDLGame* init(string windowTitle, int width, int height) {
		assert(instance_.get() == nullptr);
		instance_.reset(new SDLGame(windowTitle, width, height));
		return instance_.get();
	}

	inline static SDLGame* instance() {
		assert(instance_.get() != nullptr);
		return instance_.get();
	}

	inline SDL_Window* getWindow() const {
		return window_;
	}

	inline SDL_Renderer* getRenderer() const {
		return renderer_;
	}

	inline int getWindowWidth() const {
		return width_;
	}

	inline int getWindowHeight() const {
		return height_;
	}

	inline FontsManager* getFontMngr() const {
		return fonts_;
	}

	inline TexturesManager* getTextureMngr() const {
		return textures_;
	}

	inline AudioManager* getAudioMngr() const {
		return audio_;
	}

	inline RandomNumberGenerator* getRandGen() const {
		return random_;
	}

	inline InputHandler* getInputHandler() const {
		return InputHandler::instance();
	}

	inline void toggleFullScreen() {
		int flags = SDL_GetWindowFlags(window_);
		if (flags & SDL_WINDOW_FULLSCREEN) {
			SDL_SetWindowFullscreen(window_, 0);
		} else {
			SDL_SetWindowFullscreen(window_, SDL_WINDOW_FULLSCREEN);
		}

	}
	inline Uint32 getTime() {
		return SDL_GetTicks();
	}

private:
	SDLGame(string windowTitle_, int width, int height);

	void initSDL(); // initialize SDL
	void closeSDL(); // close SDL
	void initResources(); // initialize the SDLResources object with the data at the top of this file
	void closeResources(); // close the SDLResources object (frees all memory)

protected:

	FontsManager *fonts_;
	TexturesManager *textures_;
	AudioManager *audio_;
	RandomNumberGenerator *random_;

	SDL_Window *window_; // the window
	SDL_Renderer *renderer_;  // the renderer

	string windowTitle_; // window title
	int width_; // window width
	int height_; // window height

	static unique_ptr<SDLGame> instance_;

};

