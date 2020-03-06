#ifndef _SENDDATA_H
#define _SENDDATA_H

//#include "HandleWebSocket.h"
//#include "PlaneManager.h"

#include <jsoncpp/json/json.h>
//#include <jsoncpp/json/writer.h>
#include <string>
#include <iostream>

#include "PlaneManager.h"
//#include "TcpSocket.h"

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
    PlaneManager *aircraftData;

    //PlaneManager planeData;
    //WsServer* server;
    vector(unsigned char) data;
    //char *maybe;


};

#endif
