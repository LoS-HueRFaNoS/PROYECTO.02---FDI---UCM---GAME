#include <iostream>
#include <SDL.h>

int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) std::cout << "Ha funcionado!\n";
    else std::cout << "No ha funcionado...\n";
    return 0;    
}