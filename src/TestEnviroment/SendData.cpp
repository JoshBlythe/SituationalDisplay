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

void SendData::SendAircraftInfo(PlaneManager &aircrafts)
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

        //maybe put this before doing sending the message to solve the issue.
        if(a > (aircraftData.planes.size() - 1))
        {
            a = 0;
        }
        //create string to store values
        std::string current;
        current = aircraftData.convertData(a);

        //std::cout << current << std::endl;

        //push data into a vector of format type which is able to be sent via the socket
        for(size_t c = 0; c < current.size(); c++)
        {
            sc = current.at(c);
            vector_push_back(data, sc);

        }

        //send the data via a tcp socket (to clientConnected socket)
        WsTcpSocketSend(clientConnected, data);

    }

    //close client socket
    WsTcpSocketClose(clientConnected);

    if(a == (aircraftData.planes.size() - 1))
    {
        a = 0;
        return;
    }
    else if (a < (aircraftData.planes.size() - 1))
    {
        if(a == (aircraftData.planes.size() - 1))
        {
            a = 0;
            return;
        }
        else
        {
            std::cout << a << std::endl;
            a++;
        }

    }

}
