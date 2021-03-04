// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
//

#include "Texture.h"
#include "Font.h"
#include <iostream>

#pragma region METODOS_TEXTURE

void Texture::liberar()
{
	SDL_DestroyTexture(texture);
	texture = nullptr;
	w = h = 0;
}

void Texture::load(string filename, uint nRows, uint nCols) 
{
	SDL_Surface* tempSurface = IMG_Load(filename.c_str());
	if (!tempSurface) throw FileNotFoundError((filename + ";\n " + string(IMG_GetError())).c_str());
	liberar();
	texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	if (!texture) throw SDLerror(string(SDL_GetError()).c_str(), "SDL");
	numRows = nRows;
	numCols = nCols;
	w = tempSurface->w;
	h = tempSurface->h;
	fw = w / numCols;
	fh = h / numRows;
	SDL_FreeSurface(tempSurface);
}

 void Texture::loadFrom_Text(const fontName fileName, string text, SDL_Color color)
{
	SDL_Surface* surf = acedFontTTF().generateSurface(fileName, text, color);
	if (!surf)
		throw SDLerror(string(TTF_GetError()).c_str(), "SURFACE");
	else {
		liberar();
		texture = SDL_CreateTextureFromSurface(renderer, surf);
		if (!texture) {
			throw SDLerror(string(SDL_GetError()).c_str(), "SDL");
			w = h = 0;
		}
		else {
			w = surf->w;
			h = surf->h;
		}
	}
	SDL_FreeSurface(surf);
} 

void Texture::render(const SDL_Rect& destRect, SDL_RendererFlip flip) const 
{
	SDL_Rect srcRect;
	srcRect.x = 0; srcRect.y = 0;
	srcRect.w = w; srcRect.h = h;
	SDL_RenderCopyEx(renderer, texture, &srcRect, &destRect, 0, 0, flip);
}

void Texture::renderFrame(const SDL_Rect& destRect, int row, int col, int angle, SDL_RendererFlip flip) const 
{
	SDL_Rect srcRect;
	srcRect.x = fw * col;
	srcRect.y = fh * row;
	srcRect.w = fw;
	srcRect.h = fh;
	SDL_RenderCopyEx(renderer, texture, &srcRect, &destRect, angle, 0, flip);
}

 void Texture::renderText(const SDL_Rect& destRect) const
{
	SDL_Rect srcRect;
	srcRect.x = 0; srcRect.y = 0;
	srcRect.w = w; srcRect.h = h;
	SDL_RenderCopy(renderer, texture, &srcRect, &destRect);
}














 // @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
#pragma endregion