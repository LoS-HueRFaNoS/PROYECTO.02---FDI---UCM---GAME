#pragma once

#include "FontsManager.h"
#include <map>

/*
 *
 */
class SDLFontsManager: public FontsManager {
public:
	SDLFontsManager();
	virtual ~SDLFontsManager();

	// supposed to be called before start using the object
	bool init() override;

	Font* getFont(std::size_t tag) override;
	bool loadFont(std::size_t tag, const string& fileName, int size) override;
private:
	map<int, Font*> fonts_;
	bool initialized_;
};

