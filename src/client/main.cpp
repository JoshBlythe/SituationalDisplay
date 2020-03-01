#include <memory>
#include <SDL2/SDL.h>

//#include "PlaneManager.h"
#include "Display.h"
#include "SendData.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <libwebsockets.h>

//struct WsTcpSocket;

int main(int argv, char* argc[])
{
    //PlaneManager manger;
    SendData httpSend;
   //Display *display = new Display(argv, argc);
    //display->InitWindow();

    //display->RunDisplay();

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

        //manger.StateProcessNetwork();
        //manger.Send();
        httpSend.sendData();
    }

    return 0;
}
