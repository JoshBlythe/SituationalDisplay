#ifndef _SENDDATA_H
#define _SENDDATA_H

//#include "HandleWebSocket.h"
//#include "PlaneManager.h"

#include <string>
#include <iostream>

#include "TcpSocket.h"

struct WsTcpSocket;

class SendData
{
public:
    SendData();
    ~SendData();

    void convertData();
    void sendData();

private:
    WsTcpSocket *server;
    WsTcpSocket *clientConnected;

    //PlaneManager planeData;
    //WsServer* server;
    vector(unsigned char) data;
    //char *maybe;

    //std::string please;
};

#endif
