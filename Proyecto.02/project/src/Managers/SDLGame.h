#pragma once

#include <SDL.h>
#include "../Templates/Resources.h"
#include "../Templates/RPGLogic.h"
#include "../Managers/SDL/TexturesManager.h"
#include "../Managers/SDL/AudioManager.h"
#include "../Managers/SDL/FontsManager.h"
#include "../Utilities/RandomNumberGenerator.h"
#include "../Utilities/InputHandler.h"
#include "../Utilities/checkML.h"

#include <string>
#include <memory>
#include <assert.h>
#include <Windows.h>

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

	inline void setWindowSize(int width, int height) {
		width_ = width;
		height_ = height;
		SDL_SetWindowSize(window_, width, height);
	}

	int  throwDice(int dice) {
		return random_->nextInt(1, dice + 1);
	}

	inline Uint32 getTime() {
		return SDL_GetTicks();
	}

	void setFullScreen(bool fullscreen)
	{
		int newWidth, newHeight;
		if (fullscreen) {
			RECT rect;
			HWND hd = GetDesktopWindow();
			GetClientRect(hd, &rect);
			newWidth = (rect.right - rect.left);
			newHeight = (rect.bottom - rect.top);
		}
		else {
			newWidth = width_;
			newHeight = height_;
		}
		setWindowSize(newWidth, newHeight);
		SDL_SetWindowFullscreen(window_, fullscreen ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_RESIZABLE);
	}

	// pasa a  ser publico para poder segmentar el inicio
	void initResources(); // initialize the SDLResources object with the data at the top of this file

	// cambio a dimensiones de la pantalla actual
	double setVerticalScale(double num) { return num * getWindowHeight() / 1050; };
	double setHorizontalScale(double num) { return num * getWindowWidth() / 1920; };

	/// <summary>
	/// panel data with relative size respect window size and with given interfaz parameters
	/// (look .cpp for more info)
	/// </summary>
	/// <param name="x"> = position at X axe </param>
	/// <param name="y"> = position at Y axe </param>
	/// <param name="w"> = marco width size </param>
	/// <param name="h"> = marco height size </param>
	/// <param name="r"> = elements in a row </param>
	/// <param name="c"> = elements in a col </param>
	/// <param name="mw"> = horizontal margins size </param>
	/// <param name="mh"> = vertical margins size </param>
	/// <param name="ew"> = horizontal espace size between elements </param>
	/// <param name="eh"> = vertical espace size between elements </param>
	/// <returns> struct SDL_Panel </returns>
	SDL_Panel relativePanel(double x, double y, double w, double h, int r, int c, double mw, double mh, double ew, double eh);

private:
	SDLGame(string windowTitle_, int width, int height);

	void initSDL(); // initialize SDL
	void closeSDL(); // close SDL
	void closeResources(); // close the SDLResources object (frees all memory)

protected:

	FontsManager* fonts_;
	TexturesManager* textures_;
	AudioManager* audio_;
	RandomNumberGenerator* random_;

	SDL_Window* window_; // the window
	SDL_Renderer* renderer_;  // the renderer

	string windowTitle_; // window title
	int width_; // window width
	int height_; // window height

	static unique_ptr<SDLGame> instance_;

};

