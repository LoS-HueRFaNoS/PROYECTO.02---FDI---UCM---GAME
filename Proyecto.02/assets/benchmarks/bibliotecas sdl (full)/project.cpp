#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"

int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) std::cout << "SDL: Ha funcionado!\n";
    else std::cout << "SDL: No ha funcionado...\n";
    if (IMG_Init(IMG_INIT_JPG) > 0) std::cout << "IMG: Ha funcionado!\n";
    else std::cout << "IMG: No ha funcionado...\n";
    if (TTF_OpenFont("ttf_fonts/FreeMono.ttf", 14) == 0) std::cout << "TTF: Ha funcionado!\n";
    else std::cout << "TTF: No ha funcionado...\n";
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) != -1) std::cout << "MIX: Ha funcionado!\n";
    else std::cout << "MIX: No ha funcionado...\n";
    return 0;    
}