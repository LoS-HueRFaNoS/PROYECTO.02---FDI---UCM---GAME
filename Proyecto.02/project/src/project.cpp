#include "checkML.h"

#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "SDLerror.h"

#pragma region METODOS_PROJECT

int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) std::cout << "SDL: Ha funcionado!\n";
    else SDLerror(string(SDL_GetError()).c_str(), "SDL");
    if (IMG_Init(IMG_INIT_JPG) > 0) std::cout << "IMG: Ha funcionado!\n";
    else SDLerror(string(IMG_GetError()).c_str(), "IMG");
    if (TTF_OpenFont("ttf_fonts/FreeMono.ttf", 14) == 0) std::cout << "TTF: Ha funcionado!\n";
    else SDLerror(string(TTF_GetError()).c_str(), "TTF");
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) != -1) std::cout << "MIX: Ha funcionado!\n";
    else SDLerror(string(Mix_GetError()).c_str(), "MIX");
    return 0;    
}

#pragma endregion