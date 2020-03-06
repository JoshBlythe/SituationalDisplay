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

void SendData::sendData()
{
    //test without dump1090 data
//    std::vector<std::string> testingString;

//    std::string please = "name: ";

//    for (int i = 0; i < 5; i++)
//    {
//       please[3] = i;
//       testingString.push_back(please);
//    }

    char sc = 0;

    //PlaneManager aircraftData;

    if(aircraftData->jsonConverted.empty())
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


        //size_t length = aircraftData.toSend.size();

        for (size_t i = 0; i < aircraftData->jsonConverted.size(); i++)
        {
            //set the current variable to be the current string in the vector
            std::string cur = aircraftData->jsonConverted.at(i);

            //loop though the lenght of the string
            for (size_t c = 0; c < cur.size(); c++)
            {
                //get each character in the sting
                sc = cur.at(c);
                //push data into vector to send to client
                vector_push_back(data, sc);
            }
        }

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

        WsTcpSocketSend(clientConnected, data);


    }
}



