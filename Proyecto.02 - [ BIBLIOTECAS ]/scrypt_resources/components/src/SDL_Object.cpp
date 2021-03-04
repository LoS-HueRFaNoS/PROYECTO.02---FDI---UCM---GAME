// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
//

#include "SDL_Object.h"

#pragma region METODOS_SDL_OBJECT

const void SDL_Object::saveToFile(ofstream& file)
{
	file << pos << ' ';
	file << width << ' ' << height << ' ';
}

SDL_Rect const SDL_Object::getDestRect()
{
	SDL_Rect destRect;
	destRect.h = height;
	destRect.w = width;
	destRect.y = int(pos.getY());
	destRect.x = int(pos.getX());
	return destRect;
}














// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
#pragma endregion