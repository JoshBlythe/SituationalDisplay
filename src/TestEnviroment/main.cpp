#include <memory>
//#include <SDL2/SDL.h>

#include "Display.h"
#include "SendData.h"
#include "ServerMessageEm.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <libwebsockets.h>


int main()
{
   ServerMessageEm *testServer = new ServerMessageEm();
   PlaneManager manger;
   SendData *httpSend = new SendData();
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

        testServer->SetAircraftPos();
        testServer->SendMessage();

        //obtain data from dump1090 server/seperate it and store it
//        manger.StateProcessPacket();
        manger.StateProcessNetwork();

        //send the data via tcp server to web application
        httpSend->SendAircraftInfo(manger);
//        manger.RemoveData();
    }

    return 0;
}
