#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "SDLerror.h"

#pragma region METODOS_PROJECT

int main(int argc, char* argv[])
{
    string e = "Unable to initialize ";
    string end = ";\n";
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) std::cout << "SDL: Ha funcionado!\n";
    else SDLerror((e + "SDL" + end + string(SDL_GetError())).c_str());
    if (IMG_Init(IMG_INIT_JPG) > 0) std::cout << "IMG: Ha funcionado!\n";
    else SDLerror((e + "IMG" + end + string(IMG_GetError())).c_str());
    if (TTF_OpenFont("ttf_fonts/FreeMono.ttf", 14) == 0) std::cout << "TTF: Ha funcionado!\n";
    else SDLerror((e + "TTF" + end + string(TTF_GetError())).c_str());
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) != -1) std::cout << "MIX: Ha funcionado!\n";
    else SDLerror((e + "MIX" + end + string(Mix_GetError())).c_str());
    return 0;    
}

#pragma endregion