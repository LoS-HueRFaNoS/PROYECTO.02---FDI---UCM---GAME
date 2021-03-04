// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
//

#pragma once
#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "checkML.h"

#include "SDL_image.h" // imagenes png
#include "Font.h"

class Texture 
{
private:
    SDL_Texture* texture = nullptr;
    SDL_Renderer* renderer = nullptr;
    uint w = 0;
    uint h = 0;
    uint fw = 0; // Frame width
    uint fh = 0; // Frame height
    uint numCols = 1;
    uint numRows = 1;

public:
    Texture() {};
    Texture(SDL_Renderer* r) : renderer(r) {};
    Texture(SDL_Renderer* r, string filename, uint numRows = 1, uint numCols = 1) : renderer(r) { load(filename, numRows, numCols); };
    Texture(SDL_Renderer* r, const fontName fileName, string text, SDL_Color color) : renderer(r) { loadFrom_Text(fileName, text, color); };
    ~Texture() { liberar(); };
    void liberar();

    int getW() const { return w; };     // devuelve el ancho
    int getH() const { return h; };     // devuelve el alto
    uint getNumCols() const { return numCols; };        
    SDL_Texture* getTexture() const { return texture; };    // devuelve la textura

    void load(string filename, uint numRows = 1, uint numCols = 1);     // carga la imagen y genera el source rect
    void loadFrom_Text(const fontName fileName, string text, SDL_Color color);
    
    void render(const SDL_Rect& rect, SDL_RendererFlip flip = SDL_FLIP_NONE) const;     // anadir una imagen
    void renderFrame(const SDL_Rect& destRect, int row, int col, int angle = 0, SDL_RendererFlip flip = SDL_FLIP_NONE) const;   // anadir frame
    void renderText(const SDL_Rect& destRect) const;   // anadir un texto ttf
};














// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
#endif