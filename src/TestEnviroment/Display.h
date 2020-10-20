#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <SDL2/SDL.h>


//#include "TcpSocket.h"
#include "Exception.h"
#include "SpriteRender.h"
#include "Enviroment.h"

#include "PlaneManager.h"

class Display
{
public:
    Display(int argc, char** argv);
    ~Display();

    void InitWindow();
    void RunDisplay();
    void DrawPlane();


private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    Enviroment* enviroment;
    PlaneManager manger;

    SprtieRender* GlobeImage;
    //SprtieRender render;

};
