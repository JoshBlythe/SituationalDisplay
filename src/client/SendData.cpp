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
}

SendData::~SendData()
{
    WsTcpSocketClose(server);
}

void SendData::convertData()
{

    //TODO :
    //USE JSON TO CONVERT THE DATA INTO A VECTOR
    //Send that vector along down the socket

    //PlaneManager plane;

//    if(plane.planes.size() == 0)
//    {
//        return;
//    }

//    for (size_t i = 0; i < plane.planes.size(); i++)
//    {

//    }

}

void SendData::sendData()
{
    char si = 0;
    std::string please = "hello";

    struct WsTcpSocket *socket = NULL;

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

        //memcpy(data, maybe, sizeof (data));

        //vector_push_back(data, 'A');
        //vector_push_back(data, 'P');
        //vector_push_back(data, 'P');
        //vector_push_back(data, 'L');
        //vector_push_back(data, 'E');


        for (size_t i = 0; i < please.size(); i++)
        {
            si = please.at(i);

            vector_push_back(data, si);

        }


        WsTcpSocketSend(clientConnected, data);

    }

    //if(WsTcpSocketReady(server))
    //{
      //  WsTcpSocketAccept(server);
        //send the data to down the port
    //}
}



