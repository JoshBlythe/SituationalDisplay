#include "Display.h"

Display::Display(int argc, char** argv)
{
    enviroment = new Enviroment(argc, argv);

    std::string GlobeImageLoc = enviroment->fileLocations() + "/" + "GlobeImage" + ".png";

    GlobeImage = new SprtieRender(GlobeImageLoc, 0, 0, 800, 600);
}

Display::~Display()
{
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Display::InitWindow()
{
    //initalise SDL
    if(SDL_WasInit(SDL_INIT_EVERYTHING) < 0)
    {
        //throw a exception
        throw Exception("Error initalising SDL!");
    }

    //create window
    window = SDL_CreateWindow("Situational Display",
                              SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              800, 600, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

    //check if window is initalised
    if(!window)
    {
        //throw exception.
        throw Exception("Error creating SDL window!!");

    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(!renderer)
    {
        throw Exception("Error Creating SDL renderer!");
    }

//    if(!SDL_GL_CreateContext(window))
//    {
//        //throw exception.
//        throw Exception("Error during SDL_GL_CreateContext!");
//    }

//    if(glewInit() != GLEW_OK)
//    {
//        throw Exception("Glew Init Error.");
//    }

}

void Display::RunDisplay()
{
    bool _running = true;
    SDL_Event e = {0};


    while(_running)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_QUIT)
            {
                _running = false;
            }
        }

        manger.StateProcessNetwork();

//        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        SDL_PumpEvents();

        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0,0,0, 255);

        //Draw Globe Map.
        //GlobeImage->DrawSprite(renderer);

        //SDL_RenderPresent(renderer);

        //SDL_Delay(3000000);
        //SDL_GL_SwapWindow(window);
    }


}

void Display::DrawPlane()
{

}
