#pragma once

#include "TexturesManager.h"
#include <map>

/*
 *
 */
class SDLTexturesManager: public TexturesManager {
public:
	SDLTexturesManager();
	virtual ~SDLTexturesManager();

	// supposed to be called before start using the object
	bool init() override;

	Texture* getTexture(std::size_t tag) override {
		return textures_[tag];
	}

	bool loadFromImg(std::size_t, SDL_Renderer *renderer,
			const string &fileName) override;
	bool loadFromText(std::size_t, SDL_Renderer *renderer, const string &text,
			const Font *font, const SDL_Color &color) override;
private:
	void storeTexture(std::size_t tag, Texture *texture);

	bool initialized_;
	map<std::size_t, Texture*> textures_;

};
