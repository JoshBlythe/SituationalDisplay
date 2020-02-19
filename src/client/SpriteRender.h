#ifndef _SPRITERENDER_H
#define _SPRITERENDER_H

#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class SprtieRender
{
public:

    SprtieRender(std::string file, int x, int y, int w, int h);
    ~SprtieRender();

    void DrawSprite(SDL_Renderer* renderer);
    SDL_Texture* loadTexture();

private:
    std::string filereadin;

    SDL_Rect position;

    SDL_Texture* texture;

    std::vector<SprtieRender> textures;
};

#endif
