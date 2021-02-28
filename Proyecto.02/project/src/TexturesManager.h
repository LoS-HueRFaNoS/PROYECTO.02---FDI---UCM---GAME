#pragma once

#include "Font.h"
#include "Texture.h"
#include <string>

using namespace std;

/*
 *
 */
class TexturesManager {
public:
	TexturesManager();
	virtual ~TexturesManager();

	// supposed to be called before start using the object
	virtual bool init() = 0;

	virtual Texture* getTexture(std::size_t tag) = 0;
	virtual bool loadFromImg(std::size_t tag, SDL_Renderer *renderer,
			const string &fileName) = 0;
	virtual bool loadFromText(std::size_t tag, SDL_Renderer *renderer,
			const string &texto, const Font *font, const SDL_Color &color = { 0,
					0, 0, 255 }) = 0;
};
