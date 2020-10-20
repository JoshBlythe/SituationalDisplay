#include "SpriteRender.h"

SprtieRender::SprtieRender(std::string file, int x, int y, int w, int h)
{
     filereadin = file;

     position.x = x;
     position.y = y;
     position.w = w;
     position.h = h;
}

SprtieRender::~SprtieRender()
{
    if(texture)
    {
        SDL_DestroyTexture(texture);
    }
}

void SprtieRender::DrawSprite(SDL_Renderer* renderer)
{
    SDL_Surface* image = IMG_Load(filereadin.c_str());

     if(!image)
     {
         std::cout << SDL_GetError() << std::endl;
         std::cout << "Couldn't find image." << filereadin.c_str() << IMG_GetError() << std::endl;
     }

    texture = SDL_CreateTextureFromSurface(renderer, image);

    SDL_FreeSurface(image);

    if(texture)
    {
        SDL_RenderCopy(renderer, texture, NULL, &position);
    }
}
