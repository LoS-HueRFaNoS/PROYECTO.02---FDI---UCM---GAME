#include "Font.h"

#include <iostream>
#include "../Utilities/SDL_macros.h"

using namespace std;

Font::Font() :
		font_(nullptr) {
}

Font::Font(const string& fileName, int size) {
	load(fileName, size);
}

Font::~Font() {
	close();
}

bool Font::load(const string& fileName, int size) {
	font_ = TTF_OpenFont(fileName.c_str(), size);
	if (font_ == nullptr) {
		throw "Couldn't load font: " + fileName;
	}
	return font_;
}

void Font::close() {
	if (font_) {
		TTF_CloseFont(font_);
		font_ = nullptr;
	}
}

SDL_Surface* Font::renderText(const string& text, SDL_Color color, bool isTitle) const {
	if (font_) {
		if (isTitle) TTF_SetFontStyle(font_, TTF_STYLE_UNDERLINE);
		else TTF_SetFontStyle(font_, TTF_STYLE_NORMAL);
		return TTF_RenderUTF8_Blended(font_, text.c_str(), color/*, hex2sdlcolor("0x000000FF")*/);
	} else {
		return nullptr;
	}
}
