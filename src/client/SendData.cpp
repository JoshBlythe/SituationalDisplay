#include "SendData.h"

#include <stdio.h>
#include <string.h>

#define SERVER_HOST "localhost"
#define SERVER_PORT 1234

SendData::SendData()
{


    server = WsTcpListen(SERVER_PORT);

    if(!server)
    {
        _WsPanic("Unable to Initalise Server");
        abort();
    }

    data = vector_new(unsigned char);
    a = 0;

}

SendData::~SendData()
{
    WsTcpSocketClose(server);
}

void SendData::sendData(PlaneManager &aircrafts)
{
    //get a context of current aircraft/ passing the data stored for each aircraft within
    aircraftData = aircrafts;

    char sc = 0;

    if(aircraftData.planes.empty())
    {
        return;
    }

    struct WsTcpSocket *socket = NULL;
    struct WsTcpSocket *clientConnected = NULL;

    if(clientConnected)
    {
        socket = clientConnected;

        if(!WsTcpSocketConnected(socket))
        {
            printf("Client Disconnected!\n");
            WsTcpSocketClose(socket);
            clientConnected = NULL;
            return;
        }

        if(!WsTcpSocketReady(socket))
        {
            return;
        }

        //receive data here.
        //or send
        WsTcpSocketSend(clientConnected, data);

    }
    else
    {
        socket = server;

        if(!WsTcpSocketReady(socket))
        {
            return;
        }

        printf("Client Connected\n");
        clientConnected = WsTcpSocketAccept(socket);

        //create string to store values
        std::string current;
        current = aircraftData.convertData(aircrafts.planes, a);

        std::cout << current << std::endl;

        for(size_t c = 0; c < current.size(); c++)
        {
            sc = current.at(c);
            vector_push_back(data, sc);

        }

        WsTcpSocketSend(clientConnected, data);


        if(a == aircraftData.planes.size())
        {
            a = 0;
        }
        else if (a < aircraftData.planes.size())
        {
            a++;
            std::cout << a << std::endl;
            if(a == aircraftData.planes.size())
            {
                a = 0;
            }
        }
    }
}



/////////////////////////////////////////////////////
//        size_t lenght = 0;
//        lenght = testingString.size();

//        for (size_t i = 0; i < lenght; i++)
//        {
//            std::string curr = testingString[i];

//            for (size_t c = 0; c < curr.size(); c++)
//            {
//                sc = curr.at(c);
//                vector_push_back(data, sc);
//            }

//        }

        //works
        //WsTcpSocketSend(clientConnected, data);


//        size_t i = 0;
//        //size_t a = 0;
//          std::string current;

//        for (i = 0; i < aircraftData.planes.size(); i++)
//        {
//            current = aircraftData.convertData(aircrafts.planes, i);
//            for(size_t c = 0; c < current.size(); c++)
//            {
//                sc = current.at(c);
//                vector_push_back(data, sc);

//            }

//            WsTcpSocketSend(clientConnected, data);

//        }



